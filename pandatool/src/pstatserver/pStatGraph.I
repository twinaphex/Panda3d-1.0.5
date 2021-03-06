// Filename: pStatGraph.I
// Created by:  drose (19Jul00)
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
//     Function: PStatGraph::get_monitor
//       Access: Public
//  Description: Returns the monitor associated with this chart.
////////////////////////////////////////////////////////////////////
INLINE PStatMonitor *PStatGraph::
get_monitor() const {
  return _monitor;
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::get_num_labels
//       Access: Public
//  Description: Returns the number of labels to be drawn for this
//               chart.
////////////////////////////////////////////////////////////////////
INLINE int PStatGraph::
get_num_labels() const {
  return _labels.size();
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::get_label_collector
//       Access: Public
//  Description: Returns the collector index associated with the nth
//               label.
////////////////////////////////////////////////////////////////////
INLINE int PStatGraph::
get_label_collector(int n) const {
  nassertr(n >= 0 && n < (int)_labels.size(), 0);
  return _labels[n];
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::get_label_name
//       Access: Public
//  Description: Returns the text associated with the nth label.
////////////////////////////////////////////////////////////////////
INLINE string PStatGraph::
get_label_name(int n) const {
  nassertr(n >= 0 && n < (int)_labels.size(), string());
  return _monitor->get_client_data()->get_collector_name(_labels[n]);
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::get_label_color
//       Access: Public
//  Description: Returns the color associated with the nth label.
////////////////////////////////////////////////////////////////////
INLINE RGBColorf PStatGraph::
get_label_color(int n) const {
  nassertr(n >= 0 && n < (int)_labels.size(), RGBColorf(0.0, 0.0, 0.0));
  return _monitor->get_collector_color(_labels[n]);
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::set_target_frame_rate
//       Access: Public
//  Description: Sets the target frame rate of the application in Hz.
//               This only affects the choice of initial scale and the
//               placement of guide bars.
////////////////////////////////////////////////////////////////////
INLINE void PStatGraph::
set_target_frame_rate(float frame_rate) {
  if (_target_frame_rate != frame_rate) {
    _target_frame_rate = frame_rate;
    normal_guide_bars();
  }
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::get_target_frame_rate
//       Access: Public
//  Description: Returns the indicated target frame rate in Hz.  See
//               set_target_frame_rate().
////////////////////////////////////////////////////////////////////
INLINE float PStatGraph::
get_target_frame_rate() const {
  return _target_frame_rate;
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::get_xsize
//       Access: Public
//  Description: Returns the width of the chart in pixels.
////////////////////////////////////////////////////////////////////
INLINE int PStatGraph::
get_xsize() const {
  return _xsize;
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::get_ysize
//       Access: Public
//  Description: Returns the height of the chart in pixels.
////////////////////////////////////////////////////////////////////
INLINE int PStatGraph::
get_ysize() const {
  return _ysize;
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::set_guide_bar_units
//       Access: Public
//  Description: Sets the units that are displayed for the guide bar
//               labels.  This may be a union of one or more members
//               of the GuideBarUnits enum.
////////////////////////////////////////////////////////////////////
INLINE void PStatGraph::
set_guide_bar_units(int guide_bar_units) {
  if (_guide_bar_units != guide_bar_units) {
    _guide_bar_units = guide_bar_units;
    normal_guide_bars();
  }
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::get_guide_bar_units
//       Access: Public
//  Description: Returns the units that are displayed for the guide bar
//               labels.  This may be a union of one or more members
//               of the GuideBarUnits enum.
////////////////////////////////////////////////////////////////////
INLINE int PStatGraph::
get_guide_bar_units() const {
  return _guide_bar_units;
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::set_guide_bar_unit_name
//       Access: Public
//  Description: Sets the name of the units to be used for the guide
//               bars if the units type is set to GBU_named |
//               GBU_show_units.
////////////////////////////////////////////////////////////////////
INLINE void PStatGraph::
set_guide_bar_unit_name(const string &unit_name) {
  _unit_name = unit_name;
}

////////////////////////////////////////////////////////////////////
//     Function: PStatGraph::get_guide_bar_unit_name
//       Access: Public
//  Description: Returns the name of the units to be used for the guide
//               bars if the units type is set to GBU_named |
//               GBU_show_units.
////////////////////////////////////////////////////////////////////
INLINE const string &PStatGraph::
get_guide_bar_unit_name() const {
  return _unit_name;
}
