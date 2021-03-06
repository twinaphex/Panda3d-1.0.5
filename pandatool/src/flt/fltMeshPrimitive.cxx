// Filename: fltMeshPrimitive.cxx
// Created by:  drose (28Feb01)
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

#include "fltMeshPrimitive.h"
#include "fltRecordReader.h"
#include "fltRecordWriter.h"
#include "fltHeader.h"
#include "fltMaterial.h"

TypeHandle FltMeshPrimitive::_type_handle;

////////////////////////////////////////////////////////////////////
//     Function: FltMeshPrimitive::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
FltMeshPrimitive::
FltMeshPrimitive(FltHeader *header) : FltBead(header) {
  _primitive_type = PT_tristrip;
}

////////////////////////////////////////////////////////////////////
//     Function: FltMeshPrimitive::extract_record
//       Access: Protected, Virtual
//  Description: Fills in the information in this bead based on the
//               information given in the indicated datagram, whose
//               opcode has already been read.  Returns true on
//               success, false if the datagram is invalid.
////////////////////////////////////////////////////////////////////
bool FltMeshPrimitive::
extract_record(FltRecordReader &reader) {
  if (!FltBead::extract_record(reader)) {
    return false;
  }

  nassertr(reader.get_opcode() == FO_mesh_primitive, false);
  DatagramIterator &iterator = reader.get_iterator();

  _primitive_type = (PrimitiveType)iterator.get_be_int16();

  int vertex_width = iterator.get_be_int16();
  int num_vertices = iterator.get_be_int32();

  if (vertex_width == 1) {
    for (int i = 0; i < num_vertices; i++) {
      _vertices.push_back(iterator.get_uint8());
    }

  } else if (vertex_width == 2) {
    for (int i = 0; i < num_vertices; i++) {
      _vertices.push_back(iterator.get_be_uint16());
    }

  } else if (vertex_width == 4) {
    for (int i = 0; i < num_vertices; i++) {
      _vertices.push_back(iterator.get_be_int32());
    }

  } else {
    nout << "Invalid vertex width in mesh primitive: " << vertex_width
         << "\n";
    return false;
  }

  check_remaining_size(iterator);
  return true;
}

////////////////////////////////////////////////////////////////////
//     Function: FltMeshPrimitive::build_record
//       Access: Protected, Virtual
//  Description: Fills up the current record on the FltRecordWriter with
//               data for this record, but does not advance the
//               writer.  Returns true on success, false if there is
//               some error.
////////////////////////////////////////////////////////////////////
bool FltMeshPrimitive::
build_record(FltRecordWriter &writer) const {
  if (!FltBead::build_record(writer)) {
    return false;
  }

  writer.set_opcode(FO_mesh_primitive);
  Datagram &datagram = writer.update_datagram();

  datagram.add_be_int16(_primitive_type);

  // Determine the optimum index width, based on the largest vertex
  // index.
  int max_index = 0;
  Vertices::const_iterator vi;
  for (vi = _vertices.begin(); vi != _vertices.end(); ++vi) {
    max_index = max(max_index, (*vi));
  }

  int vertex_width;
  if (max_index < 0x100) {
    vertex_width = 1;
  } else if (max_index < 0x10000) {
    vertex_width = 2;
  } else {
    vertex_width = 4;
  }

  datagram.add_be_int16(vertex_width);
  datagram.add_be_int32(_vertices.size());

  if (vertex_width == 1) {
    for (vi = _vertices.begin(); vi != _vertices.end(); ++vi) {
      datagram.add_uint8(*vi);
    }

  } else if (vertex_width == 2) {
    for (vi = _vertices.begin(); vi != _vertices.end(); ++vi) {
      datagram.add_be_uint16(*vi);
    }

  } else {
    for (vi = _vertices.begin(); vi != _vertices.end(); ++vi) {
      datagram.add_be_int32(*vi);
    }
  }

  return true;
}
