// Filename: fltMeshPrimitive.h
// Created by:  drose (28Feb01)
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

#ifndef FLTMESHPRIMITIVE_H
#define FLTMESHPRIMITIVE_H

#include "pandatoolbase.h"

#include "fltBead.h"
#include "fltHeader.h"

#include "luse.h"
#include "vector_int.h"

////////////////////////////////////////////////////////////////////
//       Class : FltMeshPrimitive
// Description : A single primitive of a mesh, like a triangle strip
//               or fan.
////////////////////////////////////////////////////////////////////
class FltMeshPrimitive : public FltBead {
public:
  FltMeshPrimitive(FltHeader *header);

  enum PrimitiveType {
    PT_tristrip            = 1,
    PT_trifan              = 2,
    PT_quadstrip           = 3,
    PT_polygon             = 4,
  };

  typedef vector_int Vertices;

  PrimitiveType _primitive_type;
  Vertices _vertices;


protected:
  virtual bool extract_record(FltRecordReader &reader);
  virtual bool build_record(FltRecordWriter &writer) const;

public:
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    FltBead::init_type();
    register_type(_type_handle, "FltMeshPrimitive",
                  FltBead::get_class_type());
  }

private:
  static TypeHandle _type_handle;
};

#include "fltMeshPrimitive.I"

#endif


