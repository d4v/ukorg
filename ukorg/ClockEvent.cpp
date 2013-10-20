#include <iostream>
#include "ClockEvent.h"

using namespace std;
using namespace ukorg;

static unsigned short tickCount = 0;

#define TEMPO_SUBDIVISION 24

void ClockEvent::action() {
  if(++tickCount == TEMPO_SUBDIVISION) {
    cerr << "Tick!" << endl;
    tickCount = 0;
  }
}

