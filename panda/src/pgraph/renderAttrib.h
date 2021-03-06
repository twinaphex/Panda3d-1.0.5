// Filename: renderAttrib.h
// Created by:  drose (21Feb02)
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

#ifndef RENDERATTRIB_H
#define RENDERATTRIB_H

#include "pandabase.h"

#include "typedWritableReferenceCount.h"
#include "pointerTo.h"
#include "pset.h"

class GraphicsStateGuardianBase;

////////////////////////////////////////////////////////////////////
//       Class : RenderAttrib
// Description : This is the base class for a number of render
//               attributes (other than transform) that may be set on
//               scene graph nodes to control the appearance of
//               geometry.  This includes TextureAttrib, ColorAttrib,
//               etc.
//
//               RenderAttrib represents render attributes that always
//               propagate down to the leaves without regard to the
//               particular node they are assigned to.  A RenderAttrib
//               will have the same effect on a leaf node whether it
//               is assigned to the graph at the leaf or several nodes
//               above.  This is different from RenderEffect, which
//               represents a particular render property that is
//               applied immediately to the node on which it is
//               encountered, like billboarding or decaling.
//
//               You should not attempt to create or modify a
//               RenderAttrib directly; instead, use the make() method
//               of the appropriate kind of attrib you want.  This
//               will allocate and return a new RenderAttrib of the
//               appropriate type, and it may share pointers if
//               possible.  Do not modify the new RenderAttrib if you
//               wish to change its properties; instead, create a new
//               one.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA RenderAttrib : public TypedWritableReferenceCount {
protected:
  RenderAttrib();
private:
  RenderAttrib(const RenderAttrib &copy);
  void operator = (const RenderAttrib &copy);

public:
  virtual ~RenderAttrib();

  INLINE CPT(RenderAttrib) compose(const RenderAttrib *other) const;
  INLINE CPT(RenderAttrib) invert_compose(const RenderAttrib *other) const;
  INLINE CPT(RenderAttrib) make_default() const;
  virtual void issue(GraphicsStateGuardianBase *gsg) const;

  INLINE bool always_reissue() const;

PUBLISHED:
  INLINE int compare_to(const RenderAttrib &other) const;
  virtual void output(ostream &out) const;
  virtual void write(ostream &out, int indent_level) const;

  static int get_num_attribs();
  static void list_attribs(ostream &out);
  static bool validate_attribs();

  enum PandaCompareFunc {   // intentionally defined to match D3DCMPFUNC
    M_none=0,           // alpha-test disabled (always-draw)
    M_never,            // Never draw.
    M_less,             // incoming < reference_alpha
    M_equal,            // incoming == reference_alpha
    M_less_equal,       // incoming <= reference_alpha
    M_greater,          // incoming > reference_alpha
    M_not_equal,        // incoming != reference_alpha
    M_greater_equal,    // incoming >= reference_alpha
    M_always            // Always draw.  
  };

protected:
  static CPT(RenderAttrib) return_new(RenderAttrib *attrib);
  virtual int compare_to_impl(const RenderAttrib *other) const;
  virtual CPT(RenderAttrib) compose_impl(const RenderAttrib *other) const;
  virtual CPT(RenderAttrib) invert_compose_impl(const RenderAttrib *other) const;
  virtual RenderAttrib *make_default_impl() const=0;
  void output_comparefunc(ostream &out, PandaCompareFunc fn) const;

protected:
  bool _always_reissue;

private:
  typedef pset<const RenderAttrib *, indirect_compare_to<const RenderAttrib *> > Attribs;
  static Attribs *_attribs;

  Attribs::iterator _saved_entry;

public:
  virtual void write_datagram(BamWriter *manager, Datagram &dg);
  static TypedWritable *change_this(TypedWritable *old_ptr, BamReader *manager);
  virtual void finalize();

protected:
  static TypedWritable *new_from_bam(RenderAttrib *attrib, BamReader *manager);
  void fillin(DatagramIterator &scan, BamReader *manager);
  
public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    TypedWritableReferenceCount::init_type();
    register_type(_type_handle, "RenderAttrib",
                  TypedWritableReferenceCount::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;
};

INLINE ostream &operator << (ostream &out, const RenderAttrib &attrib) {
  attrib.output(out);
  return out;
}

#include "renderAttrib.I"

#endif

