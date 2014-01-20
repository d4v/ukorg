#ifndef CLOCK_EVENT_H
#define CLOCK_EVENT_H

#include "MidiEvent.h"

namespace ukorg {

class ClockEvent : public MidiEvent {
public:
  virtual void cat(const unsigned char);
  virtual bool ready();
  virtual void action();
};

}

#endif // CLOCK_EVENT_H
