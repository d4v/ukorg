#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <iostream>
#include "MidiDevice.h"
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

void *MidiDevice::readRoutine(void *arg) {
  MidiDevice *dev = (MidiDevice*) arg;

  cout << "ReadThread" << endl;
  static const size_t bufSize = 512;
  int nbRead = 0;
  char buf[bufSize];

  while((nbRead = read(dev->mFileDesc,buf,bufSize)) > 0) {

    for(int idx = 0; idx < nbRead; idx++) {
      unsigned char c = buf[idx];
      switch(c) {
        case MIDI_REALTIME_TIMING_CLOCK :
          pthread_mutex_lock(&dev->mEvQueueMutex);
          dev->mEvQueue.push(new ClockEvent());
          pthread_cond_signal(&dev->mEvQueueCond);
          pthread_mutex_unlock(&dev->mEvQueueMutex);
          break;
        case MIDI_REALTIME_ACTIVE_SENSING:
          /** Device is alive, nothing else to do */
          break;
        default:
          cerr << "Unknown midi msg : " << hex << (int) c << endl;
      }
    }
  }

  return 0;
}

MidiDevice::MidiDevice() {
  pthread_cond_init(&mEvQueueCond,0);
  pthread_mutex_init(&mEvQueueMutex,0);

  // FIXME, What if several midi devices?
  mFileDesc = open("/dev/midi",0);
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

