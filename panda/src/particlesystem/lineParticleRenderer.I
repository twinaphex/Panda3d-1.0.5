// Filename: lineParticleRenderer.I
// Created by:  darren (06Oct00)
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
//    Function : set_head_color
//      Access : public
////////////////////////////////////////////////////////////////////
INLINE void LineParticleRenderer::
set_head_color(const Colorf& c) {
  _head_color = c;
}

////////////////////////////////////////////////////////////////////
//    Function : set_tail_color
//      Access : public
////////////////////////////////////////////////////////////////////
INLINE void LineParticleRenderer::
set_tail_color(const Colorf& c) {
  _tail_color = c;
}

////////////////////////////////////////////////////////////////////
//    Function : get_head_color
//      Access : public
////////////////////////////////////////////////////////////////////
INLINE const Colorf& LineParticleRenderer::
get_head_color() const {
  return _head_color;
}

////////////////////////////////////////////////////////////////////
//    Function : get_tail_color
//      Access : public
////////////////////////////////////////////////////////////////////
INLINE const Colorf& LineParticleRenderer::
get_tail_color() const {
  return _tail_color;
}
