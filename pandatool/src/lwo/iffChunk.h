// Filename: iffChunk.h
// Created by:  drose (23Apr01)
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

#ifndef IFFCHUNK_H
#define IFFCHUNK_H

#include "pandatoolbase.h"

#include "iffId.h"

#include "typedObject.h"
#include "typedReferenceCount.h"

class IffInputFile;

////////////////////////////////////////////////////////////////////
//       Class : IffChunk
// Description : The basic kind of record in an EA "IFF" file, which
//               the LightWave object file is based on.
////////////////////////////////////////////////////////////////////
class IffChunk : public TypedReferenceCount {
public:
  INLINE IffChunk();

  INLINE IffId get_id() const;
  INLINE void set_id(IffId id);

  virtual bool read_iff(IffInputFile *in, size_t stop_at)=0;

  virtual void output(ostream &out) const;
  virtual void write(ostream &out, int indent_level = 0) const;

  virtual IffChunk *make_new_chunk(IffInputFile *in, IffId id);

private:
  IffId _id;

public:
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    TypedReferenceCount::init_type();
    register_type(_type_handle, "IffChunk",
                  TypedReferenceCount::get_class_type());
  }

private:
  static TypeHandle _type_handle;
};

#include "iffChunk.I"

INLINE ostream &operator << (ostream &out, const IffChunk &chunk) {
  chunk.output(out);
  return out;
}

#endif


