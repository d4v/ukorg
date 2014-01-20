#include <iostream>
#include "ClockEvent.h"

using namespace std;
using namespace ukorg;

static unsigned short tickCount = 0;

#define TEMPO_SUBDIVISION 24

void ClockEvent::cat(const unsigned char) {}

bool ClockEvent::ready() {
  return true;
}

void ClockEvent::action() {
  if(++tickCount == TEMPO_SUBDIVISION) {
//    cerr << "Tick!" << endl;
    tickCount = 0;
  }
}

