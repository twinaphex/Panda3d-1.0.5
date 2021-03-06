// Filename: qtessSurface.I
// Created by:  drose (13Oct03)
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


////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::get_name
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
INLINE const string &QtessSurface::
get_name() const {
  return _egg_surface->get_name();
}

////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::is_valid
//       Access: Public
//  Description: Returns true if the defined surface is valid, false
//               otherwise.
////////////////////////////////////////////////////////////////////
INLINE bool QtessSurface::
is_valid() const {
  return (_nurbs != (NurbsSurfaceEvaluator *)NULL);
}

////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::set_importance
//       Access: Public
//  Description: Sets the importance of the surface, as a ratio in
//               proportion to the square of its size.
////////////////////////////////////////////////////////////////////
INLINE void QtessSurface::
set_importance(double importance2) {
  _importance = sqrt(importance2);
  _importance2 = importance2;
}

////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::set_match_u
//       Access: Public
//  Description: Indicates the surface to which this surface must
//               match in its U direction.  If u_to_u is true, it
//               matches to the other surface's U direction;
//               otherwise, it matches to the other surface's V
//               direction.
//
//               Note that the surface pointer is an indirect pointer.
//               The value passed in is the address of the pointer to
//               the actual surface (which may or may not be filled in
//               yet).  The actual pointer may be filled in later.
////////////////////////////////////////////////////////////////////
INLINE void QtessSurface::
set_match_u(QtessSurface **match_u, bool match_u_to_u) {
  _match_u = match_u;
  _match_u_to_u = match_u_to_u;
}

////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::set_match_v
//       Access: Public
//  Description: Indicates the surface to which this surface must
//               match in its V direction.  If v_to_v is true, it
//               matches to the other surface's V direction;
//               otherwise, it matches to the other surface's U
//               direction.
//
//               Note that the surface pointer is an indirect pointer.
//               The value passed in is the address of the pointer to
//               the actual surface (which may or may not be filled in
//               yet).  The actual pointer may be filled in later.
////////////////////////////////////////////////////////////////////
INLINE void QtessSurface::
set_match_v(QtessSurface **match_v, bool match_v_to_v) {
  _match_v = match_v;
  _match_v_to_v = match_v_to_v;
}

////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::set_min_u
//       Access: Public
//  Description: Specifies the absolute minimum number of segments
//               allowed in the U direction.
////////////////////////////////////////////////////////////////////
INLINE void QtessSurface::
set_min_u(int min_u) {
  _min_u = min_u;
}

////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::set_min_v
//       Access: Public
//  Description: Specifies the absolute minimum number of segments
//               allowed in the V direction.
////////////////////////////////////////////////////////////////////
INLINE void QtessSurface::
set_min_v(int min_v) {
  _min_v = min_v;
}


////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::count_patches
//       Access: Public
//  Description: Returns the number of patches the NURBS contains.
//               Each patch is a square area bounded by isoparams.
//               This actually scales by the importance of the
//               surface, if it is not 1.
////////////////////////////////////////////////////////////////////
INLINE double QtessSurface::
count_patches() const {
  return _num_u * _num_v * _importance2;
}

////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::count_tris
//       Access: Public
//  Description: Returns the number of triangles that will be
//               generated by the current tesselation parameters.
////////////////////////////////////////////////////////////////////
INLINE int QtessSurface::
count_tris() const {
  return _tess_u * _tess_v * 2;
}

////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::get_joint_membership_index
//       Access: Public
//  Description: Returns the extra dimension number within the surface
//               where the vertex membership in the indicated joint
//               should be stored.
////////////////////////////////////////////////////////////////////
INLINE int QtessSurface::
get_joint_membership_index(EggGroup *joint) {
  JointTable::iterator jti = _joint_table.find(joint);
  if (jti != _joint_table.end()) {
    return (*jti).second;
  }
  int d = _next_d;
  _next_d++;
  _joint_table[joint] = d;
  return d;
}

////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::get_dxyz_index
//       Access: Public
//  Description: Returns the extra dimension number within the surface
//               where the indicated Dxyz morph offset should be stored.
////////////////////////////////////////////////////////////////////
INLINE int QtessSurface::
get_dxyz_index(const string &morph_name) {
  MorphTable::iterator mti = _dxyz_table.find(morph_name);
  if (mti != _dxyz_table.end()) {
    return (*mti).second;
  }
  int d = _next_d;
  _next_d += 3;
  _dxyz_table[morph_name] = d;
  return d;
}

////////////////////////////////////////////////////////////////////
//     Function: QtessSurface::get_drgba_index
//       Access: Public
//  Description: Returns the extra dimension number within the surface
//               where the indicated Drgba morph offset should be stored.
////////////////////////////////////////////////////////////////////
INLINE int QtessSurface::
get_drgba_index(const string &morph_name) {
  MorphTable::iterator mti = _drgba_table.find(morph_name);
  if (mti != _drgba_table.end()) {
    return (*mti).second;
  }
  int d = _next_d;
  _next_d += 4;
  _drgba_table[morph_name] = d;
  return d;
}
