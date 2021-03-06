// Filename: eggGroupUniquifier.h
// Created by:  drose (22Feb01)
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

#ifndef EGGGROUPUNIQUIFIER_H
#define EGGGROUPUNIQUIFIER_H

#include "pandabase.h"

#include "eggNameUniquifier.h"

////////////////////////////////////////////////////////////////////
//       Class : EggGroupUniquifier
// Description : This is a specialization of EggNameUniquifier to
//               generate unique names for EggGroup nodes.  It's not
//               called automatically; you must invoke it yourself if
//               you want it.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDAEGG EggGroupUniquifier : public EggNameUniquifier {
PUBLISHED:
  EggGroupUniquifier();

  virtual string get_category(EggNode *node);
  virtual string filter_name(EggNode *node);
  virtual string generate_name(EggNode *node,
                               const string &category, int index);

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    EggNameUniquifier::init_type();
    register_type(_type_handle, "EggGroupUniquifier",
                  EggNameUniquifier::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;

};

#endif


