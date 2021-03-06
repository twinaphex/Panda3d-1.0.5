// Filename: texture.h
// Created by:  mike (09Jan97)
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
#ifndef TEXTURE_H
#define TEXTURE_H

#include "pandabase.h"

#include "imageBuffer.h"
#include "pixelBuffer.h"
#include "graphicsStateGuardianBase.h"
#include "pmap.h"

class PNMImage;
class TextureContext;
class FactoryParams;
class PreparedGraphicsObjects;

////////////////////////////////////////////////////////////////////
//       Class : Texture
// Description : 2D texture class
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA Texture : public ImageBuffer {
PUBLISHED:
  enum FilterType {
    // Mag Filter and Min Filter

    // Point sample the pixel
    FT_nearest,

    // Bilinear filtering of four neighboring pixels
    FT_linear,

    // Min Filter Only

    // Point sample the pixel from the nearest mipmap level
    FT_nearest_mipmap_nearest,

    // Bilinear filter the pixel from the nearest mipmap level
    FT_linear_mipmap_nearest,

    // Point sample the pixel from two mipmap levels, and linearly blend
    FT_nearest_mipmap_linear,

    // A.k.a. trilinear filtering: Bilinear filter the pixel from
    // two mipmap levels, and linearly blend the results.
    FT_linear_mipmap_linear,

    // Returned by string_filter_type() for an invalid match.
    FT_invalid
  };

  enum WrapMode {
    WM_clamp,  // coords that would be outside [0-1] are clamped to 0 or 1
    WM_repeat,
    WM_mirror,
    WM_mirror_once,   // mirror once, then clamp
    WM_border_color,  // coords outside [0-1] use explict border color
    // Returned by string_wrap_mode() for an invalid match.
    WM_invalid
  };

PUBLISHED:
  Texture(bool match_framebuffer_format = false);
  Texture(int xsize, int ysize, int components, int component_width, 
          PixelBuffer::Type type, PixelBuffer::Format format,
          bool allocate_ram);
  ~Texture();

  bool read(const Filename &fullpath, int primary_file_num_channels = 0);
  bool read(const Filename &fullpath, const Filename &alpha_fullpath,
            int primary_file_num_channels = 0, int alpha_file_channel = 0);
  bool write(const Filename &fullpath = "") const;

  bool load(const PNMImage &pnmimage);
  bool store(PNMImage &pnmimage) const;

  void set_wrapu(WrapMode wrap);
  void set_wrapv(WrapMode wrap);
  void set_minfilter(FilterType filter);
  void set_magfilter(FilterType filter);
  void set_anisotropic_degree(int anisotropic_degree);
  void set_border_color(const Colorf &color);
  void set_border_width(int border_width);

  INLINE WrapMode get_wrapu() const;
  INLINE WrapMode get_wrapv() const;
  INLINE FilterType get_minfilter() const;
  INLINE FilterType get_magfilter() const;
  INLINE int get_anisotropic_degree() const;
  INLINE Colorf get_border_color() const;
  INLINE int get_border_width() const;
  INLINE bool uses_mipmaps() const;

  INLINE bool get_match_framebuffer_format() const;

  void prepare(PreparedGraphicsObjects *prepared_objects);

public:
  static bool is_mipmap(FilterType type);

  TextureContext *prepare_now(PreparedGraphicsObjects *prepared_objects, 
                              GraphicsStateGuardianBase *gsg);
  bool release(PreparedGraphicsObjects *prepared_objects);
  int release_all();

  INLINE bool has_ram_image() const;
  INLINE bool might_have_ram_image() const;
  PixelBuffer *get_ram_image();
  INLINE void set_keep_ram_image(bool keep_ram_image);
  INLINE bool get_keep_ram_image() const;

  // These bits are used as parameters to Texture::mark_dirty() and
  // also TextureContext::mark_dirty() (and related functions in
  // TextureContext).
  enum DirtyFlags {
    DF_image      = 0x001,  // The image pixels have changed.
    DF_wrap       = 0x002,  // The wrap properties have changed.
    DF_filter     = 0x004,  // The minfilter or magfilter have changed.
    DF_mipmap     = 0x008,  // The use of mipmaps or not has changed.
    DF_border     = 0x010,  // The border has changed.
  };

  void mark_dirty(int flags_to_set);

  static WrapMode string_wrap_mode(const string &string);
  static FilterType string_filter_type(const string &string);

private:
  void clear_prepared(PreparedGraphicsObjects *prepared_objects);

  WrapMode _wrapu;
  WrapMode _wrapv;
  FilterType _minfilter;
  FilterType _magfilter;
  int _anisotropic_degree;
  bool _keep_ram_image;
  Colorf _border_color;
  int _border_width;
  bool _match_framebuffer_format;

  // A Texture keeps a list (actually, a map) of all the
  // PreparedGraphicsObjects tables that it has been prepared into.
  // Each PGO conversely keeps a list (a set) of all the Textures that
  // have been prepared there.  When either destructs, it removes
  // itself from the other's list.
  typedef pmap<PreparedGraphicsObjects *, TextureContext *, pointer_hash> Contexts;
  Contexts _contexts;

  // This value represents the intersection of all the dirty flags of
  // the various TextureContexts that might be associated with this
  // texture.
  int _all_dirty_flags;

public:
  // These are public to allow direct manipulation of the underlying
  // pixel buffer when needed.  Know what you are doing!
  PT(PixelBuffer) _pbuffer;

  // Datagram stuff
public:
  static void register_with_read_factory(void);
  virtual void write_datagram(BamWriter* manager, Datagram &me);

  static TypedWritable *make_Texture(const FactoryParams &params);

protected:
  void fillin(DatagramIterator& scan, BamReader* manager, bool has_rawdata = false);

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    ImageBuffer::init_type();
    register_type(_type_handle, "Texture",
                  ImageBuffer::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:

  static TypeHandle _type_handle;

  friend class TextureContext;
  friend class PreparedGraphicsObjects;
};

EXPCL_PANDA ostream &operator << (ostream &out, Texture::FilterType ft);
EXPCL_PANDA istream &operator >> (istream &in, Texture::FilterType &ft);

#include "texture.I"

#endif

