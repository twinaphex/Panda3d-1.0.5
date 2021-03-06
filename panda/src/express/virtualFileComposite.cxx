// Filename: virtualFileComposite.cxx
// Created by:  drose (03Aug02)
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

#include "virtualFileComposite.h"

TypeHandle VirtualFileComposite::_type_handle;


////////////////////////////////////////////////////////////////////
//     Function: VirtualFileComposite::get_file_system
//       Access: Published, Virtual
//  Description: Returns the VirtualFileSystem this file is associated
//               with.
////////////////////////////////////////////////////////////////////
VirtualFileSystem *VirtualFileComposite::
get_file_system() const {
  return _file_system;
}

////////////////////////////////////////////////////////////////////
//     Function: VirtualFileComposite::get_filename
//       Access: Published, Virtual
//  Description: Returns the full pathname to this file within the
//               virtual file system.
////////////////////////////////////////////////////////////////////
Filename VirtualFileComposite::
get_filename() const {
  return _filename;
}

////////////////////////////////////////////////////////////////////
//     Function: VirtualFileComposite::is_directory
//       Access: Published, Virtual
//  Description: Returns true if this file represents a directory (and
//               scan_directory() may be called), false otherwise.
////////////////////////////////////////////////////////////////////
bool VirtualFileComposite::
is_directory() const {
  return true;
}

////////////////////////////////////////////////////////////////////
//     Function: VirtualFileComposite::scan_local_directory
//       Access: Protected, Virtual
//  Description: Fills file_list up with the list of files that are
//               within this directory, excluding those whose
//               basenames are listed in mount_points.  Returns true
//               if successful, false if the file is not a directory
//               or the directory cannot be read.
////////////////////////////////////////////////////////////////////
bool VirtualFileComposite::
scan_local_directory(VirtualFileList *file_list, 
                     const ov_set<string> &mount_points) const {
  bool any_ok = false;
  Components::const_iterator ci;
  for (ci = _components.begin(); ci != _components.end(); ++ci) {
    if ((*ci)->scan_local_directory(file_list, mount_points)) {
      any_ok = true;
    }
  }
  
  return any_ok;
}
