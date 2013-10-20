#ifndef CLOCK_EVENT_H
#define CLOCK_EVENT_H

#include "MidiEvent.h"

namespace ukorg {

class ClockEvent : public MidiEvent {
public:
  virtual void action();
};

}

#endif // CLOCK_EVENT_H
