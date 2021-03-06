// Filename: eggComponentData.cxx
// Created by:  drose (26Feb01)
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

#include "eggComponentData.h"
#include "eggBackPointer.h"

#include "indent.h"

TypeHandle EggComponentData::_type_handle;


////////////////////////////////////////////////////////////////////
//     Function: EggComponentData::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
EggComponentData::
EggComponentData(EggCharacterCollection *collection,
                 EggCharacterData *char_data) :
  _collection(collection),
  _char_data(char_data)
{
}

////////////////////////////////////////////////////////////////////
//     Function: EggComponentData::Destructor
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
EggComponentData::
~EggComponentData() {
  BackPointers::iterator bpi;
  for (bpi = _back_pointers.begin(); bpi != _back_pointers.end(); ++bpi) {
    EggBackPointer *back = (*bpi);
    if (back != (EggBackPointer *)NULL) {
      delete back;
    }
  }
}

////////////////////////////////////////////////////////////////////
//     Function: EggComponentData::add_name
//       Access: Public
//  Description: Adds the indicated name to the set of names that this
//               component can be identified with.  If this is the
//               first name added, it becomes the primary name of the
//               component; later names added do not replace the
//               primary name, but do get added to the list of names
//               that will be accepted by matched_name().
////////////////////////////////////////////////////////////////////
void EggComponentData::
add_name(const string &name, NameUniquifier &uniquifier) {
  if (_names.insert(name).second) {
    // This is a new name for this component.
    if (!has_name()) {
      set_name(uniquifier.add_name(name));
      if (get_name() != name) {
        nout << "Warning: renamed " << name << " to " << get_name()
             << " to avoid naming conflict.\n";
      }
    }
  }
}

////////////////////////////////////////////////////////////////////
//     Function: EggComponentData::matches_name
//       Access: Public
//  Description: Returns true if the indicated name matches any name
//               that was ever matched with this particular joint,
//               false otherwise.
////////////////////////////////////////////////////////////////////
bool EggComponentData::
matches_name(const string &name) const {
  if (name == get_name()) {
    return true;
  }
  return (_names.find(name) != _names.end());
}

////////////////////////////////////////////////////////////////////
//     Function: EggComponentData::get_num_frames
//       Access: Public, Virtual
//  Description: Returns the number of frames of animation for this
//               particular component in the indicated model.
////////////////////////////////////////////////////////////////////
int EggComponentData::
get_num_frames(int model_index) const {
  EggBackPointer *back = get_model(model_index);
  if (back == (EggBackPointer *)NULL) {
    return 0;
  }
  return back->get_num_frames();
}

////////////////////////////////////////////////////////////////////
//     Function: EggComponentData::extend_to
//       Access: Public, Virtual
//  Description: Extends the number of frames in the indicated model
//               (presumably an animation table model) to the given
//               number.
////////////////////////////////////////////////////////////////////
void EggComponentData::
extend_to(int model_index, int num_frames) const {
  EggBackPointer *back = get_model(model_index);
  nassertv(back != (EggBackPointer *)NULL);
  back->extend_to(num_frames);
}

////////////////////////////////////////////////////////////////////
//     Function: EggComponentData::set_model
//       Access: Public
//  Description: Sets the back_pointer associated with the given
//               model_index.
////////////////////////////////////////////////////////////////////
void EggComponentData::
set_model(int model_index, EggBackPointer *back) {
  while ((int)_back_pointers.size() <= model_index) {
    _back_pointers.push_back((EggBackPointer *)NULL);
  }

  if (_back_pointers[model_index] != (EggBackPointer *)NULL) {
    nout << "Warning: deleting old back pointer.\n";
    delete _back_pointers[model_index];
  }
  _back_pointers[model_index] = back;
}
