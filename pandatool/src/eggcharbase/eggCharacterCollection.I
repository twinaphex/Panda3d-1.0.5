// Filename: eggCharacterCollection.I
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


////////////////////////////////////////////////////////////////////
//     Function: EggCharacterCollection::get_num_eggs
//       Access: Public
//  Description: Returns the number of egg files that have
//               successfully been added to the Character table.
////////////////////////////////////////////////////////////////////
INLINE int EggCharacterCollection::
get_num_eggs() const {
  return _eggs.size();
}

////////////////////////////////////////////////////////////////////
//     Function: EggCharacterCollection::get_egg
//       Access: Public
//  Description: Returns the ith egg file.
////////////////////////////////////////////////////////////////////
INLINE EggData *EggCharacterCollection::
get_egg(int i) const {
  nassertr(i >= 0 && i < (int)_eggs.size(), (EggData *)NULL);
  return _eggs[i]._egg;
}

////////////////////////////////////////////////////////////////////
//     Function: EggCharacterCollection::get_first_model_index
//       Access: Public
//  Description: Returns the first model index associated with the
//               indicated egg file.  An egg file may contain multiple
//               models, which will be consecutive integers beginning
//               at get_first_model_index() and continuing for
//               get_num_models().
//
//               Each "model" corresponds to a single character model,
//               or one LOD of a multiple-LOD model, or a single
//               animation bundle.
////////////////////////////////////////////////////////////////////
INLINE int EggCharacterCollection::
get_first_model_index(int egg_index) const {
  nassertr(egg_index >= 0 && egg_index < (int)_eggs.size(), 0);
  return _eggs[egg_index]._first_model_index;
}

////////////////////////////////////////////////////////////////////
//     Function: EggCharacterCollection::get_num_models
//       Access: Public
//  Description: Returns the number of different models found in the
//               indicated egg file.  An egg file may contain multiple
//               models, which will be consecutive integers beginning
//               at get_first_model_index() and continuing for
//               get_num_models().
//
//               Each "model" corresponds to a single character model,
//               or one LOD of a multiple-LOD model, or a single
//               animation bundle.
////////////////////////////////////////////////////////////////////
INLINE int EggCharacterCollection::
get_num_models(int egg_index) const {
  nassertr(egg_index >= 0 && egg_index < (int)_eggs.size(), 0);
  return _eggs[egg_index]._models.size();
}

////////////////////////////////////////////////////////////////////
//     Function: EggCharacterCollection::get_num_characters
//       Access: Public
//  Description: Returns the number of separate Characters that have
//               been discovered in the various egg files added to the
//               collection.
////////////////////////////////////////////////////////////////////
INLINE int EggCharacterCollection::
get_num_characters() const {
  return _characters.size();
}

////////////////////////////////////////////////////////////////////
//     Function: EggCharacterCollection::get_character
//       Access: Public
//  Description: Returns the ith character in the collection.
////////////////////////////////////////////////////////////////////
INLINE EggCharacterData *EggCharacterCollection::
get_character(int i) const {
  nassertr(i >= 0 && i < (int)_characters.size(), (EggCharacterData *)NULL);
  return _characters[i];
}

////////////////////////////////////////////////////////////////////
//     Function: EggCharacterCollection::get_character_by_model_index
//       Access: Public
//  Description: Returns the character associated with the indicated
//               model index.
////////////////////////////////////////////////////////////////////
INLINE EggCharacterData *EggCharacterCollection::
get_character_by_model_index(int model_index) const {
  nassertr(model_index >= 0 && model_index < (int)_characters_by_model_index.size(),
           (EggCharacterData *)NULL);
  return _characters_by_model_index[model_index];
}

////////////////////////////////////////////////////////////////////
//     Function: EggCharacterCollection::ModelDescription::Constructor
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
INLINE EggCharacterCollection::ModelDescription::
ModelDescription() {
  _root_node = (EggObject *)NULL;
}
