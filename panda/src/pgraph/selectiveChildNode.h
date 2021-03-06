// Filename: selectiveChildNode.h
// Created by:  drose (06Mar02)
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

#ifndef SELECTIVECHILDNODE_H
#define SELECTIVECHILDNODE_H

#include "pandabase.h"

#include "pandaNode.h"

////////////////////////////////////////////////////////////////////
//       Class : SelectiveChildNode
// Description : A base class for nodes like LODNode and SequenceNode
//               that select only one visible child at a time.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA SelectiveChildNode : public PandaNode {
PUBLISHED:
  INLINE SelectiveChildNode(const string &name);

protected:
  INLINE SelectiveChildNode(const SelectiveChildNode &copy);

public:
  virtual bool has_selective_visibility() const;
  virtual int get_first_visible_child() const;
  virtual int get_next_visible_child(int n) const;

protected:
  INLINE void select_child(int n);

private:
  // Not sure if this should be cycled or not.  It's not exactly
  // thread-safe not to cycle it, but it doesn't really need the full
  // pipeline control.  It's probably a problem in the non-thread-safe
  // design; need to rethink the design a bit.
  int _selected_child;

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    PandaNode::init_type();
    register_type(_type_handle, "SelectiveChildNode",
                  PandaNode::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;
};

#include "selectiveChildNode.I"

#endif
