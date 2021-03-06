// Filename: switchNode.cxx
// Created by:  drose (31Jul02)
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

#include "pandabase.h"
#include "switchNode.h"
#include "cullTraverser.h"

TypeHandle SwitchNode::_type_handle;

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::CData::make_copy
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
CycleData *SwitchNode::CData::
make_copy() const {
  return new CData(*this);
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::safe_to_combine
//       Access: Public, Virtual
//  Description: Returns true if it is generally safe to combine this
//               particular kind of PandaNode with other kinds of
//               PandaNodes, adding children or whatever.  For
//               instance, an LODNode should not be combined with any
//               other PandaNode, because its set of children is
//               meaningful.
////////////////////////////////////////////////////////////////////
bool SwitchNode::
safe_to_combine() const {
  return false;
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::CData::write_datagram
//       Access: Public, Virtual
//  Description: Writes the contents of this object to the datagram
//               for shipping out to a Bam file.
////////////////////////////////////////////////////////////////////
void SwitchNode::CData::
write_datagram(BamWriter *manager, Datagram &dg) const {
  dg.add_int32(_visible_child);
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::CData::fillin
//       Access: Public, Virtual
//  Description: This internal function is called by make_from_bam to
//               read in all of the relevant data from the BamFile for
//               the new SwitchNode.
////////////////////////////////////////////////////////////////////
void SwitchNode::CData::
fillin(DatagramIterator &scan, BamReader *manager) {
  _visible_child = scan.get_int32();
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::Copy Constructor
//       Access: Protected
//  Description:
////////////////////////////////////////////////////////////////////
SwitchNode::
SwitchNode(const SwitchNode &copy) :
  SelectiveChildNode(copy),
  _cycler(copy._cycler)
{
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::make_copy
//       Access: Public, Virtual
//  Description: Returns a newly-allocated Node that is a shallow copy
//               of this one.  It will be a different Node pointer,
//               but its internal data may or may not be shared with
//               that of the original Node.
////////////////////////////////////////////////////////////////////
PandaNode *SwitchNode::
make_copy() const {
  return new SwitchNode(*this);
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::has_cull_callback
//       Access: Public, Virtual
//  Description: Should be overridden by derived classes to return
//               true if cull_callback() has been defined.  Otherwise,
//               returns false to indicate cull_callback() does not
//               need to be called for this node during the cull
//               traversal.
////////////////////////////////////////////////////////////////////
bool SwitchNode::
has_cull_callback() const {
  return true;
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::cull_callback
//       Access: Public, Virtual
//  Description: If has_cull_callback() returns true, this function
//               will be called during the cull traversal to perform
//               any additional operations that should be performed at
//               cull time.  This may include additional manipulation
//               of render state or additional visible/invisible
//               decisions, or any other arbitrary operation.
//
//               By the time this function is called, the node has
//               already passed the bounding-volume test for the
//               viewing frustum, and the node's transform and state
//               have already been applied to the indicated
//               CullTraverserData object.
//
//               The return value is true if this node should be
//               visible, or false if it should be culled.
////////////////////////////////////////////////////////////////////
bool SwitchNode::
cull_callback(CullTraverser *, CullTraverserData &) {
  select_child(get_visible_child());
  return true;
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::has_single_child_visibility
//       Access: Public, Virtual
//  Description: Should be overridden by derived classes to return
//               true if this kind of node has the special property
//               that just one of its children is visible at any given
//               time, and furthermore that the particular visible
//               child can be determined without reference to any
//               external information (such as a camera).  At present,
//               only SequenceNodes and SwitchNodes fall into this
//               category.
//
//               If this function returns true, get_visible_child()
//               can be called to return the index of the
//               currently-visible child.
////////////////////////////////////////////////////////////////////
bool SwitchNode::
has_single_child_visibility() const {
  return true;
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::get_visible_child
//       Access: Published, Virtual
//  Description: Returns the index of the child that should be visible.
////////////////////////////////////////////////////////////////////
int SwitchNode::
get_visible_child() const {
  CDReader cdata(_cycler);
  return cdata->_visible_child;
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::register_with_read_factory
//       Access: Public, Static
//  Description: Tells the BamReader how to create objects of type
//               SwitchNode.
////////////////////////////////////////////////////////////////////
void SwitchNode::
register_with_read_factory() {
  BamReader::get_factory()->register_factory(get_class_type(), make_from_bam);
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::write_datagram
//       Access: Public, Virtual
//  Description: Writes the contents of this object to the datagram
//               for shipping out to a Bam file.
////////////////////////////////////////////////////////////////////
void SwitchNode::
write_datagram(BamWriter *manager, Datagram &dg) {
  SelectiveChildNode::write_datagram(manager, dg);
  manager->write_cdata(dg, _cycler);
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::make_from_bam
//       Access: Protected, Static
//  Description: This function is called by the BamReader's factory
//               when a new object of type SwitchNode is encountered
//               in the Bam file.  It should create the SwitchNode
//               and extract its information from the file.
////////////////////////////////////////////////////////////////////
TypedWritable *SwitchNode::
make_from_bam(const FactoryParams &params) {
  SwitchNode *node = new SwitchNode("");
  DatagramIterator scan;
  BamReader *manager;

  parse_params(params, scan, manager);
  node->fillin(scan, manager);

  return node;
}

////////////////////////////////////////////////////////////////////
//     Function: SwitchNode::fillin
//       Access: Protected
//  Description: This internal function is called by make_from_bam to
//               read in all of the relevant data from the BamFile for
//               the new SwitchNode.
////////////////////////////////////////////////////////////////////
void SwitchNode::
fillin(DatagramIterator &scan, BamReader *manager) {
  SelectiveChildNode::fillin(scan, manager);
  manager->read_cdata(scan, _cycler);
}
