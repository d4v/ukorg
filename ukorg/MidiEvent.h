#ifndef MIDI_EVENT_H
#define MIDI_EVENT_H

namespace ukorg {

class MidiEvent {

public:
  virtual void action() = 0;

  static void free(MidiEvent *);
};

}

#endif // MIDI_EVENT_H
