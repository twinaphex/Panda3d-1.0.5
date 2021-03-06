// Filename: cLerpNodePathInterval.h
// Created by:  drose (27Aug02)
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

#ifndef CLERPNODEPATHINTERVAL_H
#define CLERPNODEPATHINTERVAL_H

#include "directbase.h"
#include "cLerpInterval.h"
#include "nodePath.h"

////////////////////////////////////////////////////////////////////
//       Class : CLerpNodePathInterval
// Description : An interval that lerps one or more properties (like
//               pos, hpr, etc.) on a NodePath over time.
////////////////////////////////////////////////////////////////////
class EXPCL_DIRECT CLerpNodePathInterval : public CLerpInterval {
PUBLISHED:
  CLerpNodePathInterval(const string &name, double duration, 
                        BlendType blend_type, bool bake_in_start,
                        bool fluid,
                        const NodePath &node, const NodePath &other);

  INLINE const NodePath &get_node() const;
  INLINE const NodePath &get_other() const;

  INLINE void set_start_pos(const LVecBase3f &pos);
  INLINE void set_end_pos(const LVecBase3f &pos);
  INLINE void set_start_hpr(const LVecBase3f &hpr);
  INLINE void set_end_hpr(const LVecBase3f &hpr);
  INLINE void set_end_hpr(const LQuaternionf &quat);
  INLINE void set_start_quat(const LQuaternionf &quat);
  INLINE void set_end_quat(const LVecBase3f &hpr);
  INLINE void set_end_quat(const LQuaternionf &quat);
  INLINE void set_start_scale(const LVecBase3f &scale);
  INLINE void set_start_scale(float scale);
  INLINE void set_end_scale(const LVecBase3f &scale);
  INLINE void set_end_scale(float scale);
  INLINE void set_start_shear(const LVecBase3f &shear);
  INLINE void set_end_shear(const LVecBase3f &shear);
  INLINE void set_start_color(const LVecBase4f &color);
  INLINE void set_end_color(const LVecBase4f &color);
  INLINE void set_start_color_scale(const LVecBase4f &color_scale);
  INLINE void set_end_color_scale(const LVecBase4f &color_scale);

  virtual void priv_initialize(double t);
  virtual void priv_instant();
  virtual void priv_step(double t);
  virtual void priv_reverse_initialize(double t);
  virtual void priv_reverse_instant();

  virtual void output(ostream &out) const;

private:
  void setup_slerp();

  NodePath _node;
  NodePath _other;

  enum Flags {
    F_end_pos            = 0x000001,
    F_end_hpr            = 0x000002,
    F_end_quat           = 0x000004,
    F_end_scale          = 0x000008,
    F_end_color          = 0x000010,
    F_end_color_scale    = 0x000020,
    F_end_shear          = 0x000040,

    F_start_pos          = 0x000080,
    F_start_hpr          = 0x000100,
    F_start_quat         = 0x000200,
    F_start_scale        = 0x000400,
    F_start_color        = 0x000800,
    F_start_color_scale  = 0x001000,
    F_start_shear        = 0x002000,

    F_fluid              = 0x004000,
    F_bake_in_start      = 0x008000,
    
    F_slerp_setup        = 0x010000,
  };
  
  unsigned int _flags;
  LPoint3f _start_pos, _end_pos;
  LVecBase3f _start_hpr, _end_hpr;
  LQuaternionf _start_quat, _end_quat;
  LVecBase3f _start_scale, _end_scale;
  LVecBase3f _start_shear, _end_shear;
  Colorf _start_color, _end_color;
  LVecBase4f _start_color_scale, _end_color_scale;

  double _prev_d;
  float _slerp_angle;
  float _slerp_denom;
  LQuaternionf _slerp_c;

  void slerp_basic(LQuaternionf &result, float t) const;
  void slerp_angle_0(LQuaternionf &result, float t) const;
  void slerp_angle_180(LQuaternionf &result, float t) const;

  // Define a pointer to one of the above three methods.
  void (CLerpNodePathInterval::*_slerp)(LQuaternionf &result, float t) const;
  
public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    CLerpInterval::init_type();
    register_type(_type_handle, "CLerpNodePathInterval",
                  CLerpInterval::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;
};

#include "cLerpNodePathInterval.I"

#endif

