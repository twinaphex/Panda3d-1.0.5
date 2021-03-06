// Filename: cLwoClip.cxx
// Created by:  drose (27Apr01)
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

#include "cLwoClip.h"
#include "lwoToEggConverter.h"

#include "lwoClip.h"
#include "lwoStillImage.h"
#include "dcast.h"


////////////////////////////////////////////////////////////////////
//     Function: CLwoClip::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
CLwoClip::
CLwoClip(LwoToEggConverter *converter, const LwoClip *clip) :
  _converter(converter),
  _clip(clip)
{
  _still_image = false;

  // Walk through the chunk list, looking for some basic properties.
  int num_chunks = _clip->get_num_chunks();
  for (int i = 0; i < num_chunks; i++) {
    const IffChunk *chunk = _clip->get_chunk(i);

    if (chunk->is_of_type(LwoStillImage::get_class_type())) {
      const LwoStillImage *image = DCAST(LwoStillImage, chunk);
      _filename = image->_filename;
      _still_image = true;
    }
  }
}
