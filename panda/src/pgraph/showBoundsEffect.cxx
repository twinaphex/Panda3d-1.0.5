// Filename: showBoundsEffect.cxx
// Created by:  drose (25Mar02)
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

#include "showBoundsEffect.h"
#include "bamReader.h"
#include "bamWriter.h"
#include "datagram.h"
#include "datagramIterator.h"

TypeHandle ShowBoundsEffect::_type_handle;

////////////////////////////////////////////////////////////////////
//     Function: ShowBoundsEffect::make
//       Access: Published, Static
//  Description: Constructs a new ShowBoundsEffect object.
////////////////////////////////////////////////////////////////////
CPT(RenderEffect) ShowBoundsEffect::
make() {
  ShowBoundsEffect *effect = new ShowBoundsEffect;
  return return_new(effect);
}

////////////////////////////////////////////////////////////////////
//     Function: ShowBoundsEffect::safe_to_combine
//       Access: Public, Virtual
//  Description: Returns true if this kind of effect can safely be
//               combined with sibling nodes that share the exact same
//               effect, or false if this is not a good idea.
////////////////////////////////////////////////////////////////////
bool ShowBoundsEffect::
safe_to_combine() const {
  return false;
}

////////////////////////////////////////////////////////////////////
//     Function: ShowBoundsEffect::compare_to_impl
//       Access: Protected, Virtual
//  Description: Intended to be overridden by derived ShowBoundsEffect
//               types to return a unique number indicating whether
//               this ShowBoundsEffect is equivalent to the other one.
//
//               This should return 0 if the two ShowBoundsEffect objects
//               are equivalent, a number less than zero if this one
//               should be sorted before the other one, and a number
//               greater than zero otherwise.
//
//               This will only be called with two ShowBoundsEffect
//               objects whose get_type() functions return the same.
////////////////////////////////////////////////////////////////////
int ShowBoundsEffect::
compare_to_impl(const RenderEffect *other) const {
  // All ShowBoundsEffects are equivalent--there are no properties to
  // store.
  return 0;
}

////////////////////////////////////////////////////////////////////
//     Function: ShowBoundsEffect::make_default_impl
//       Access: Protected, Virtual
//  Description: Intended to be overridden by derived ShowBoundsEffect
//               types to specify what the default property for a
//               ShowBoundsEffect of this type should be.
//
//               This should return a newly-allocated ShowBoundsEffect of
//               the same type that corresponds to whatever the
//               standard default for this kind of ShowBoundsEffect is.
////////////////////////////////////////////////////////////////////
RenderEffect *ShowBoundsEffect::
make_default_impl() const {
  return new ShowBoundsEffect;
}

////////////////////////////////////////////////////////////////////
//     Function: ShowBoundsEffect::register_with_read_factory
//       Access: Public, Static
//  Description: Tells the BamReader how to create objects of type
//               ShowBoundsEffect.
////////////////////////////////////////////////////////////////////
void ShowBoundsEffect::
register_with_read_factory() {
  BamReader::get_factory()->register_factory(get_class_type(), make_from_bam);
}

////////////////////////////////////////////////////////////////////
//     Function: ShowBoundsEffect::write_datagram
//       Access: Public, Virtual
//  Description: Writes the contents of this object to the datagram
//               for shipping out to a Bam file.
////////////////////////////////////////////////////////////////////
void ShowBoundsEffect::
write_datagram(BamWriter *manager, Datagram &dg) {
  RenderEffect::write_datagram(manager, dg);
}

////////////////////////////////////////////////////////////////////
//     Function: ShowBoundsEffect::make_from_bam
//       Access: Protected, Static
//  Description: This function is called by the BamReader's factory
//               when a new object of type ShowBoundsEffect is encountered
//               in the Bam file.  It should create the ShowBoundsEffect
//               and extract its information from the file.
////////////////////////////////////////////////////////////////////
TypedWritable *ShowBoundsEffect::
make_from_bam(const FactoryParams &params) {
  ShowBoundsEffect *effect = new ShowBoundsEffect;
  DatagramIterator scan;
  BamReader *manager;

  parse_params(params, scan, manager);
  effect->fillin(scan, manager);

  return effect;
}

////////////////////////////////////////////////////////////////////
//     Function: ShowBoundsEffect::fillin
//       Access: Protected
//  Description: This internal function is called by make_from_bam to
//               read in all of the relevant data from the BamFile for
//               the new ShowBoundsEffect.
////////////////////////////////////////////////////////////////////
void ShowBoundsEffect::
fillin(DatagramIterator &scan, BamReader *manager) {
  RenderEffect::fillin(scan, manager);
}
