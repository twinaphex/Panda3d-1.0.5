// Filename: textureMemoryCounter.cxx
// Created by:  drose (19Dec00)
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

#include "textureMemoryCounter.h"
#include "paletteImage.h"
#include "textureImage.h"
#include "destTextureImage.h"
#include "omitReason.h"
#include "texturePlacement.h"

#include "indent.h"
#include <math.h>

////////////////////////////////////////////////////////////////////
//     Function: TextureMemoryCounter::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
TextureMemoryCounter::
TextureMemoryCounter() {
  reset();
}

////////////////////////////////////////////////////////////////////
//     Function: TextureMemoryCounter::reset
//       Access: Public
//  Description: Resets the count to zero.
////////////////////////////////////////////////////////////////////
void TextureMemoryCounter::
reset() {
  _num_textures = 0;
  _num_unplaced = 0;
  _num_placed = 0;
  _num_palettes = 0;

  _bytes = 0;
  _unused_bytes = 0;
  _duplicate_bytes = 0;
  _coverage_bytes = 0;
  _textures.clear();
  _palettes.clear();
}

////////////////////////////////////////////////////////////////////
//     Function: TextureMemoryCounter::add_placement
//       Access: Public
//  Description: Adds the indicated TexturePlacement to the counter.
////////////////////////////////////////////////////////////////////
void TextureMemoryCounter::
add_placement(TexturePlacement *placement) {
  TextureImage *texture = placement->get_texture();
  nassertv(texture != (TextureImage *)NULL);

  if (placement->get_omit_reason() == OR_none) {
    PaletteImage *image = placement->get_image();
    nassertv(image != (PaletteImage *)NULL);
    add_palette(image);

    int bytes = count_bytes(image, placement->get_placed_x_size(),
                            placement->get_placed_y_size());
    add_texture(texture, bytes);
    _num_placed++;

  } else {
    DestTextureImage *dest = placement->get_dest();
    if (dest != (DestTextureImage *)NULL) {
      int bytes = count_bytes(dest);
      add_texture(texture, bytes);
      
      _bytes += bytes;
      _num_unplaced++;
    }
  }
}

////////////////////////////////////////////////////////////////////
//     Function: TextureMemoryCounter::report
//       Access: Public
//  Description: Reports the measured texture memory usage.
////////////////////////////////////////////////////////////////////
void TextureMemoryCounter::
report(ostream &out, int indent_level) {
  indent(out, indent_level)
    << _num_placed << " of " << _num_textures << " textures appear on "
    << _num_palettes << " palette images with " << _num_unplaced
    << " unplaced.\n";

  indent(out, indent_level)
    << (_bytes + 512) / 1024 << "k estimated texture memory required.\n";

  if (_bytes != 0) {
    if (_unused_bytes != 0) {
      indent(out, indent_level + 2);
      format_memory_fraction(out, _unused_bytes, _bytes)
        << " is wasted because of unused palette space.\n";
    }

    if (_coverage_bytes > 0) {
      indent(out, indent_level + 2);
      format_memory_fraction(out, _coverage_bytes, _bytes)
        << " is wasted for repeating textures and margins.\n";

    } else if (_coverage_bytes < 0) {
      indent(out, indent_level + 2);
      format_memory_fraction(out, -_coverage_bytes, _bytes)
        << " is *saved* for palettizing partial textures.\n";
    }

    if (_duplicate_bytes != 0) {
      indent(out, indent_level + 2);
      format_memory_fraction(out, _duplicate_bytes, _bytes)
        << " is wasted because of a texture appearing in multiple groups.\n";
    }
  }
}

////////////////////////////////////////////////////////////////////
//     Function: TextureMemoryCounter::format_memory_fraction
//       Access: Private, Static
//  Description: Writes to the indicated ostream an indication of the
//               fraction of the total memory usage that is
//               represented by fraction_bytes.
////////////////////////////////////////////////////////////////////
ostream &TextureMemoryCounter::
format_memory_fraction(ostream &out, int fraction_bytes, int palette_bytes) {
  out << floor(1000.0 * (double)fraction_bytes / (double)palette_bytes + 0.5) / 10.0
      << "% (" << (fraction_bytes + 512) / 1024 << "k)";
  return out;
}

