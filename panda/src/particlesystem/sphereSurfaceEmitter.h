// Filename: sphereSurfaceEmitter.h
// Created by:  charles (22Jun00)
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

#ifndef SPHERESURFACEEMITTER_H
#define SPHERESURFACEEMITTER_H

#include "baseParticleEmitter.h"

////////////////////////////////////////////////////////////////////
//       Class : SphereSurfaceEmitter
// Description : Describes a curved space in which
//               particles are generated.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDAPHYSICS SphereSurfaceEmitter : public BaseParticleEmitter {
PUBLISHED:
  SphereSurfaceEmitter();
  SphereSurfaceEmitter(const SphereSurfaceEmitter &copy);
  virtual ~SphereSurfaceEmitter();

  virtual BaseParticleEmitter *make_copy();

  INLINE void set_radius(float r);
  INLINE float get_radius() const;

  virtual void output(ostream &out) const;
  virtual void write(ostream &out, int indent=0) const;

private:
  float _radius;

  // CUSTOM EMISSION PARAMETERS
  // none

  virtual void assign_initial_position(LPoint3f& pos);
  virtual void assign_initial_velocity(LVector3f& vel);
};

#include "sphereSurfaceEmitter.I"

#endif // SPHERESURFACEEMITTER_H
