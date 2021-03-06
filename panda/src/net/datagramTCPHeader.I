// Filename: datagramTCPHeader.I
// Created by:  drose (01Aug01)
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


////////////////////////////////////////////////////////////////////
//     Function: DatagramTCPHeader::get_datagram_size
//       Access: Public
//  Description: Returns the number of bytes in the associated
//               datagram.
////////////////////////////////////////////////////////////////////
INLINE int DatagramTCPHeader::
get_datagram_size() const {
  DatagramIterator di(_header);
  return di.get_uint16();
}

////////////////////////////////////////////////////////////////////
//     Function: DatagramTCPHeader::get_header
//       Access: Public
//  Description: Returns a pointer to a block of data of length
//               datagram_tcp_header_size, which can be written to the
//               network as the header information.
////////////////////////////////////////////////////////////////////
INLINE string DatagramTCPHeader::
get_header() const {
  return _header.get_message();
}
