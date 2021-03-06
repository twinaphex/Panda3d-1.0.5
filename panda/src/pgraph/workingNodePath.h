// Filename: workingNodePath.h
// Created by:  drose (16Mar02)
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

#ifndef WORKINGNODEPATH_H
#define WORKINGNODEPATH_H

#include "pandabase.h"

#include "nodePath.h"
#include "nodePathComponent.h"

////////////////////////////////////////////////////////////////////
//       Class : WorkingNodePath
// Description : This is a class designed to support low-overhead
//               traversals of the complete scene graph, with a memory
//               of the complete path through the graph at any given
//               point.
//
//               You could just use a regular NodePath to do this, but
//               since the NodePath requires storing
//               NodePathComponents on each node as it is constructed,
//               and then removing them when it destructs, there is
//               considerable overhead in that approach.
//
//               The WorkingNodePath eliminates this overhead (but
//               does not guarantee consistency if the scene graph
//               changes while the path is held).
//
//               At any given point, you may ask the WorkingNodePath
//               for its actual NodePath, and it will construct and
//               return a new NodePath representing the complete
//               generated chain.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA WorkingNodePath {
public:
  INLINE WorkingNodePath(const NodePath &start);
  INLINE WorkingNodePath(const WorkingNodePath &copy);
  INLINE WorkingNodePath(const WorkingNodePath &parent, PandaNode *child);
  INLINE ~WorkingNodePath();

  INLINE void operator = (const WorkingNodePath &copy);

  bool is_valid() const;

  INLINE NodePath get_node_path() const;
  INLINE PandaNode *node() const;

  int get_num_nodes() const;
  PandaNode *get_node(int index) const;

  void output(ostream &out) const;

private:
  PT(NodePathComponent) r_get_node_path() const;

  // Either one or the other of these pointers will be filled in, but
  // never both.  We maintain a linked list of WorkingNodePath
  // objects, with a NodePathComponent at the head of the list.
  const WorkingNodePath *_next;
  PT(NodePathComponent) _start;

  PandaNode *_node;
};

INLINE ostream &operator << (ostream &out, const WorkingNodePath &node_path);

#include "workingNodePath.I"

#endif
