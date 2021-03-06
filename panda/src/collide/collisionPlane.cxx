// Filename: collisionPlane.cxx
// Created by:  drose (25Apr00)
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


#include "collisionPlane.h"
#include "collisionHandler.h"
#include "collisionEntry.h"
#include "collisionSphere.h"
#include "collisionLine.h"
#include "collisionRay.h"
#include "collisionSegment.h"
#include "config_collide.h"

#include "pointerToArray.h"
#include "geomNode.h"
#include "geom.h"
#include "datagram.h"
#include "datagramIterator.h"
#include "bamReader.h"
#include "bamWriter.h"
#include "omniBoundingVolume.h"
#include "geomQuad.h"

TypeHandle CollisionPlane::_type_handle;

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::make_copy
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
CollisionSolid *CollisionPlane::
make_copy() {
  return new CollisionPlane(*this);
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::xform
//       Access: Public, Virtual
//  Description: Transforms the solid by the indicated matrix.
////////////////////////////////////////////////////////////////////
void CollisionPlane::
xform(const LMatrix4f &mat) {
  _plane = _plane * mat;
  CollisionSolid::xform(mat);
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::get_collision_origin
//       Access: Public, Virtual
//  Description: Returns the point in space deemed to be the "origin"
//               of the solid for collision purposes.  The closest
//               intersection point to this origin point is considered
//               to be the most significant.
////////////////////////////////////////////////////////////////////
LPoint3f CollisionPlane::
get_collision_origin() const {
  // No real sensible origin exists for a plane.  We return 0, 0, 0,
  // without even bothering to ensure that that point exists on the
  // plane.
  return LPoint3f::origin();
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::output
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
void CollisionPlane::
output(ostream &out) const {
  out << "cplane, (" << _plane << ")";
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::recompute_bound
//       Access: Protected, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
BoundingVolume *CollisionPlane::
recompute_bound() {
  // Planes always have an infinite bounding volume.
  BoundedObject::recompute_bound();
  // Less than ideal: we throw away whatever we just allocated in
  // BoundedObject.
  return set_bound_ptr(new OmniBoundingVolume);
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::test_intersection_from_sphere
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
PT(CollisionEntry) CollisionPlane::
test_intersection_from_sphere(const CollisionEntry &entry) const {
  const CollisionSphere *sphere;
  DCAST_INTO_R(sphere, entry.get_from(), 0);

  const LMatrix4f &wrt_mat = entry.get_wrt_mat();

  LPoint3f from_center = sphere->get_center() * wrt_mat;
  LVector3f from_radius_v =
    LVector3f(sphere->get_radius(), 0.0f, 0.0f) * wrt_mat;
  float from_radius = length(from_radius_v);

  float dist = dist_to_plane(from_center);
  if (dist > from_radius) {
    // No intersection.
    return NULL;
  }

  if (collide_cat.is_debug()) {
    collide_cat.debug()
      << "intersection detected from " << entry.get_from_node_path() << " into "
      << entry.get_into_node_path() << "\n";
  }
  PT(CollisionEntry) new_entry = new CollisionEntry(entry);

  LVector3f from_normal = get_normal() * entry.get_inv_wrt_mat();

  LVector3f normal = (has_effective_normal() && sphere->get_respect_effective_normal()) ? get_effective_normal() : get_normal();

  new_entry->set_surface_normal(normal);
  new_entry->set_surface_point(from_center - get_normal() * dist);
  new_entry->set_interior_point(from_center - get_normal() * from_radius);

  return new_entry;
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::test_intersection_from_line
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
PT(CollisionEntry) CollisionPlane::
test_intersection_from_line(const CollisionEntry &entry) const {
  const CollisionLine *line;
  DCAST_INTO_R(line, entry.get_from(), 0);

  const LMatrix4f &wrt_mat = entry.get_wrt_mat();

  LPoint3f from_origin = line->get_origin() * wrt_mat;
  LVector3f from_direction = line->get_direction() * wrt_mat;

  float t;
  if (!_plane.intersects_line(t, from_origin, from_direction)) {
    // No intersection.
    return NULL;
  }

  if (collide_cat.is_debug()) {
    collide_cat.debug()
      << "intersection detected from " << entry.get_from_node_path()
      << " into " << entry.get_into_node_path() << "\n";
  }
  PT(CollisionEntry) new_entry = new CollisionEntry(entry);

  LPoint3f into_intersection_point = from_origin + t * from_direction;

  LVector3f normal = (has_effective_normal() && line->get_respect_effective_normal()) ? get_effective_normal() : get_normal();

  new_entry->set_surface_normal(normal);
  new_entry->set_surface_point(into_intersection_point);

  return new_entry;
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::test_intersection_from_ray
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
PT(CollisionEntry) CollisionPlane::
test_intersection_from_ray(const CollisionEntry &entry) const {
  const CollisionRay *ray;
  DCAST_INTO_R(ray, entry.get_from(), 0);

  const LMatrix4f &wrt_mat = entry.get_wrt_mat();

  LPoint3f from_origin = ray->get_origin() * wrt_mat;
  LVector3f from_direction = ray->get_direction() * wrt_mat;

  float t;
  if (!_plane.intersects_line(t, from_origin, from_direction)) {
    // No intersection.
    return NULL;
  }

  if (t < 0.0f) {
    // The intersection point is before the start of the ray.
    return NULL;
  }

  if (collide_cat.is_debug()) {
    collide_cat.debug()
      << "intersection detected from " << entry.get_from_node_path()
      << " into " << entry.get_into_node_path() << "\n";
  }
  PT(CollisionEntry) new_entry = new CollisionEntry(entry);

  LPoint3f into_intersection_point = from_origin + t * from_direction;

  LVector3f normal = (has_effective_normal() && ray->get_respect_effective_normal()) ? get_effective_normal() : get_normal();

  new_entry->set_surface_normal(normal);
  new_entry->set_surface_point(into_intersection_point);

  return new_entry;
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::test_intersection_from_segment
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
PT(CollisionEntry) CollisionPlane::
test_intersection_from_segment(const CollisionEntry &entry) const {
  const CollisionSegment *segment;
  DCAST_INTO_R(segment, entry.get_from(), 0);

  const LMatrix4f &wrt_mat = entry.get_wrt_mat();

  LPoint3f from_a = segment->get_point_a() * wrt_mat;
  LPoint3f from_b = segment->get_point_b() * wrt_mat;
  LVector3f from_direction = from_b - from_a;

  float t;
  if (!_plane.intersects_line(t, from_a, from_direction)) {
    // No intersection.
    return NULL;
  }

  if (t < 0.0f || t > 1.0f) {
    // The intersection point is before the start of the segment or
    // after the end of the segment.
    return NULL;
  }

  if (collide_cat.is_debug()) {
    collide_cat.debug()
      << "intersection detected from " << entry.get_from_node_path()
      << " into " << entry.get_into_node_path() << "\n";
  }
  PT(CollisionEntry) new_entry = new CollisionEntry(entry);

  LPoint3f into_intersection_point = from_a + t * from_direction;

  LVector3f normal = (has_effective_normal() && segment->get_respect_effective_normal()) ? get_effective_normal() : get_normal();

  new_entry->set_surface_normal(normal);
  new_entry->set_surface_point(into_intersection_point);

  return new_entry;
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::fill_viz_geom
//       Access: Protected, Virtual
//  Description: Fills the _viz_geom GeomNode up with Geoms suitable
//               for rendering this solid.
////////////////////////////////////////////////////////////////////
void CollisionPlane::
fill_viz_geom() {
  if (collide_cat.is_debug()) {
    collide_cat.debug()
      << "Recomputing viz for " << *this << "\n";
  }

  // Since we can't represent an infinite plane, we'll have to be
  // satisfied with drawing a big polygon.  Choose four points on the
  // plane to be the corners of the polygon.

  // We must choose four points fairly reasonably spread apart on
  // the plane.  We'll start with a center point and one corner
  // point, and then use cross products to find the remaining three
  // corners of a square.

  // The center point will be on the axis with the largest
  // coefficent.  The first corner will be diagonal in the other two
  // dimensions.

  LPoint3f cp;
  LVector3f p1, p2, p3, p4;

  LVector3f normal = get_normal();
  float D = _plane[3];

  if (fabs(normal[0]) > fabs(normal[1]) &&
      fabs(normal[0]) > fabs(normal[2])) {
    // X has the largest coefficient.
    cp.set(-D / normal[0], 0.0f, 0.0f);
    p1 = LPoint3f(-(normal[1] + normal[2] + D)/normal[0], 1.0f, 1.0f) - cp;

  } else if (fabs(normal[1]) > fabs(normal[2])) {
    // Y has the largest coefficient.
    cp.set(0.0f, -D / normal[1], 0.0f);
    p1 = LPoint3f(1.0f, -(normal[0] + normal[2] + D)/normal[1], 1.0f) - cp;

  } else {
    // Z has the largest coefficient.
    cp.set(0.0f, 0.0f, -D / normal[2]);
    p1 = LPoint3f(1.0f, 1.0f, -(normal[0] + normal[1] + D)/normal[2]) - cp;
  }

  p1.normalize();
  p2 = cross(normal, p1);
  p3 = cross(normal, p2);
  p4 = cross(normal, p3);

  static const double plane_scale = 10.0;

  PTA_Vertexf verts;
  verts.push_back(cp + p1 * plane_scale);
  verts.push_back(cp + p2 * plane_scale);
  verts.push_back(cp + p3 * plane_scale);
  verts.push_back(cp + p4 * plane_scale);

  GeomQuad *quad = new GeomQuad;
  quad->set_coords(verts);
  quad->set_num_prims(1);

  _viz_geom->add_geom(quad, get_solid_viz_state());
  _viz_geom->add_geom(quad, get_wireframe_viz_state());
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::write_datagram
//       Access: Public
//  Description: Function to write the important information in
//               the particular object to a Datagram
////////////////////////////////////////////////////////////////////
void CollisionPlane::
write_datagram(BamWriter *manager, Datagram &me)
{
  CollisionSolid::write_datagram(manager, me);
  _plane.write_datagram(me);
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::fillin
//       Access: Protected
//  Description: Function that reads out of the datagram (or asks
//               manager to read) all of the data that is needed to
//               re-create this object and stores it in the appropiate
//               place
////////////////////////////////////////////////////////////////////
void CollisionPlane::
fillin(DatagramIterator& scan, BamReader* manager)
{
  CollisionSolid::fillin(scan, manager);
  _plane.read_datagram(scan);
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::make_CollisionPlane
//       Access: Protected
//  Description: Factory method to generate a CollisionPlane object
////////////////////////////////////////////////////////////////////
TypedWritable* CollisionPlane::
make_CollisionPlane(const FactoryParams &params)
{
  CollisionPlane *me = new CollisionPlane;
  DatagramIterator scan;
  BamReader *manager;

  parse_params(params, scan, manager);
  me->fillin(scan, manager);
  return me;
}

////////////////////////////////////////////////////////////////////
//     Function: CollisionPlane::register_with_factory
//       Access: Public, Static
//  Description: Factory method to generate a CollisionPlane object
////////////////////////////////////////////////////////////////////
void CollisionPlane::
register_with_read_factory(void)
{
  BamReader::get_factory()->register_factory(get_class_type(), make_CollisionPlane);
}