////////////////////////////////////////////////////////////////////
//     Function: TextureMemoryCounter::add_palette
//       Access: Private
//  Description: Adds the indicated PaletteImage to the count.  If
//               this is called twice for a given PaletteImage it does
//               nothing.
////////////////////////////////////////////////////////////////////
void TextureMemoryCounter::
add_palette(PaletteImage *image) {
  bool inserted = _palettes.insert(image).second;
  if (!inserted) {
    // We've already added this palette image.
    return;
  }

  int bytes = count_bytes(image);
  double unused = 1.0 - image->count_utilization();
  double coverage = image->count_coverage();

  _bytes += bytes;
  _unused_bytes += (int)(unused * bytes);
  _coverage_bytes += (int)(coverage * bytes);

  _num_palettes++;
}

////////////////////////////////////////////////////////////////////
//     Function: TextureMemoryCounter::add_texture
//       Access: Private
//  Description: Adds the given TextureImage to the counter.  If the
//               texture image has already been added, this counts the
//               smaller of the two as duplicate bytes.
////////////////////////////////////////////////////////////////////
void TextureMemoryCounter::
add_texture(TextureImage *texture, int bytes) {
  pair<Textures::iterator, bool> result;
  result = _textures.insert(Textures::value_type(texture, bytes));
  if (result.second) {
    // If it was inserted, no problem--no duplicates.
    _num_textures++;
    return;
  }

  // If it was not inserted, we have a duplicate.
  Textures::iterator ti = result.first;

  _duplicate_bytes += min(bytes, (*ti).second);
  (*ti).second = max(bytes, (*ti).second);
}

////////////////////////////////////////////////////////////////////
//     Function: TextureMemoryCounter::count_bytes
//       Access: Private
//  Description: Attempts to estimate the number of bytes the given
//               image file will use in texture memory.
////////////////////////////////////////////////////////////////////
int TextureMemoryCounter::
count_bytes(ImageFile *image) {
  return count_bytes(image, image->get_x_size(), image->get_y_size());
}

////////////////////////////////////////////////////////////////////
//     Function: TextureMemoryCounter::count_bytes
//       Access: Private
//  Description: Attempts to estimate the number of bytes the given
//               image file will use in texture memory.
////////////////////////////////////////////////////////////////////
int TextureMemoryCounter::
count_bytes(ImageFile *image, int x_size, int y_size) {
  int pixels = x_size * y_size;

  // Try to guess the number of bytes per pixel this texture will
  // consume in texture memory, based on its requested format.  This
  // is only a loose guess, because this depends of course on the
  // pecularities of the particular rendering engine.
  int bpp = 0;
  switch (image->get_properties()._format) {
  case EggTexture::F_rgba12:
    bpp = 6;
    break;

  case EggTexture::F_rgba:
  case EggTexture::F_rgbm:
  case EggTexture::F_rgba8:
    bpp = 4;
    break;

  case EggTexture::F_rgb:
  case EggTexture::F_rgb12:
    bpp = 3;
    break;

  case EggTexture::F_rgba4:
  case EggTexture::F_rgba5:
  case EggTexture::F_rgb8:
  case EggTexture::F_rgb5:
  case EggTexture::F_luminance_alpha:
  case EggTexture::F_luminance_alphamask:
    bpp = 2;
    break;

  case EggTexture::F_rgb332:
  case EggTexture::F_red:
  case EggTexture::F_green:
  case EggTexture::F_blue:
  case EggTexture::F_alpha:
  case EggTexture::F_luminance:
    bpp = 1;
    break;

  default:
    bpp = image->get_num_channels();
  }

  int bytes = pixels * bpp;

  // If we're mipmapping, it's worth 1/3 more bytes.
  switch (image->get_properties()._minfilter) {
  case EggTexture::FT_nearest_mipmap_nearest:
  case EggTexture::FT_linear_mipmap_nearest:
  case EggTexture::FT_nearest_mipmap_linear:
  case EggTexture::FT_linear_mipmap_linear:
    bytes = (bytes * 4) / 3;
    break;

  default:
    break;
  }

  return bytes;
}
