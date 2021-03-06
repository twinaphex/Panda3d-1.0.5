// Filename: ramfile.cxx
// Created by:  mike (09Jan97)
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

#include "ramfile.h"

////////////////////////////////////////////////////////////////////
//     Function: Ramfile::read
//       Access: Published
//  Description: Extracts and returns the indicated number of
//               characters from the current data pointer, and
//               advances the data pointer.  If the data pointer
//               exceeds the end of the buffer, returns empty string.
//
//               The interface here is intentionally designed to be
//               similar to that for Python's file.read() function.
////////////////////////////////////////////////////////////////////
string Ramfile::
read(size_t length) {
  size_t orig_pos = _pos;
  _pos = min(_pos + length, _data.length());
  return _data.substr(orig_pos, length);
}

////////////////////////////////////////////////////////////////////
//     Function: Ramfile::readline
//       Access: Published
//  Description: Assumes the stream represents a text file, and
//               extracts one line up to and including the trailing
//               newline character.  Returns empty string when the end
//               of file is reached.
//
//               The interface here is intentionally designed to be
//               similar to that for Python's file.readline()
//               function.
////////////////////////////////////////////////////////////////////
string Ramfile::
readline() {
  size_t start = _pos;
  while (_pos < _data.length() && _data[_pos] != '\n') {
    ++_pos;
  }

  if (_pos < _data.length() && _data[_pos] == '\n') {
    // Include the newline character also.
    ++_pos;
  }

  return _data.substr(start, _pos - start);
}

