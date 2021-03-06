// Filename: movingPart.h
// Created by:  drose (22Feb99)
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

#ifndef MOVINGPART_H
#define MOVINGPART_H

#include "pandabase.h"

#include "movingPartBase.h"
#include "animChannel.h"

////////////////////////////////////////////////////////////////////
//       Class : MovingPart
// Description : This is the template instantiation of MovingPartBase,
//               on the particular type of value provided by the
//               channel.
////////////////////////////////////////////////////////////////////
template<class SwitchType>
class MovingPart : public MovingPartBase {
public:
  typedef TYPENAME SwitchType::ValueType ValueType;
  typedef AnimChannel<SwitchType> ChannelType;

protected:
  INLINE MovingPart(const MovingPart &copy);

public:
  INLINE MovingPart(PartGroup *parent, const string &name,
                    const ValueType &_initial_value);

  virtual TypeHandle get_value_type() const;
  virtual AnimChannelBase *make_initial_channel() const;
  virtual void output_value(ostream &out) const;

  ValueType _value;
  ValueType _initial_value;

public:
  INLINE virtual void write_datagram(BamWriter* manager, Datagram &me);

protected:
  INLINE MovingPart(void);
  INLINE void fillin(DatagramIterator& scan, BamReader* manager);

public:
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}
PUBLISHED:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  INLINE ValueType get_value() const {
    return _value;
  }
  INLINE ValueType get_initial_value() const {
    return _initial_value;
  }
public:
  static void init_type() {
    MovingPartBase::init_type();
    register_type(_type_handle, SwitchType::get_part_type_name(),
                  MovingPartBase::get_class_type());
  }

private:
  static TypeHandle _type_handle;
};

#include "movingPart.I"

#endif



