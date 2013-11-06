#ifndef MIDI_DEVICE_H
#define MIDI_DEVICE_H

#include <queue>

namespace ukorg {

class MidiEvent;

class MidiDevice {
  int mFileDesc;
  pthread_t mReadThread;
  std::queue<MidiEvent*> mEvQueue;
  pthread_cond_t  mEvQueueCond;
  pthread_mutex_t mEvQueueMutex;

public:
  MidiDevice();
  virtual ~MidiDevice();
  
  void nextEvent(MidiEvent **);

private:
  static void pushEvent(MidiDevice *,MidiEvent *);
  static void *readRoutine(void *args);
};

}

#endif // MIDI_DEVICE_H
