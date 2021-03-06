// Filename: lerp_helpers.h
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

#ifndef LERP_HELPERS_H
#define LERP_HELPERS_H

#include "directbase.h"

//
// This header file is only included within .cxx files in this
// directory.
//

//
// The functions defined here include some trivial template functions
// for handling basic lerp computations, common to several .cxx files
// here.
//

////////////////////////////////////////////////////////////////////
//     Function: lerp_value
//  Description: Applies the linear lerp computation for a single
//               parameter.
////////////////////////////////////////////////////////////////////
template<class NumericType>
INLINE void
lerp_value(NumericType &current_value,
           double d,
           const NumericType &starting_value,
           const NumericType &ending_value) {
  current_value = starting_value + d * (ending_value - starting_value);
}

////////////////////////////////////////////////////////////////////
//     Function: lerp_value_from_prev
//  Description: Applies the linear lerp computation for a single
//               parameter, when the starting value is implicit.
//
//               This computes the new value based on assuming the
//               prev_value represents the value computed at delta
//               prev_d.
////////////////////////////////////////////////////////////////////
template<class NumericType>
INLINE void
lerp_value_from_prev(NumericType &current_value,
                     double d, double prev_d,
                     const NumericType &prev_value,
                     const NumericType &ending_value) {
  if (prev_d == 1.0) {
    current_value = ending_value;
  } else {
    NumericType starting_value = 
      (prev_value - prev_d * ending_value) / (1.0 - prev_d);
    current_value = starting_value + d * (ending_value - starting_value);
  }
}


#endif

