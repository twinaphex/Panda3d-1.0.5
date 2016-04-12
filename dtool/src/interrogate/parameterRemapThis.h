// Filename: parameterRemapThis.h
// Created by:  drose (02Aug00)
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

#ifndef PARAMETERREMAPTHIS_H
#define PARAMETERREMAPTHIS_H

#include "dtoolbase.h"

#include "parameterRemap.h"

class CPPType;

////////////////////////////////////////////////////////////////////
//       Class : ParameterRemapThis
// Description : A ParameterRemap class that represents a generated
//               "this" parameter.
////////////////////////////////////////////////////////////////////
class ParameterRemapThis : public ParameterRemap {
public:
  ParameterRemapThis(CPPType *type, bool is_const);

  virtual void pass_parameter(ostream &out, const string &variable_name);
  virtual string get_return_expr(const string &expression);
  virtual bool is_this();
};

#endif