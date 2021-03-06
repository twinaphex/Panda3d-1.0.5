// Filename: dcSubatomicType.h
// Created by:  drose (05Oct00)
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

#ifndef DCSUBATOMICTYPE_H
#define DCSUBATOMICTYPE_H

#include "dcbase.h"

BEGIN_PUBLISH
////////////////////////////////////////////////////////////////////
//        Enum : DCSubatomicType
// Description : This defines the numeric type of each element of a
//               DCAtomicField; that is, the particular values that
//               will get added to the message when the atomic field
//               method is called.
////////////////////////////////////////////////////////////////////
enum DCSubatomicType {
  ST_int8,
  ST_int16,
  ST_int32,
  ST_int64,

  ST_uint8,
  ST_uint16,
  ST_uint32,
  ST_uint64,

  ST_float64,

  ST_string,      // a human-printable string
  ST_blob,        // any variable length message, stored as a string
  ST_blob32,      // a blob with a 32-bit length, up to 4.2 GB long
  ST_int16array,
  ST_int32array,
  ST_uint16array,
  ST_uint32array,

  ST_int8array,
  ST_uint8array,

  // A special-purpose array: a list of alternating uint32 and uint8
  // values.  In Python, this becomes a list of 2-tuples.
  ST_uint32uint8array,

  // Equivalent to uint8, except that it suggests a pack_type of
  // PT_string.
  ST_char,

  // New additions should be added at the end to prevent the file hash
  // code from changing.

  ST_invalid
};
END_PUBLISH

ostream &operator << (ostream &out, DCSubatomicType type);

#endif


