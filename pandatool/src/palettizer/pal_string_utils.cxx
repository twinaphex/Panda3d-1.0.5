// Filename: pal_string_utils.cxx
// Created by:  drose (30Nov00)
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

#include "pal_string_utils.h"

#include "pnmFileType.h"
#include "pnmFileTypeRegistry.h"


// Extracts the first word of the string into param, and the remainder
// of the line into value.
void
extract_param_value(const string &str, string &param, string &value) {
  size_t i = 0;

  // First, skip all whitespace at the beginning.
  while (i < str.length() && isspace(str[i])) {
    i++;
  }

  size_t start = i;

  // Now skip to the end of the whitespace.
  while (i < str.length() && !isspace(str[i])) {
    i++;
  }

  size_t end = i;

  param = str.substr(start, end - start);

  // Skip a little bit further to the start of the value.
  while (i < str.length() && isspace(str[i])) {
    i++;
  }
  value = trim_right(str.substr(i));
}


bool
parse_image_type_request(const string &word, PNMFileType *&color_type,
                         PNMFileType *&alpha_type) {
  PNMFileTypeRegistry *registry = PNMFileTypeRegistry::get_global_ptr();
  color_type = (PNMFileType *)NULL;
  alpha_type = (PNMFileType *)NULL;

  string color_name = word;
  string alpha_name;
  size_t comma = word.find(',');
  if (comma != string::npos) {
    // If we have a comma in the image_type, it's two types: a color
    // type and an alpha type.
    color_name = word.substr(0, comma);
    alpha_name = word.substr(comma + 1);
  }

  if (!color_name.empty()) {
    color_type = registry->get_type_from_extension(color_name);
    if (color_type == (PNMFileType *)NULL) {
      nout << "Image file type '" << color_name << "' is unknown.\n";
      return false;
    }
  }

  if (!alpha_name.empty()) {
    alpha_type = registry->get_type_from_extension(alpha_name);
    if (alpha_type == (PNMFileType *)NULL) {
      nout << "Image file type '" << alpha_name << "' is unknown.\n";
      return false;
    }
  }

  return true;
}


