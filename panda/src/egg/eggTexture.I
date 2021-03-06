// Filename: eggTexture.I
// Created by:  drose (18Jan99)
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
//     Function: EggTexture::set_format
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_format(Format format) {
  _format = format;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_format
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggTexture::Format EggTexture::
get_format() const {
  return _format;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_wrap_mode
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_wrap_mode(WrapMode mode) {
  _wrap_mode = mode;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_wrap_mode
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggTexture::WrapMode EggTexture::
get_wrap_mode() const {
  return _wrap_mode;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_wrap_u
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_wrap_u(WrapMode mode) {
  _wrap_u = mode;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_wrap_u
//       Access: Published
//  Description: Returns the amount specified for U wrap.  This may be
//               unspecified, even if there is an overall wrap value.
////////////////////////////////////////////////////////////////////
INLINE EggTexture::WrapMode EggTexture::
get_wrap_u() const {
  return _wrap_u;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::determine_wrap_u
//       Access: Published
//  Description: Determines the appropriate wrap in the U direction.
//               This is different from get_wrap_u() in that if the U
//               wrap is unspecified, it returns the overall wrap
//               value.
////////////////////////////////////////////////////////////////////
INLINE EggTexture::WrapMode EggTexture::
determine_wrap_u() const {
  return (_wrap_u == WM_unspecified) ? get_wrap_mode() : get_wrap_u();
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_wrap_v
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_wrap_v(WrapMode mode) {
  _wrap_v = mode;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_wrap_v
//       Access: Published
//  Description: Returns the amount specified for V wrap.  This may be
//               unspecified, even if there is an overall wrap value.
////////////////////////////////////////////////////////////////////
INLINE EggTexture::WrapMode EggTexture::
get_wrap_v() const {
  return _wrap_v;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::determine_wrap_v
//       Access: Published
//  Description: Determines the appropriate wrap in the V direction.
//               This is different from get_wrap_v() in that if the U
//               wrap is unspecified, it returns the overall wrap
//               value.
////////////////////////////////////////////////////////////////////
INLINE EggTexture::WrapMode EggTexture::
determine_wrap_v() const {
  return (_wrap_v == WM_unspecified) ? get_wrap_mode() : get_wrap_v();
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_minfilter
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_minfilter(FilterType type) {
  _minfilter = type;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_minfilter
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggTexture::FilterType EggTexture::
get_minfilter() const {
  return _minfilter;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_magfilter
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_magfilter(FilterType type) {
  _magfilter = type;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_magfilter
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggTexture::FilterType EggTexture::
get_magfilter() const {
  return _magfilter;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_anisotropic_degree
//       Access: Published
//  Description: Sets the degree of anisotropic filtering for this
//               texture.  1 is off; higher levels indicate filtering
//               in effect.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_anisotropic_degree(int anisotropic_degree) {
  _anisotropic_degree = anisotropic_degree;
  _flags |= F_has_anisotropic_degree;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::clear_anisotropic_degree
//       Access: Published
//  Description: Removes the specification of anisotropic filtering
//               from the texture.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
clear_anisotropic_degree() {
  _anisotropic_degree = 0;
  _flags &= ~F_has_anisotropic_degree;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::has_anisotropic_degree
//       Access: Published
//  Description: Returns true if a value for the anisotropic filtering
//               degree has been specified for this texture, false
//               otherwise.
////////////////////////////////////////////////////////////////////
INLINE bool EggTexture::
has_anisotropic_degree() const {
  return (_flags & F_has_anisotropic_degree) != 0;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_anisotropic_degree
//       Access: Published
//  Description: Returns the anisotropic filtering degree that has
//               been specified for this texture, or 0 if nothing has
//               been specified.
////////////////////////////////////////////////////////////////////
INLINE int EggTexture::
get_anisotropic_degree() const {
  // note: _anisotropic_degree of 0 and 1 are equivalent (no
  // anisotropic filtering to be done by gsg)
  return _anisotropic_degree;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_env_type
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_env_type(EnvType type) {
  _env_type = type;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_env_type
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggTexture::EnvType EggTexture::
get_env_type() const {
  return _env_type;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_combine_mode
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_combine_mode(CombineChannel channel, CombineMode cm) {
  nassertv((int)channel >= 0 && (int)channel < (int)CC_num_channels);
  _combiner[channel]._mode = cm;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_combine_mode
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggTexture::CombineMode EggTexture::
get_combine_mode(CombineChannel channel) const {
  nassertr((int)channel >= 0 && (int)channel < (int)CC_num_channels, CM_unspecified);
  return _combiner[channel]._mode;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_combine_source
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_combine_source(CombineChannel channel, int n, CombineSource cs) {
  nassertv((int)channel >= 0 && (int)channel < (int)CC_num_channels);
  nassertv(n >= 0 && n < (int)CI_num_indices);
  _combiner[channel]._ops[n]._source = cs;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_combine_source
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggTexture::CombineSource EggTexture::
get_combine_source(CombineChannel channel, int n) const {
  nassertr((int)channel >= 0 && (int)channel < (int)CC_num_channels, CS_unspecified);
  nassertr(n >= 0 && n < (int)CI_num_indices, CS_unspecified);
  return _combiner[channel]._ops[n]._source;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_combine_operand
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_combine_operand(CombineChannel channel, int n, CombineOperand co) {
  nassertv((int)channel >= 0 && (int)channel < (int)CC_num_channels);
  nassertv(n >= 0 && n < (int)CI_num_indices);
  _combiner[channel]._ops[n]._operand = co;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_combine_operand
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggTexture::CombineOperand EggTexture::
get_combine_operand(CombineChannel channel, int n) const {
  nassertr((int)channel >= 0 && (int)channel < (int)CC_num_channels, CO_unspecified);
  nassertr(n >= 0 && n < (int)CI_num_indices, CO_unspecified);
  return _combiner[channel]._ops[n]._operand;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_tex_gen
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_tex_gen(TexGen tex_gen) {
  _tex_gen = tex_gen;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_tex_gen
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE EggTexture::TexGen EggTexture::
get_tex_gen() const {
  return _tex_gen;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_stage_name
//       Access: Published
//  Description: Specifies the particular TextureStage this texture
//               will be rendered on by name.  If this is omitted, the
//               texture will be rendered on the default TextureStage,
//               unless some other stage-specific property is
//               specificied, in which case the texture will be
//               rendered on a TextureStage with the same name as the
//               tref.  This is in support of multitexturing.
//
//               Each different TextureStage in the world must be
//               uniquely named.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_stage_name(const string &stage_name) {
  _stage_name = stage_name;
  _flags |= F_has_stage_name;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::clear_stage_name
//       Access: Published
//  Description: Removes the named TextureStage specification.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
clear_stage_name() {
  _stage_name = string();
  _flags &= ~F_has_stage_name;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::has_stage_name
//       Access: Published
//  Description: Returns true if a stage name has been explicitly
//               specified for this texture, false otherwise.
////////////////////////////////////////////////////////////////////
INLINE bool EggTexture::
has_stage_name() const {
  return (_flags & F_has_stage_name) != 0;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_stage_name
//       Access: Published
//  Description: Returns the stage name that has been specified for
//               this texture, or the tref name if no texture stage
//               has explicitly been specified.
////////////////////////////////////////////////////////////////////
INLINE const string &EggTexture::
get_stage_name() const {
  return has_stage_name() ? _stage_name : get_name();
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_priority
//       Access: Published
//  Description: Sets the importance of this texture with respect to
//               other textures also applied on the same geometry.
//               This is only meaningful in the presence of
//               multitexturing.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_priority(int priority) {
  _priority = priority;
  _flags |= F_has_priority;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::clear_priority
//       Access: Published
//  Description: Removes the specification of multitexture priority
//               from the texture.  The default priority value is 0.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
clear_priority() {
  _priority = 0;
  _flags &= ~F_has_priority;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::has_priority
//       Access: Published
//  Description: Returns true if a priority value for multitexture
//               importance has been specified for the texture, false
//               otherwise.
////////////////////////////////////////////////////////////////////
INLINE bool EggTexture::
has_priority() const {
  return (_flags & F_has_priority) != 0;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_priority
//       Access: Published
//  Description: Returns the multitexture importance value that has been
//               specified for the texture, or 0 if no priority value has
//               been specified.
////////////////////////////////////////////////////////////////////
INLINE int EggTexture::
get_priority() const {
  return _priority;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_color
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_color(const Colorf &color) {
  _color = color;
  _flags |= F_has_color;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::clear_color
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
clear_color() {
  _color.set(0.0f, 0.0f, 0.0f, 1.0f);
  _flags &= ~F_has_color;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::has_color
//       Access: Published
//  Description: Returns true if a blend color has been
//               specified for the texture.
////////////////////////////////////////////////////////////////////
INLINE bool EggTexture::
has_color() const {
  return (_flags & F_has_color) != 0;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_color
//       Access: Published
//  Description: Returns the blend color if one has been
//               specified, or (0, 0, 0, 1) otherwise.
////////////////////////////////////////////////////////////////////
INLINE const Colorf &EggTexture::
get_color() const {
  return _color;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_uv_name
//       Access: Published
//  Description: Specifies the named set of texture coordinates that
//               this texture will use when it is applied to geometry.
//               Geometry may have multiple sets of texture
//               coordinates defined, by name.
//
//               If this is not specified for a particular texture,
//               the default set of texture coordinates will be used.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_uv_name(const string &uv_name) {
  _uv_name = uv_name;
  _flags |= F_has_uv_name;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::clear_uv_name
//       Access: Published
//  Description: Removes the restriction to a particular named set of
//               texture coordinates and restores the texture to using
//               the default texture coordinates.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
clear_uv_name() {
  _uv_name = string();
  _flags &= ~F_has_uv_name;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::has_uv_name
//       Access: Published
//  Description: Returns true if a texcoord name has been explicitly
//               specified for this texture, false otherwise.
////////////////////////////////////////////////////////////////////
INLINE bool EggTexture::
has_uv_name() const {
  return (_flags & F_has_uv_name) != 0;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_uv_name
//       Access: Published
//  Description: Returns the texcoord name that has been specified for
//               this texture, or the empty string if no texcoord name
//               has explicitly been specified.
////////////////////////////////////////////////////////////////////
INLINE const string &EggTexture::
get_uv_name() const {
  return _uv_name;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_transform
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_transform(const LMatrix3d &transform) {
  _transform = transform;
  _flags |= F_has_transform;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::clear_transform
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
clear_transform() {
  _transform = LMatrix3d::ident_mat();
  _flags &= ~F_has_transform;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::has_transform
//       Access: Published
//  Description: Returns true if a texture matrix transform has been
//               specified for the texture (even if the transform is
//               identity).
////////////////////////////////////////////////////////////////////
INLINE bool EggTexture::
has_transform() const {
  return (_flags & F_has_transform) != 0;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_transform
//       Access: Published
//  Description: Returns the texture matrix transform if one has been
//               specified, or identity matrix otherwise.
////////////////////////////////////////////////////////////////////
INLINE const LMatrix3d &EggTexture::
get_transform() const {
  return _transform;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::transform_is_identity()
//       Access: Published
//  Description: Returns true if no texture matrix transform has been
//               specified, or if the one specified is the identity
//               transform.  Returns false only if a nonidentity
//               transform has been applied.
////////////////////////////////////////////////////////////////////
INLINE bool EggTexture::
transform_is_identity() const {
  return (!has_transform() ||
          _transform.almost_equal(LMatrix3d::ident_mat(), 0.0001));
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_alpha_filename
//       Access: Published
//  Description: Specifies a separate file that will be loaded in with
//               the 1- or 3-component texture and applied as the
//               alpha channel.  This is useful when loading textures
//               from file formats that do not support alpha, for
//               instance jpg.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_alpha_filename(const Filename &alpha_filename) {
  _alpha_filename = alpha_filename;
  _alpha_fullpath = alpha_filename;
  _flags |= F_has_alpha_filename;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::clear_alpha_filename
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
clear_alpha_filename() {
  _alpha_filename = Filename();
  _alpha_fullpath = Filename();
  _flags &= ~F_has_alpha_filename;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::has_alpha_filename
//       Access: Published
//  Description: Returns true if a separate file for the alpha
//               component has been applied, false otherwise.  See
//               set_alpha_filename().
////////////////////////////////////////////////////////////////////
INLINE bool EggTexture::
has_alpha_filename() const {
  return (_flags & F_has_alpha_filename) != 0;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_alpha_filename
//       Access: Published
//  Description: Returns the separate file assigned for the alpha
//               channel.  It is an error to call this unless
//               has_alpha_filename() returns true.  See set_alpha_filename().
////////////////////////////////////////////////////////////////////
INLINE const Filename &EggTexture::
get_alpha_filename() const {
  nassertr(has_alpha_filename(), _alpha_filename);
  return _alpha_filename;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_alpha_fullpath
//       Access: Published
//  Description: Returns the full pathname to the alpha file, if it is
//               known; otherwise, returns the same thing as
//               get_alpha_filename().
//
//               This function simply returns whatever was set by the
//               last call to set_alpha_fullpath().  This string is
//               not written to the egg file; its main purpose is to
//               record the full path to the alpha filename if it is
//               known, for egg structures that are generated
//               in-memory and then immediately converted to a scene
//               graph.
////////////////////////////////////////////////////////////////////
INLINE const Filename &EggTexture::
get_alpha_fullpath() const {
  return _alpha_fullpath;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_alpha_fullpath
//       Access: Published
//  Description: Records the full pathname to the file, for the
//               benefit of get_alpha_fullpath().
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_alpha_fullpath(const Filename &alpha_fullpath) {
  _alpha_fullpath = alpha_fullpath;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::set_alpha_file_channel
//       Access: Published
//  Description: If a separate alpha-file is specified, this indicates
//               which channel number should be extracted from this
//               file to derive the alpha channel for the final image.
//               The default is 0, which means the grayscale
//               combination of r, g, b.  Otherwise, this should be
//               the 1-based channel number, for instance 1, 2, or 3
//               for r, g, or b, respectively, or 4 for the alpha
//               channel of a four-component image.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
set_alpha_file_channel(int alpha_file_channel) {
  _alpha_file_channel = alpha_file_channel;
  _flags |= F_has_alpha_file_channel;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::clear_alpha_file_channel
//       Access: Published
//  Description: Removes the specification of a particular channel to
//               use from the alpha-file image.
////////////////////////////////////////////////////////////////////
INLINE void EggTexture::
clear_alpha_file_channel() {
  _alpha_file_channel = 0;
  _flags &= ~F_has_alpha_file_channel;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::has_alpha_file_channel
//       Access: Published
//  Description: Returns true if a particular channel has been
//               specified for the alpha-file image, false otherwise.
////////////////////////////////////////////////////////////////////
INLINE bool EggTexture::
has_alpha_file_channel() const {
  return (_flags & F_has_alpha_file_channel) != 0;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_alpha_file_channel
//       Access: Published
//  Description: Returns the particular channel that has been
//               specified for the alpha-file image, or 0 if no
//               channel has been specified.  See
//               set_alpha_file_channel().
////////////////////////////////////////////////////////////////////
INLINE int EggTexture::
get_alpha_file_channel() const {
  return _alpha_file_channel;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::get_multitexture_sort
//       Access: Published
//  Description: Returns an integer that represents the depth to which
//               this texture is layered on all other textures in the
//               egg file.  In general, if texture A is layered over
//               texture B, then sort(A) > sort(B).  If texture A is
//               never layered over any other texture, then sort(A) ==
//               0.  More than that is difficult to guarantee.
////////////////////////////////////////////////////////////////////
INLINE int EggTexture::
get_multitexture_sort() const {
  return _multitexture_sort;
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::SourceAndOperand::Constructor
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
INLINE EggTexture::SourceAndOperand::
SourceAndOperand() :
  _source(CS_unspecified),
  _operand(CO_unspecified)
{
}

////////////////////////////////////////////////////////////////////
//     Function: EggTexture::Combiner::Constructor
//       Access: Public
//  Description: 
////////////////////////////////////////////////////////////////////
INLINE EggTexture::Combiner::
Combiner() :
  _mode(CM_unspecified)
{
}

////////////////////////////////////////////////////////////////////
//     Function: UniqueEggTextures::Constructor
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE UniqueEggTextures::
UniqueEggTextures(int eq) : _eq(eq) {
}

////////////////////////////////////////////////////////////////////
//     Function: UniqueEggTextures::Function operator
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
INLINE bool UniqueEggTextures::
operator ()(const EggTexture *t1, const EggTexture *t2) const {
  return t1->sorts_less_than(*t2, _eq);
}

