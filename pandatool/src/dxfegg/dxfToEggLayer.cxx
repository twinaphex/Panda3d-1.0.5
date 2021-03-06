// Filename: dxfToEggLayer.cxx
// Created by:  drose (04May04)
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

#include "dxfToEggLayer.h"
#include "dxfToEggConverter.h"

#include "dxfFile.h"
#include "eggGroup.h"
#include "eggPolygon.h"
#include "eggLine.h"
#include "eggVertex.h"
#include "eggVertexPool.h"


////////////////////////////////////////////////////////////////////
//     Function: DXFToEggLayer::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
DXFToEggLayer::
DXFToEggLayer(const string &name, EggGroupNode *parent) : DXFLayer(name) {
  _group = new EggGroup(name);
  parent->add_child(_group);
  _vpool = new EggVertexPool(name);
  _group->add_child(_vpool);
}


////////////////////////////////////////////////////////////////////
//     Function: DXFToEggLayer::add_polygon
//       Access: Public
//  Description: Given that done_entity() has just been called and that
//               the current entity represents a polygon, adds the
//               corresponding polygon to the layer's EggGroup and
//               vertex pool.
////////////////////////////////////////////////////////////////////
void DXFToEggLayer::
add_polygon(const DXFToEggConverter *entity) {
  EggPolygon *poly = new EggPolygon;
  _group->add_child(poly);

  const DXFFile::Color &color = entity->get_color();
  poly->set_color(Colorf(color.r, color.g, color.b, 1.0));

  // A polyline's vertices are stored in the attached vector by dxf.C.
  // They were defined in the DXF file using a series of "VERTEX"
  // entries.

  // For a 3dface, the vertices are defined explicitly as part of the
  // entity; but in this case, they were added to the vector before
  // add_polygon() was called.

  DXFVertices::const_iterator vi;
  for (vi = entity->_verts.begin();
       vi != entity->_verts.end();
       ++vi) {
    poly->add_vertex(add_vertex(*vi));
  }

  poly->cleanup();
}


////////////////////////////////////////////////////////////////////
//     Function: DXFToEggLayer::add_line
//       Access: Public
//  Description: Similar to add_polygon(), but adds a set of point
//               lights instead.
////////////////////////////////////////////////////////////////////
void DXFToEggLayer::
add_line(const DXFToEggConverter *entity) {
  EggLine *line = new EggLine;
  _group->add_child(line);

  const DXFFile::Color &color = entity->get_color();
  line->set_color(Colorf(color.r, color.g, color.b, 1.0));

  DXFVertices::const_iterator vi;
  for (vi = entity->_verts.begin();
       vi != entity->_verts.end();
       ++vi) {
    line->add_vertex(add_vertex(*vi));
  }
}


////////////////////////////////////////////////////////////////////
//     Function: DXFToEggLayer::add_vertex
//       Access: Public
//  Description: Adds a unique vertex to the layer's vertex pool and
//               returns it.  If the vertex was already defined
//               previously, returns the original definition.  This is
//               designed to share the common vertices within a layer.
////////////////////////////////////////////////////////////////////
EggVertex *DXFToEggLayer::
add_vertex(const DXFVertex &vert) {
  EggVertex egg_vert;
  egg_vert.set_pos(vert._p);

  return _vpool->create_unique_vertex(egg_vert);
}
