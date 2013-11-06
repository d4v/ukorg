#ifndef MIDI_EVENT_H
#define MIDI_EVENT_H

namespace ukorg {

class MidiEvent {
public:
  virtual ~MidiEvent() {}

  virtual void cat(const unsigned char) = 0;

  virtual bool ready() = 0;

  virtual void action() = 0;

  static void free(MidiEvent *);
};

class GenericEvent : public MidiEvent {
  unsigned char status;
public:
  GenericEvent(unsigned char c);
  virtual ~GenericEvent() {}

  virtual void cat(const unsigned char);

  virtual bool ready();

  virtual void action();
};

}

#endif // MIDI_EVENT_H
