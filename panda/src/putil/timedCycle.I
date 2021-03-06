// Filename: timedCycle.I
// Created by:  jason (01Aug00)
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
//     Function: TimedCycle::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
INLINE TimedCycle::
TimedCycle() :
  _cycle_time(30),
  _inv_cycle_time(1./30),
  _next_switch(-1),
  _current_child(0),
  _element_count(0)
{
  _global_clock = ClockObject::get_global_clock();
}

////////////////////////////////////////////////////////////////////
//     Function: TimedCycle::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
INLINE TimedCycle::
TimedCycle(float cycle_time, int element_count) :
  _cycle_time(cycle_time),
  _current_child(0),
  _element_count(element_count)
{
  nassertv(_cycle_time > 0);
  _global_clock = ClockObject::get_global_clock();
  _next_switch = _global_clock->get_frame_time() + _cycle_time;
  _inv_cycle_time = 1. / _cycle_time;
}

////////////////////////////////////////////////////////////////////
//     Function: TimedCycle::set_element_count
//       Access: Public
//  Description: Set the number of elements being cycled through
////////////////////////////////////////////////////////////////////
INLINE void TimedCycle::
set_element_count(int element_count)
{
  _element_count = element_count;
}

////////////////////////////////////////////////////////////////////
//     Function: TimedCycle::set_cycle_time
//       Access: Public
//  Description: Set the number of elements being cycled through
////////////////////////////////////////////////////////////////////
INLINE void TimedCycle::
set_cycle_time(float cycle_time)
{
  nassertv(cycle_time > 0);
  if (_next_switch == -1)
  {
    _next_switch = _global_clock->get_frame_time() + cycle_time;
  }
  else
  {
    _next_switch = _next_switch - _cycle_time + cycle_time;
  }
  _cycle_time = cycle_time;
  _inv_cycle_time = 1. / _cycle_time;
}


////////////////////////////////////////////////////////////////////
//     Function: TimedCycle::next_element
//       Access: Public
//  Description: Set the number of elements being cycled through
////////////////////////////////////////////////////////////////////
INLINE int TimedCycle::
next_element()
{
  double current_time = _global_clock->get_frame_time();
  unsigned int increment = (unsigned int) ((current_time - _next_switch)
                                           * _inv_cycle_time);

  _next_switch += _cycle_time * increment;
  _current_child = (_current_child + increment) % _element_count;

  return _current_child;
}

