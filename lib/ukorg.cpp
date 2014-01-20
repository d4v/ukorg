#include <pthread.h>
#include <iostream>
#include "MidiDevice.h"
#include "MidiEvent.h"
#include "ukorg_internal.h"

using namespace std;
using namespace ukorg;

static vector<ukorg_listener*> ukorg_listeners;

const vector<ukorg_listener*> &ukorg_get_listeners() {
  return ukorg_listeners;
}

ukorg_listener *ukorg_register_listener(struct ukorg_callbacks* cbs,
                                        void *user_data) {
  ukorg_listener *listener = new ukorg_listener;

  listener->callbacks = cbs;
  listener->user_data = user_data;

  ukorg_listeners.push_back(listener);
  return listener;
}

void * ukorg_routine(void *user_data) {
  MidiDevice *dev = (MidiDevice *) user_data;
  try {
    while(true) {
      MidiEvent *ev = 0;

      dev->nextEvent(&ev);

      ev->action();

      MidiEvent::free(ev);
    }
  } catch (exception &e) {
    cerr << e.what() << endl;
  }

  return 0;
}

static pthread_t   ukorg_thread;
static MidiDevice *ukorg_device;

void ukorg_start() {
  try {
    ukorg_device = new MidiDevice;

    if(pthread_create(&ukorg_thread,0,ukorg_routine,ukorg_device)) {
      cerr << "Failed to create listening thread" << endl;
    }
  } catch (exception &e) {
    cerr << e.what() << endl;
  }
}


