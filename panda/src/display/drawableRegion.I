// Filename: drawableRegion.I
// Created by:  drose (11Jul02)
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
//     Function: DrawableRegion::Constructor
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
INLINE DrawableRegion::
DrawableRegion() : 
  _screenshot_buffer_type(RenderBuffer::T_front),
  _draw_buffer_type(RenderBuffer::T_back),
  _flags(0),
  _clear_color(0.0f, 0.0f, 0.0f, 0.0f),
  _clear_depth(1.0f)
{
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::Copy Constructor
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
INLINE DrawableRegion::
DrawableRegion(const DrawableRegion &copy) :
  _screenshot_buffer_type(copy._screenshot_buffer_type),
  _draw_buffer_type(copy._draw_buffer_type),
  _flags(copy._flags),
  _clear_color(copy._clear_color),
  _clear_depth(copy._clear_depth)
{
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::Copy Assignment Operator
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
INLINE void DrawableRegion::
operator = (const DrawableRegion &copy) {
  _screenshot_buffer_type = copy._screenshot_buffer_type;
  _draw_buffer_type = copy._draw_buffer_type;
  _flags = copy._flags;
  _clear_color = copy._clear_color;
  _clear_depth = copy._clear_depth;
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::copy_clear_settings
//       Access: Public
//  Description: Copies only the clear settings from the other drawable
//               region.
////////////////////////////////////////////////////////////////////
INLINE void DrawableRegion::
copy_clear_settings(const DrawableRegion &copy) {
  _flags = (_flags & ~F_clear_all) | (copy._flags & F_clear_all);
  _clear_color = copy._clear_color;
  _clear_depth = copy._clear_depth;
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::set_clear_color_active
//       Access: Published
//  Description: Toggles the flag that indicates whether the color
//               buffer should be cleared every frame.  If this is
//               true, the color buffer will be cleared to the color
//               indicated by set_clear_color(); otherwise, it will be
//               left alone.
////////////////////////////////////////////////////////////////////
INLINE void DrawableRegion::
set_clear_color_active(bool clear_color_active) {
  if (clear_color_active) {
    _flags |= F_clear_color_active;
  } else {
    _flags &= ~F_clear_color_active;
  }
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::get_clear_color_active
//       Access: Published
//  Description: Returns the current setting of the flag that
//               indicates whether the color buffer should be cleared
//               every frame.  See set_clear_color_active().
////////////////////////////////////////////////////////////////////
INLINE bool DrawableRegion::
get_clear_color_active() const {
  return ((_flags & F_clear_color_active) != 0);
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::set_clear_depth_active
//       Access: Published
//  Description: Toggles the flag that indicates whether the depth
//               buffer should be cleared every frame.  If this is
//               true, the depth buffer will be cleared to the depth
//               value indicated by set_clear_depth(); otherwise, it
//               will be left alone.
////////////////////////////////////////////////////////////////////
INLINE void DrawableRegion::
set_clear_depth_active(bool clear_depth_active) {
  if (clear_depth_active) {
    _flags |= F_clear_depth_active;
  } else {
    _flags &= ~F_clear_depth_active;
  }
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::get_clear_depth_active
//       Access: Published
//  Description: Returns the current setting of the flag that
//               indicates whether the depth buffer should be cleared
//               every frame.  See set_clear_depth_active().
////////////////////////////////////////////////////////////////////
INLINE bool DrawableRegion::
get_clear_depth_active() const {
  return ((_flags & F_clear_depth_active) != 0);
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::set_clear_color
//       Access: Published
//  Description: Sets the clear color to the indicated value.  This is
//               the value that will be used to clear the color buffer
//               every frame, but only if get_clear_color_active()
//               returns true.  If get_clear_color_active() returns
//               false, this is meaningless.
////////////////////////////////////////////////////////////////////
INLINE void DrawableRegion::
set_clear_color(const Colorf &color) {
  _clear_color = color;
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::get_clear_color
//       Access: Published
//  Description: Returns the current clear color value.  This is
//               the value that will be used to clear the color buffer
//               every frame, but only if get_clear_color_active()
//               returns true.  If get_clear_color_active() returns
//               false, this is meaningless.
////////////////////////////////////////////////////////////////////
INLINE const Colorf &DrawableRegion::
get_clear_color() const {
  return _clear_color;
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::set_clear_depth
//       Access: Published
//  Description: Sets the clear depth to the indicated value.  This is
//               the value that will be used to clear the depth buffer
//               every frame, but only if get_clear_depth_active()
//               returns true.  If get_clear_depth_active() returns
//               false, this is meaningless.
////////////////////////////////////////////////////////////////////
INLINE void DrawableRegion::
set_clear_depth(float depth) {
  _clear_depth = depth;
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::get_clear_depth
//       Access: Published
//  Description: Returns the current clear depth value.  This is
//               the value that will be used to clear the depth buffer
//               every frame, but only if get_clear_depth_active()
//               returns true.  If get_clear_depth_active() returns
//               false, this is meaningless.
////////////////////////////////////////////////////////////////////
INLINE float DrawableRegion::
get_clear_depth() const {
  return _clear_depth;
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::is_any_clear_active
//       Access: Published
//  Description: Returns true if any of the clear types (so far there
//               are just color or depth) have been set active, or
//               false if none of them are active and there is no need
//               to clear.
////////////////////////////////////////////////////////////////////
INLINE bool DrawableRegion::
is_any_clear_active() const {
  return (_flags & F_clear_all) != 0;
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::get_draw_buffer_type
//       Access: Public
//  Description: Returns the RenderBuffer into which the GSG should
//               issue draw commands.  Normally, this is the back
//               buffer for double-buffered windows, and the front
//               buffer for single-buffered windows.
////////////////////////////////////////////////////////////////////
INLINE int DrawableRegion::
get_draw_buffer_type() const {
  return _draw_buffer_type;
}

////////////////////////////////////////////////////////////////////
//     Function: DrawableRegion::get_screenshot_buffer_type
//       Access: Public, Virtual
//  Description: Returns the RenderBuffer that should be used for
//               capturing screenshots from this particular
//               DrawableRegion.
////////////////////////////////////////////////////////////////////
INLINE int DrawableRegion::
get_screenshot_buffer_type() const {
  return _screenshot_buffer_type;
}
