// Filename: linearFrictionForce.h
// Created by:  charles (23Jun00)
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

#ifndef LINEARFRICTIONFORCE_H
#define LINEARFRICTIONFORCE_H

#include "linearForce.h"

////////////////////////////////////////////////////////////////////
//       Class : LinearFrictionForce
// Description : Friction-based drag force
////////////////////////////////////////////////////////////////////
class EXPCL_PANDAPHYSICS LinearFrictionForce : public LinearForce {
PUBLISHED:
  LinearFrictionForce(float coef = 1.0f, float a = 1.0f, bool m = false);
  LinearFrictionForce(const LinearFrictionForce &copy);
  virtual ~LinearFrictionForce();

  INLINE void set_coef(float coef);
  INLINE float get_coef() const;
  
  virtual void output(ostream &out) const;
  virtual void write(ostream &out, unsigned int indent=0) const;

private:
  float _coef;

  virtual LinearForce *make_copy();
  virtual LVector3f get_child_vector(const PhysicsObject *);

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    LinearForce::init_type();
    register_type(_type_handle, "LinearFrictionForce",
                  LinearForce::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;
};

#include "linearFrictionForce.I"

#endif // LINEARFRICTIONFORCE_H
