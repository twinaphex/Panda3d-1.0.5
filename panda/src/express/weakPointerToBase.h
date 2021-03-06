// Filename: weakPointerToBase.h
// Created by:  drose (27Sep04)
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

#ifndef WEAKPOINTERTOBASE_H
#define WEAKPOINTERTOBASE_H

#include "pandabase.h"
#include "pointerToBase.h"
#include "weakPointerToVoid.h"

////////////////////////////////////////////////////////////////////
//       Class : WeakPointerToBase
// Description : This is the base class for PointerTo and
//               ConstPointerTo.  Don't try to use it directly; use
//               either derived class instead.
////////////////////////////////////////////////////////////////////
template <class T>
class WeakPointerToBase : public WeakPointerToVoid {
public:
  typedef T To;

protected:
  INLINE WeakPointerToBase(To *ptr);
  INLINE WeakPointerToBase(const PointerToBase<T> &copy);
  INLINE WeakPointerToBase(const WeakPointerToBase<T> &copy);
  INLINE ~WeakPointerToBase();

  void reassign(To *ptr);
  INLINE void reassign(const PointerToBase<To> &copy);
  INLINE void reassign(const WeakPointerToBase<To> &copy);

  // No assignment or retrieval functions are declared in
  // WeakPointerToBase, because we will have to specialize on const
  // vs. non-const later.

public:
  // These comparison functions are common to all things PointerTo, so
  // they're defined up here.
#ifndef CPPPARSER
#ifndef WIN32_VC
  INLINE bool operator == (const To *other) const;
  INLINE bool operator != (const To *other) const;
  INLINE bool operator > (const To *other) const;
  INLINE bool operator <= (const To *other) const;
  INLINE bool operator >= (const To *other) const;
  INLINE bool operator == (To *other) const;
  INLINE bool operator != (To *other) const;
  INLINE bool operator > (To *other) const;
  INLINE bool operator <= (To *other) const;
  INLINE bool operator >= (To *other) const;

  INLINE bool operator == (const WeakPointerToBase<To> &other) const;
  INLINE bool operator != (const WeakPointerToBase<To> &other) const;
  INLINE bool operator > (const WeakPointerToBase<To> &other) const;
  INLINE bool operator <= (const WeakPointerToBase<To> &other) const;
  INLINE bool operator >= (const WeakPointerToBase<To> &other) const;

  INLINE bool operator == (const PointerToBase<To> &other) const;
  INLINE bool operator != (const PointerToBase<To> &other) const;
  INLINE bool operator > (const PointerToBase<To> &other) const;
  INLINE bool operator <= (const PointerToBase<To> &other) const;
  INLINE bool operator >= (const PointerToBase<To> &other) const;
#endif  // WIN32_VC
  INLINE bool operator < (const To *other) const;
  INLINE bool operator < (const WeakPointerToBase<To> &other) const;
  INLINE bool operator < (const PointerToBase<To> &other) const;
#endif  // CPPPARSER

PUBLISHED:
  INLINE bool is_null() const;
  INLINE void clear();

  void output(ostream &out) const;
};

template<class T>
INLINE ostream &operator <<(ostream &out, const WeakPointerToBase<T> &pointer) {
  pointer.output(out);
  return out;
}

#include "weakPointerToBase.I"

#endif
