#include "MidiEventFactory.h"
#include "ClockEvent.h"
#include "SysExEvent.h"

using namespace std;
using namespace ukorg;

#define NOTE_OFF  0x80
#define NOTE_ON   0x90
#define ACTIVE_SENSING 0xFE
#define TIMING_CLOCK 0xF8
#define SYSTEM_EXCLUSIVE 0xF0

MidiEvent *MidiEventFactory::build(const unsigned char status) {
  MidiEvent *ev = 0;
  if(status == TIMING_CLOCK) {
    ev = new ClockEvent();
  } else
  if(status == ACTIVE_SENSING) {
    // TODO
  } else
  if(status == SYSTEM_EXCLUSIVE) {
    ev = new SysExEvent();
  } else {
    ev = new GenericEvent(status);
  }

  return ev;
}

