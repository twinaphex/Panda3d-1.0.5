// Filename: fltBeadID.h
// Created by:  drose (24Aug00)
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

#ifndef FLTBEADID_H
#define FLTBEADID_H

#include "pandatoolbase.h"

#include "fltBead.h"

////////////////////////////////////////////////////////////////////
//       Class : FltBeadID
// Description : A base class for any of a broad family of flt beads
//               that include an ID.
////////////////////////////////////////////////////////////////////
class FltBeadID : public FltBead {
public:
  FltBeadID(FltHeader *header);

  const string &get_id() const;
  void set_id(const string &id);

  virtual void output(ostream &out) const;

protected:
  virtual bool extract_record(FltRecordReader &reader);
  virtual bool extract_ancillary(FltRecordReader &reader);

  virtual bool build_record(FltRecordWriter &writer) const;
  virtual FltError write_ancillary(FltRecordWriter &writer) const;

private:
  string _id;

public:
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    FltBead::init_type();
    register_type(_type_handle, "FltBeadID",
                  FltBead::get_class_type());
  }

private:
  static TypeHandle _type_handle;
};

#endif

