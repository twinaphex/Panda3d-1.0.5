// Filename: memoryUsagePointers.h
// Created by:  drose (25May00)
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

#ifndef MEMORYUSAGEPOINTERS_H
#define MEMORYUSAGEPOINTERS_H

#include "pandabase.h"

#ifdef DO_MEMORY_USAGE

#include "typedObject.h"
#include "pointerTo.h"
#include "referenceCount.h"
#include "pvector.h"

////////////////////////////////////////////////////////////////////
//       Class : MemoryUsagePointers
// Description : This is a list of pointers returned by a MemoryUsage
//               object in response to some query.
//
//               Warning: once pointers are stored in a
//               MemoryUsagePointers object, they are
//               reference-counted, and will not be freed until the
//               MemoryUsagePointers object is freed (or clear() is
//               called on the object).  However, they may not even be
//               freed then; pointers may leak once they have been
//               added to this structure.  This is because we don't
//               store enough information in this structure to
//               correctly free the pointers that have been added.
//               Since this is intended primarily as a debugging tool,
//               this is not a major issue.
//
//               This class is just a user interface to talk about
//               pointers stored in a MemoryUsage object.  It doesn't
//               even exist when compiled with NDEBUG.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDAEXPRESS MemoryUsagePointers {
PUBLISHED:
  MemoryUsagePointers();
  ~MemoryUsagePointers();

  int get_num_pointers() const;
  ReferenceCount *get_pointer(int n) const;
  TypedObject *get_typed_pointer(int n) const;
  TypeHandle get_type(int n) const;
  string get_type_name(int n) const;
  double get_age(int n) const;

  void clear();

private:
  void add_entry(ReferenceCount *ref_ptr, TypedObject *typed_ptr,
                 TypeHandle type, double age);

  class Entry {
  public:
    INLINE Entry(ReferenceCount *ref_ptr, TypedObject *typed_ptr,
                 TypeHandle type, double age);
    INLINE Entry(const Entry &copy);
    INLINE void operator = (const Entry &copy);
    INLINE ~Entry();

    // We have an ordinary pointer to a type ReferenceCount, and not a
    // PT(ReferenceCount), because we can't actually delete this thing
    // (since ReferenceCount has no public destructor).  If we can't
    // delete it, we can't make a PointerTo it, since PointerTo wants
    // to be able to delete things.
    ReferenceCount *_ref_ptr;
    TypedObject *_typed_ptr;
    TypeHandle _type;
    double _age;
  };

  typedef pvector<Entry> Entries;
  Entries _entries;
  friend class MemoryUsage;
};

#include "memoryUsagePointers.I"

#endif  // MEMORY_USAGE_POINTERS

#endif
