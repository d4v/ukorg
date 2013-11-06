#ifndef MIDI_EVENT_FACTORY_H
#define MIDI_EVENT_FACTORY_H

#include "MidiEvent.h"

namespace ukorg {

class MidiEventFactory {
public:
  MidiEvent *build(const unsigned char status);
};

}

#endif // MIDI_EVENT_FACTORY_H
