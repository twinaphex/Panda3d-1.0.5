// Filename: indirectLess.h
// Created by:  drose (27Jun01)
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

#ifndef INDIRECTLESS_H
#define INDIRECTLESS_H

#include "pandabase.h"

////////////////////////////////////////////////////////////////////
//       Class : IndirectLess
// Description : An STL function object class, this is intended to be
//               used on any ordered collection of pointers to classes
//               that contain an operator <() method.  It defines the
//               order of the pointers via operator <().
////////////////////////////////////////////////////////////////////
template<class ObjectType>
class IndirectLess {
public:
  INLINE bool operator () (const ObjectType *a, const ObjectType *b) const;
};

#include "indirectLess.I"

#endif

