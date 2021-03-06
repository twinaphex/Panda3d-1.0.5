// Filename: orientedParticle.cxx
// Created by:  charles (19Jun00)
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

#include "orientedParticle.h"

////////////////////////////////////////////////////////////////////
//    Function : OrientedParticle
//      Access : public
// Description : simple constructor
////////////////////////////////////////////////////////////////////
OrientedParticle::
OrientedParticle(int lifespan, bool alive) :
  BaseParticle(lifespan, alive) {
  set_oriented(true);
}

////////////////////////////////////////////////////////////////////
//    Function : OrientedParticle
//      Access : public
// Description : copy constructor
////////////////////////////////////////////////////////////////////
OrientedParticle::
OrientedParticle(const OrientedParticle &copy) :
  BaseParticle(copy) {
}

////////////////////////////////////////////////////////////////////
//    Function : ~OrientedParticle
//      Access : public
// Description : simple destructor
////////////////////////////////////////////////////////////////////
OrientedParticle::
~OrientedParticle() {
}

////////////////////////////////////////////////////////////////////
//    Function : make_copy
//      Access : public, virtual
// Description : simple destructor
////////////////////////////////////////////////////////////////////
PhysicsObject *OrientedParticle::
make_copy() const {
  return new OrientedParticle(*this);
}

////////////////////////////////////////////////////////////////////
//    Function : init
//      Access : Public
// Description : particle init routine
////////////////////////////////////////////////////////////////////
void OrientedParticle::
init() {
}

////////////////////////////////////////////////////////////////////
//    Function : die
//      Access : public
// Description : particle death routine
////////////////////////////////////////////////////////////////////
void OrientedParticle::
die() {
}

////////////////////////////////////////////////////////////////////
//    Function : update
//      Access : public
// Description : particle update routine.
//               This NEEDS to be filled in with quaternion slerp
//               stuff, or oriented particles will not rotate.
////////////////////////////////////////////////////////////////////
void OrientedParticle::
update() {
}

////////////////////////////////////////////////////////////////////
//     Function : output
//       Access : Public
//  Description : Write a string representation of this instance to
//                <out>.
////////////////////////////////////////////////////////////////////
void OrientedParticle::
output(ostream &out) const {
  #ifndef NDEBUG //[
  out<<"OrientedParticle";
  #endif //] NDEBUG
}

////////////////////////////////////////////////////////////////////
//     Function : write
//       Access : Public
//  Description : Write a string representation of this instance to
//                <out>.
////////////////////////////////////////////////////////////////////
void OrientedParticle::
write(ostream &out, int indent) const {
  #ifndef NDEBUG //[
  out.width(indent); out<<""; out<<"OrientedParticle:\n";
  BaseParticle::write(out, indent+2);
  #endif //] NDEBUG
}
