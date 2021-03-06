// Filename: httpDate.I
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
//     Function: HTTPDate::Constructor
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE HTTPDate::
HTTPDate() : _time(-1) {
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::Constructor
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE HTTPDate::
HTTPDate(time_t time) : _time(time) {
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::Copy Constructor
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE HTTPDate::
HTTPDate(const HTTPDate &copy) : _time(copy._time) {
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::Copy Assignment Operator
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void HTTPDate::
operator = (const HTTPDate &copy) {
  _time = copy._time;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::now (named constructor)
//       Access: Published, Static
//  Description: Returns an HTTPDate that represents the current time
//               and date.
////////////////////////////////////////////////////////////////////
INLINE HTTPDate HTTPDate::
now() {
  return HTTPDate(time(NULL));
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::is_valid
//       Access: Published
//  Description: Returns true if the date is meaningful, or false if
//               it is -1 (which generally indicates the source string
//               could not be parsed.)
////////////////////////////////////////////////////////////////////
INLINE bool HTTPDate::
is_valid() const {
  return (_time != (time_t)(-1));
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::get_time
//       Access: Published
//  Description: Returns the date as a C time_t value.
////////////////////////////////////////////////////////////////////
INLINE time_t HTTPDate::
get_time() const {
  return _time;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::Operator ==
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE bool HTTPDate::
operator == (const HTTPDate &other) const {
  return _time == other._time;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::Operator !=
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE bool HTTPDate::
operator != (const HTTPDate &other) const {
  return !operator == (other);
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::Operator <
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE bool HTTPDate::
operator < (const HTTPDate &other) const {
  return _time < other._time;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::Operator >
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE bool HTTPDate::
operator > (const HTTPDate &other) const {
  return _time > other._time;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::compare_to
//       Access: Published
//  Description: Returns a number less than zero if this HTTPDate
//               sorts before the other one, greater than zero if it
//               sorts after, or zero if they are equivalent.
////////////////////////////////////////////////////////////////////
INLINE int HTTPDate::
compare_to(const HTTPDate &other) const {
  return (int)(_time - other._time);
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::operator +=
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void HTTPDate::
operator += (int seconds) {
  _time += seconds;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::operator -=
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void HTTPDate::
operator -= (int seconds) {
  _time -= seconds;
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::operator +
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE HTTPDate HTTPDate::
operator + (int seconds) const {
  return HTTPDate(_time + seconds);
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::operator -
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE HTTPDate HTTPDate::
operator - (int seconds) const {
  return HTTPDate(_time - seconds);
}

////////////////////////////////////////////////////////////////////
//     Function: HTTPDate::operator -
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE int HTTPDate::
operator - (const HTTPDate &other) const {
  return (int)(_time - other._time);
}


INLINE istream &
operator >> (istream &in, HTTPDate &date) {
  if (!date.input(in)) {
    in.clear(ios::failbit | in.rdstate());
  }
  return in;
}

INLINE ostream &
operator << (ostream &out, const HTTPDate &date) {
  date.output(out);
  return out;
}


