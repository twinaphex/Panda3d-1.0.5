// Filename: eggGroupNode.h
// Created by:  drose (16Jan99)
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

#ifndef EGGGROUPNODE_H
#define EGGGROUPNODE_H

#include "pandabase.h"

#include "eggNode.h"

#include "coordinateSystem.h"
#include "typedObject.h"
#include "pointerTo.h"
#include "luse.h"

#include "plist.h"

class EggTextureCollection;
class EggMaterialCollection;
class EggPolygon;
class EggVertex;
class DSearchPath;

////////////////////////////////////////////////////////////////////
//       Class : EggGroupNode
// Description : A base class for nodes in the hierarchy that are not
//               leaf nodes.  (See also EggGroup, which is
//               specifically the "<Group>" node in egg.)
//
//               An EggGroupNode is an STL-style container of pointers
//               to EggNodes, like a vector.  Functions
//               push_back()/pop_back() and insert()/erase() are
//               provided to manipulate the list.  The list may also
//               be operated on (read-only) via iterators and
//               begin()/end().
////////////////////////////////////////////////////////////////////
class EXPCL_PANDAEGG EggGroupNode : public EggNode {

  // This is a bit of private interface stuff that must be here as a
  // forward reference.  This allows us to define the EggGroupNode as
  // an STL container.

private:
  // We define the list of children as a list and not a vector, so we
  // can avoid the bad iterator-invalidating properties of vectors as
  // we insert/delete elements.
  typedef plist< PT(EggNode) > Children;

  // Here begins the actual public interface to EggGroupNode.

PUBLISHED:
  EggGroupNode(const string &name = "") : EggNode(name) { }
  EggGroupNode(const EggGroupNode &copy);
  EggGroupNode &operator = (const EggGroupNode &copy);
  virtual ~EggGroupNode();

  virtual void write(ostream &out, int indent_level) const;

  // The EggGroupNode itself appears to be an STL container of
  // pointers to EggNodes.  The set of children is read-only, however,
  // except through the limited add_child/remove_child or insert/erase
  // interface.  The following implements this.
public:
#ifdef WIN32_VC
  typedef const PT(EggNode) *pointer;
  typedef const PT(EggNode) *const_pointer;
#else
  typedef Children::const_pointer pointer;
  typedef Children::const_pointer const_pointer;
#endif
  typedef Children::const_reference reference;
  typedef Children::const_reference const_reference;
  typedef Children::const_iterator iterator;
  typedef Children::const_iterator const_iterator;
  typedef Children::const_reverse_iterator reverse_iterator;
  typedef Children::const_reverse_iterator const_reverse_iterator;
  typedef Children::size_type size_type;
  typedef Children::difference_type difference_type;

  iterator begin() const;
  iterator end() const;
  reverse_iterator rbegin() const;
  reverse_iterator rend() const;

  iterator insert(iterator position, PT(EggNode) x);
  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);
  void replace(iterator position, PT(EggNode) x);

PUBLISHED:
  bool empty() const;
  size_type size() const;
  void clear();

  // This is an alternate way to traverse the list of children.  It is
  // mainly provided for scripting code, which can't use the iterators
  // defined above (they don't export through interrogate very well).
  // These are, of course, non-thread-safe.
  EggNode *get_first_child();
  EggNode *get_next_child();

  EggNode *add_child(EggNode *node);
  PT(EggNode) remove_child(EggNode *node);
  void steal_children(EggGroupNode &other);

  EggNode *find_child(const string &name) const;

  bool has_absolute_pathnames() const;
  void resolve_filenames(const DSearchPath &searchpath);
  void force_filenames(const Filename &directory);
  void reverse_vertex_ordering();

  void recompute_vertex_normals(double threshold, CoordinateSystem cs = CS_default);
  void recompute_polygon_normals(CoordinateSystem cs = CS_default);
  void strip_normals();

  int triangulate_polygons(bool convex_also);

  int remove_unused_vertices();
  int remove_invalid_primitives();
  virtual bool has_primitives() const;
  virtual bool joint_has_primitives() const;
  virtual bool has_normals() const;

protected:
  virtual void update_under(int depth_offset);

  virtual void r_transform(const LMatrix4d &mat, const LMatrix4d &inv,
                           CoordinateSystem to_cs);
  virtual void r_transform_vertices(const LMatrix4d &mat);
  virtual void r_mark_coordsys(CoordinateSystem cs);
  virtual void r_flatten_transforms();
  virtual void r_apply_texmats(EggTextureCollection &textures);


  CoordinateSystem find_coordsys_entry();
  int find_textures(EggTextureCollection *collection);
  int find_materials(EggMaterialCollection *collection);
  bool r_load_externals(const DSearchPath &searchpath, 
                        CoordinateSystem coordsys);

private:
  Children _children;
  const_iterator _gnc_iterator;

  // Don't try to use these private functions.  User code should add
  // and remove children via add_child()/remove_child(), or via the
  // STL-like push_back()/pop_back() or insert()/erase(), above.
  void prepare_add_child(EggNode *node);
  void prepare_remove_child(EggNode *node);

  // This bit is in support of recompute_vertex_normals().
  class NVertexReference {
  public:
    EggPolygon *_polygon;
    Normald _normal;
    size_t _vertex;
  };
  typedef pvector<NVertexReference> NVertexGroup;
  typedef pmap<Vertexd, NVertexGroup> NVertexCollection;

  void r_collect_vertex_normals(NVertexCollection &collection,
                                double threshold, CoordinateSystem cs);
  void do_compute_vertex_normals(const NVertexGroup &group);

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    EggNode::init_type();
    register_type(_type_handle, "EggGroupNode",
                  EggNode::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;

  friend class EggTextureCollection;
  friend class EggMaterialCollection;
};

#include "eggGroupNode.I"

#endif

