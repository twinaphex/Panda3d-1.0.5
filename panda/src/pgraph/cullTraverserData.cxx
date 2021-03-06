// Filename: cullTraverserData.cxx
// Created by:  drose (06Mar02)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) 2001 - 2004, Disney Enterprises, Inc.  All rights reserved
//
// All use of this software is subject to the terms of the Panda 3d
// Software license.  You should have received a copy of this license
// along with this source code; you will also find a current copy of
// the license at http://etc.cmu.edu/panda3d/docs/license/ .
//
// To contact the maintainers of this program write to
// panda3d-general@lists.sourceforge.net .
//
////////////////////////////////////////////////////////////////////

#include "cullTraverserData.h"
#include "cullTraverser.h"
#include "config_pgraph.h"
#include "pandaNode.h"
#include "colorAttrib.h"
#include "textureAttrib.h"
#include "renderModeAttrib.h"
#include "billboardEffect.h"
#include "compassEffect.h"
#include "polylightEffect.h"
#include "renderState.h"


////////////////////////////////////////////////////////////////////
//     Function: CullTraverserData::apply_transform_and_state
//       Access: Public
//  Description: Applies the transform and state from the current
//               node onto the current data.  This also evaluates
//               billboards, etc.
////////////////////////////////////////////////////////////////////
void CullTraverserData::
apply_transform_and_state(CullTraverser *trav) {
  PandaNode *node = _node_path.node();
  CPT(RenderState) node_state = node->get_state();

  if (trav->has_tag_state_key() && node->has_tag(trav->get_tag_state_key())) {
    // Here's a node that has been tagged with the special key for our
    // current camera.  This indicates some special state transition
    // for this node, which is unique to this camera.
    const Camera *camera = trav->get_scene()->get_camera_node();
    string tag_state = node->get_tag(trav->get_tag_state_key());
    node_state = node_state->compose(camera->get_tag_state(tag_state));
  }

  apply_transform_and_state(trav, node->get_transform(),
                            node_state, node->get_effects());
}

////////////////////////////////////////////////////////////////////
//     Function: CullTraverserData::apply_specific_transform
//       Access: Public
//  Description: Applies the indicated transform and state changes
//               (e.g. as extracted from a node) onto the current
//               data.  This also evaluates billboards, etc.
////////////////////////////////////////////////////////////////////
void CullTraverserData::
apply_transform_and_state(CullTraverser *trav, 
                          CPT(TransformState) node_transform, 
                          CPT(RenderState) node_state,
                          CPT(RenderEffects) node_effects) {
  if (node_effects->has_cull_callback()) {
    node_effects->cull_callback(trav, *this, node_transform, node_state);
  }

  if (!node_transform->is_identity()) {
    _net_transform = _net_transform->compose(node_transform);
    _render_transform = _render_transform->compose(node_transform);

    if ((_view_frustum != (GeometricBoundingVolume *)NULL) ||
        (_guard_band != (GeometricBoundingVolume *)NULL)) {
      // We need to move the viewing frustums into the node's
      // coordinate space by applying the node's inverse transform.
      if (node_transform->is_singular()) {
        // But we can't invert a singular transform!  Instead of
        // trying, we'll just give up on frustum culling from this
        // point down.
        _view_frustum = (GeometricBoundingVolume *)NULL;
        _guard_band = (GeometricBoundingVolume *)NULL;

      } else {
        CPT(TransformState) inv_transform = 
          node_transform->invert_compose(TransformState::make_identity());

        // Copy the bounding volumes for the frustums so we can
        // transform them.
        if (_view_frustum != (GeometricBoundingVolume *)NULL) {
          _view_frustum = DCAST(GeometricBoundingVolume, _view_frustum->make_copy());
          _view_frustum->xform(inv_transform->get_mat());
        }

        if (_guard_band != (GeometricBoundingVolume *)NULL) {
          _guard_band = DCAST(GeometricBoundingVolume, _guard_band->make_copy());
          _guard_band->xform(inv_transform->get_mat());
        }
      }
    }
  }

  _state = _state->compose(node_state);
}

////////////////////////////////////////////////////////////////////
//     Function: CullTraverserData::is_in_view_impl
//       Access: Private
//  Description: The private implementation of is_in_view().
////////////////////////////////////////////////////////////////////
bool CullTraverserData::
is_in_view_impl() {
  // By the time we get here, we know we have a viewing frustum.
  nassertr(_view_frustum != (GeometricBoundingVolume *)NULL, true);

  const BoundingVolume &node_volume = node()->get_bound();
  nassertr(node_volume.is_of_type(GeometricBoundingVolume::get_class_type()), false);
  const GeometricBoundingVolume *node_gbv =
    DCAST(GeometricBoundingVolume, &node_volume);

  int result = _view_frustum->contains(node_gbv);

  if (pgraph_cat.is_spam()) {
    pgraph_cat.spam()
      << _node_path << " cull result = " << hex << result << dec << "\n";
  }

  if (result == BoundingVolume::IF_no_intersection) {
    // No intersection at all.  Cull.
    if (!fake_view_frustum_cull) {
      return false;
    }

    // If we have fake view-frustum culling enabled, instead of
    // actually culling an object we simply force it to be drawn in
    // red wireframe.
    _view_frustum = (GeometricBoundingVolume *)NULL;
    CPT(RenderState) fake_state = get_fake_view_frustum_cull_state();
    _state = _state->compose(fake_state);
    
  } else if ((result & BoundingVolume::IF_all) != 0) {
    // The node and its descendants are completely enclosed within
    // the frustum.  No need to cull further.
    _view_frustum = (GeometricBoundingVolume *)NULL;

  } else {
    if (node()->is_final()) {
      // The bounding volume is partially, but not completely,
      // within the viewing frustum.  Normally we'd keep testing
      // child bounding volumes as we continue down.  But this node
      // has the "final" flag, so the user is claiming that there is
      // some important reason we should consider everything visible
      // at this point.  So be it.
      _view_frustum = (GeometricBoundingVolume *)NULL;
    }
  }

  return true;
}


////////////////////////////////////////////////////////////////////
//     Function: CullTraverserData::get_fake_view_frustum_cull_state
//       Access: Private, Static
//  Description: Returns a RenderState for rendering stuff in red
//               wireframe, strictly for the fake_view_frustum_cull
//               effect.
////////////////////////////////////////////////////////////////////
CPT(RenderState) CullTraverserData::
get_fake_view_frustum_cull_state() {
  // Once someone asks for this pointer, we hold its reference count
  // and never free it.
  static CPT(RenderState) state = (const RenderState *)NULL;
  if (state == (const RenderState *)NULL) {
    state = RenderState::make
      (ColorAttrib::make_flat(Colorf(1.0f, 0.0f, 0.0f, 1.0f)),
       TextureAttrib::make_all_off(),
       RenderModeAttrib::make(RenderModeAttrib::M_wireframe),
       RenderState::get_max_priority());
  }
  return state;
}

