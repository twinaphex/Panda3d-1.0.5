// Filename: mayaCopy.h
// Created by:  drose (10May02)
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

#ifndef MAYACOPY_H
#define MAYACOPY_H

#include "pandatoolbase.h"
#include "cvsCopy.h"
#include "mayaApi.h"
#include "mayaShaders.h"
#include "dSearchPath.h"
#include "pointerTo.h"

#include "pset.h"

class MayaShader;
class MayaShaderColorDef;
class MDagPath;

////////////////////////////////////////////////////////////////////
//       Class : MayaCopy
// Description : A program to copy Maya .mb files into the cvs
//               tree.
////////////////////////////////////////////////////////////////////
class MayaCopy : public CVSCopy {
public:
  MayaCopy();

  void run();

protected:
  virtual bool copy_file(const Filename &source, const Filename &dest,
                         CVSSourceDirectory *dir, void *extra_data,
                         bool new_file);

  virtual string filter_filename(const string &source);

private:
  enum FileType {
    FT_maya,
    FT_texture
  };

  class ExtraData {
  public:
    FileType _type;
    MayaShader *_shader;
  };

  bool copy_maya_file(const Filename &source, const Filename &dest,
                     CVSSourceDirectory *dir);
  bool extract_texture(MayaShaderColorDef &color_def, CVSSourceDirectory *dir);
  bool copy_texture(const Filename &source, const Filename &dest,
                    CVSSourceDirectory *dir);

  bool collect_shaders();
  bool collect_shader_for_node(const MDagPath &dag_path);

  bool _keep_ver;

  PT(MayaApi) _maya;
  MayaShaders _shaders;
};

#endif
