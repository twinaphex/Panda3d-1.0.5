// Filename: cLwoPolygons.h
// Created by:  drose (25Apr01)
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

#ifndef CLWOPOLYGONS_H
#define CLWOPOLYGONS_H

#include "pandatoolbase.h"

#include "lwoPolygons.h"
#include "eggGroup.h"
#include "pointerTo.h"

#include "pmap.h"

class LwoToEggConverter;
class CLwoPoints;
class CLwoSurface;
class LwoTags;
class LwoPolygonTags;
class LwoDiscontinuousVertexMap;

////////////////////////////////////////////////////////////////////
//       Class : CLwoPolygons
// Description : This class is a wrapper around LwoPolygons and stores
//               additional information useful during the
//               conversion-to-egg process.
////////////////////////////////////////////////////////////////////
class CLwoPolygons {
public:
  INLINE CLwoPolygons(LwoToEggConverter *converter,
                      const LwoPolygons *polygons,
                      CLwoPoints *points);

  void add_ptags(const LwoPolygonTags *lwo_ptags, const LwoTags *tags);
  void add_vmad(const LwoDiscontinuousVertexMap *lwo_vmad);

  CLwoSurface *get_surface(int polygon_index) const;
  bool get_uv(const string &uv_name, int pi, int vi, LPoint2f &uv) const;

  void make_egg();
  void connect_egg();

  LwoToEggConverter *_converter;
  CPT(LwoPolygons) _polygons;
  CLwoPoints *_points;
  PT(EggGroup) _egg_group;

  const LwoTags *_tags;
  typedef pmap<IffId, const LwoPolygonTags *> PTags;
  PTags _ptags;

  const LwoPolygonTags *_surf_ptags;

  // There might be named maps associated with the polygons to bring a
  // per-polygon mapping to the UV's.
  typedef pmap<string, const LwoDiscontinuousVertexMap *> VMad;
  VMad _txuv;

private:
  void make_faces();
};

#include "cLwoPolygons.I"

#endif


