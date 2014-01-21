#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <iostream>
#include "MidiDevice.h"
#include "MidiEventFactory.h"
#include "ClockEvent.h"

using namespace std;
using namespace ukorg;

class MidiDeviceException : public exception {
  const string mDetails;

public:
  MidiDeviceException(const string &details) : mDetails(details) {}
  virtual ~MidiDeviceException() throw() {}

  virtual const char* what() const throw() {
    string out = string("Midi device exception - ") + mDetails;
    return out.c_str();
  }
};

#define MIDI_STATUS_MASK 0x80 /* 1000 0000 */
#define MIDI_REALTIME_TIMING_CLOCK   0xF8
#define MIDI_REALTIME_ACTIVE_SENSING 0xFE
#define MIDI_END_OF_EXCLUSIVE 0xF7

void MidiDevice::pushEvent(MidiDevice *dev,MidiEvent *ev) {
  pthread_mutex_lock(&dev->mEvQueueMutex);
  dev->mEvQueue.push(ev);
  pthread_cond_signal(&dev->mEvQueueCond);
  pthread_mutex_unlock(&dev->mEvQueueMutex);
}

void *MidiDevice::readRoutine(void *arg) {
  MidiDevice *dev = (MidiDevice*) arg;

  cerr << "ReadThread" << flush << endl;
  unsigned char c = 0x00;
  int nbRead = 0;
  MidiEventFactory evFactory;
  MidiEvent *pending = 0;

  while((nbRead = read(dev->mFileDesc,&c,1)) > 0) {
    if(c == MIDI_REALTIME_TIMING_CLOCK) {
      /** Simply push a new clock event */
      pushEvent(dev,new ClockEvent());
    } else
    if(c == MIDI_REALTIME_ACTIVE_SENSING) {
      /** Device is alive, nothing else to do */
    } else
    if(    (c &  MIDI_STATUS_MASK)
        && (c != MIDI_END_OF_EXCLUSIVE) ) {
      /** Status mask means new event */
      if(pending) {
        /** An event is already pending */
        cerr << "Unexpected Status message received :"
             << hex << (int) c << endl;
        delete pending;
      }
      /** Build a new event */
      pending = evFactory.build(c);
    } else {
      /** An event should be pending */
      if(pending) {
        pending->cat(c);
      } else {
        cerr << "Unknown message received : "
             << hex << (int) c << endl;
      }
    }

    if(pending && pending->ready()) {
      pushEvent(dev,pending);
      pending = 0;
    }
  }

  return 0;
}

MidiDevice::MidiDevice() {
  pthread_cond_init(&mEvQueueCond,0);
  pthread_mutex_init(&mEvQueueMutex,0);

  // FIXME, What if several midi devices?
//  mFileDesc = open("/dev/midi1",O_RDWR);
  mFileDesc = open("midi1",O_RDWR);
  if(mFileDesc < 0) {
    string msg = string("Failed to open midi device: ") + strerror(errno);
    throw MidiDeviceException(msg);
  }
  
  pthread_create(&mReadThread,0,readRoutine,this);
}

void MidiDevice::nextEvent(MidiEvent ** ev) {
  pthread_mutex_lock(&mEvQueueMutex);
  while(mEvQueue.empty()) {
    pthread_cond_wait(&mEvQueueCond,&mEvQueueMutex);
  }
  *ev = mEvQueue.front();
  mEvQueue.pop();

  // TODO return false if timedwait > 600ms
  pthread_mutex_unlock(&mEvQueueMutex);
}

MidiDevice::~MidiDevice() {
  close(mFileDesc);
}

