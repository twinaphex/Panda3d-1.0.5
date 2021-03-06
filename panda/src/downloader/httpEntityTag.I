// Filename: httpEntityTag.I
// Created by:  drose (28Jan03)
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
//     Function: HTTPEntityTag::Constructor
//       Access: Published
//  Description: 
////////////////////////////////////////////////////////////////////
INLINE HTTPEntityTag::
HTTPEntityTag() {
  _weak = false;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::Constructor
//       Access: Published
//  Description: This constructor accepts an explicit weak flag and a
//               literal (not quoted) tag string.
////////////////////////////////////////////////////////////////////
INLINE HTTPEntityTag::
HTTPEntityTag(bool weak, const string &tag) :
  _weak(weak),
  _tag(tag)
{
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::Copy Constructor
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE HTTPEntityTag::
HTTPEntityTag(const HTTPEntityTag &copy) : 
  _weak(copy._weak),
  _tag(copy._tag)
{
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::Copy Assignment Operator
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void HTTPEntityTag::
operator = (const HTTPEntityTag &copy) {
  _weak = copy._weak;
  _tag = copy._tag;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::is_weak
//       Access: Published
//  Description: Returns true if the entity tag is marked as "weak".
//               A consistent weak entity tag does not guarantee that
//               its resource has not changed in any way, but it does
//               promise that the resource has not changed in any
//               semantically meaningful way.
////////////////////////////////////////////////////////////////////
INLINE bool HTTPEntityTag::
is_weak() const {
  return _weak;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::get_tag
//       Access: Published
//  Description: Returns the tag as a literal string.
////////////////////////////////////////////////////////////////////
INLINE const string &HTTPEntityTag::
get_tag() const {
  return _tag;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::strong_equiv
//       Access: Published
//  Description: Returns true if the two tags have "strong" equivalence:
//               they are the same tag, and both are "strong".
////////////////////////////////////////////////////////////////////
INLINE bool HTTPEntityTag::
strong_equiv(const HTTPEntityTag &other) const {
  return _tag == other._tag && !_weak && !other._weak;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::weak_equiv
//       Access: Published
//  Description: Returns true if the two tags have "weak" equivalence:
//               they are the same tag, and one or both may be "weak".
////////////////////////////////////////////////////////////////////
INLINE bool HTTPEntityTag::
weak_equiv(const HTTPEntityTag &other) const {
  return _tag == other._tag;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::Operator ==
//       Access: Published
//  Description: The == operator tests object equivalence; see also
//               strong_equiv() and weak_equiv() for the two kinds of
//               HTTP equivalence.
////////////////////////////////////////////////////////////////////
INLINE bool HTTPEntityTag::
operator == (const HTTPEntityTag &other) const {
  return _weak == other._weak && _tag == other._tag;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::Operator !=
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE bool HTTPEntityTag::
operator != (const HTTPEntityTag &other) const {
  return !operator == (other);
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::Operator <
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE bool HTTPEntityTag::
operator < (const HTTPEntityTag &other) const {
  if (_weak != other._weak) {
    return (int)_weak < (int)other._weak;
  }
  return _tag < other._tag;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::compare_to
//       Access: Published
//  Description: Returns a number less than zero if this HTTPEntityTag
//               sorts before the other one, greater than zero if it
//               sorts after, or zero if they are equivalent.
////////////////////////////////////////////////////////////////////
INLINE int HTTPEntityTag::
compare_to(const HTTPEntityTag &other) const {
  if (_weak != other._weak) {
    return (int)_weak - (int)other._weak;
  }
  return strcmp(_tag.c_str(), other._tag.c_str());
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPEntityTag::output
//       Access: Published
//  Description: 
////////////////////////////////////////////////////////////////////
INLINE void HTTPEntityTag::
output(ostream &out) const {
  out << get_string();
}


INLINE ostream &
operator << (ostream &out, const HTTPEntityTag &entityTag) {
  entityTag.output(out);
  return out;
}


