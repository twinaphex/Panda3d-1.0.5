// Filename: pStatView.h
// Created by:  drose (10Jul00)
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

#ifndef PSTATVIEW_H
#define PSTATVIEW_H

#include "pandatoolbase.h"

#include "pStatClientData.h"
#include "pStatThreadData.h"
#include "pStatViewLevel.h"

#include "pointerTo.h"

////////////////////////////////////////////////////////////////////
//       Class : PStatView
// Description : A View boils down the frame data to a linear list of
//               times spent in a number of different Collectors,
//               within a particular thread.  This automatically
//               accounts for overlapping start/stop times and nested
//               Collectors in a sensible way.
////////////////////////////////////////////////////////////////////
class PStatView {
public:
  PStatView();
  ~PStatView();

  void constrain(int collector, bool show_level);
  void unconstrain();

  void set_thread_data(const PStatThreadData *thread_data);
  INLINE const PStatThreadData *get_thread_data();
  INLINE const PStatClientData *get_client_data();

  void set_to_frame(const PStatFrameData &frame_data);
  INLINE void set_to_frame(int frame_number);
  INLINE void set_to_time(float time);

  bool all_collectors_known() const;
  float get_net_value() const;

  const PStatViewLevel *get_top_level();

  bool has_level(int collector) const;
  PStatViewLevel *get_level(int collector);
 
  INLINE bool get_show_level() const;
  INLINE int get_level_index() const;

private:
  void update_time_data(const PStatFrameData &frame_data);
  void update_level_data(const PStatFrameData &frame_data);

  void clear_levels();
  bool reset_level(PStatViewLevel *level);

  int _constraint;
  bool _show_level;
  bool _all_collectors_known;

  typedef pmap<int, PStatViewLevel *> Levels;
  Levels _levels;

  int _level_index;

  CPT(PStatClientData) _client_data;
  CPT(PStatThreadData) _thread_data;
};

#include "pStatView.I"

#endif

