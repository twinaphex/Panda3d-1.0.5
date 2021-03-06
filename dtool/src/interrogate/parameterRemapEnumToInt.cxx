// Filename: parameterRemapEnumToInt.cxx
// Created by:  drose (04Aug00)
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

#include "parameterRemapEnumToInt.h"
#include "interrogate.h"

#include "cppSimpleType.h"
#include "cppConstType.h"
#include "cppPointerType.h"
#include "cppReferenceType.h"

////////////////////////////////////////////////////////////////////
//     Function: ParameterRemapEnumToInt::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
ParameterRemapEnumToInt::
ParameterRemapEnumToInt(CPPType *orig_type) :
  ParameterRemap(orig_type)
{
  _new_type = CPPType::new_type(new CPPSimpleType(CPPSimpleType::T_int));
  _enum_type = unwrap_type(_orig_type);
}

////////////////////////////////////////////////////////////////////
//     Function: ParameterRemapEnumToInt::pass_parameter
//       Access: Public, Virtual
//  Description: Outputs an expression that converts the indicated
//               variable from the new type to the original type, for
//               passing into the actual C++ function.
////////////////////////////////////////////////////////////////////
void ParameterRemapEnumToInt::
pass_parameter(ostream &out, const string &variable_name) {
  out << "(" << _enum_type->get_local_name(&parser) << ")" << variable_name;
}

////////////////////////////////////////////////////////////////////
//     Function: ParameterRemapEnumToInt::get_return_expr
//       Access: Public, Virtual
//  Description: Returns an expression that evalutes to the
//               appropriate value type for returning from the
//               function, given an expression of the original type.
////////////////////////////////////////////////////////////////////
string ParameterRemapEnumToInt::
get_return_expr(const string &expression) {
  return "(int)(" + expression + ")";
}

////////////////////////////////////////////////////////////////////
//     Function: ParameterRemapEnumToInt::unwrap_type
//       Access: Private
//  Description: Recursively walks through the type definition,
//               and finds the enum definition under all the wrappers.
////////////////////////////////////////////////////////////////////
CPPType *ParameterRemapEnumToInt::
unwrap_type(CPPType *source_type) const {
  switch (source_type->get_subtype()) {
  case CPPDeclaration::ST_const:
    return unwrap_type(source_type->as_const_type()->_wrapped_around);

  case CPPDeclaration::ST_reference:
    return unwrap_type(source_type->as_reference_type()->_pointing_at);

  case CPPDeclaration::ST_pointer:
    return unwrap_type(source_type->as_pointer_type()->_pointing_at);

  default:
    return source_type;
  }
}
