// Filename: eggJointData.I
// Created by:  drose (23Feb01)
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
//     Function: EggJointData::get_parent
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggJointData *EggJointData::
get_parent() const {
  return _parent;
}

////////////////////////////////////////////////////////////////////
//     Function: EggJointData::get_num_children
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
INLINE int EggJointData::
get_num_children() const {
  return _children.size();
}

////////////////////////////////////////////////////////////////////
//     Function: EggJointData::get_child
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggJointData *EggJointData::
get_child(int n) const {
  nassertr(n >= 0 && n < (int)_children.size(), (EggJointData *)NULL);
  return _children[n];
}

////////////////////////////////////////////////////////////////////
//     Function: EggJointData::find_joint
//       Access: Public
//  Description: Returns the first descendent joint found with the
//               indicated name, or NULL if no joint has that name.
////////////////////////////////////////////////////////////////////
INLINE EggJointData *EggJointData::
find_joint(const string &name) {
  EggJointData *joint = find_joint_exact(name);
  if (joint == (EggJointData *)NULL) {
    joint = find_joint_matches(name);
  }
  return joint;
}


////////////////////////////////////////////////////////////////////
//     Function: EggJointData::has_rest_frame
//       Access: Public
//  Description: Returns true if the joint knows its rest frame, false
//               otherwise.  In general, this will be true as long as
//               the joint is included in at least one model file, or
//               false if it appears only in animation files.
////////////////////////////////////////////////////////////////////
INLINE bool EggJointData::
has_rest_frame() const {
  return _has_rest_frame;
}

////////////////////////////////////////////////////////////////////
//     Function: EggJointData::rest_frames_differ
//       Access: Public
//  Description: Returns true if the rest frames for different models
//               differ in their initial value.  This is not
//               technically an error, but it is unusual enough to be
//               suspicious.
////////////////////////////////////////////////////////////////////
INLINE bool EggJointData::
rest_frames_differ() const {
  return _rest_frames_differ;
}

////////////////////////////////////////////////////////////////////
//     Function: EggJointData::get_rest_frame
//       Access: Public
//  Description: Returns the rest frame of the joint.  This is the
//               matrix value that appears for the joint in each model
//               file; it should be the same transform in each model.
////////////////////////////////////////////////////////////////////
INLINE const LMatrix4d &EggJointData::
get_rest_frame() const {
  nassertr(has_rest_frame(), LMatrix4d::ident_mat());
  return _rest_frame;
}

////////////////////////////////////////////////////////////////////
//     Function: EggJointData::reparent_to
//       Access: Public
//  Description: Indicates an intention to change the parent of this
//               joint to the indicated joint, or NULL to remove it
//               from the hierarchy.  The joint is not reparented
//               immediately, but rather all of the joints are
//               reparented at once when do_reparent() is called.
////////////////////////////////////////////////////////////////////
INLINE void EggJointData::
reparent_to(EggJointData *new_parent) {
  _new_parent = new_parent;
}
