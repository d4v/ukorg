#include <iostream>
#include "MidiEvent.h"

using namespace std;
using namespace ukorg;

void MidiEvent::free(MidiEvent *ev) {
  //TODO
}

void GenericEvent::cat(const unsigned char c) {
  // Shouldn't happen
}

GenericEvent::GenericEvent(unsigned char c) : status(c) {}

bool GenericEvent::ready() {
  return true;
}

void GenericEvent::action() {
  cout << "Generic event : " << hex << (int) status << endl;
}

