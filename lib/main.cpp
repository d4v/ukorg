#include <stdlib.h>
#include <iostream>
#include "MidiDevice.h"
#include "MidiEvent.h"

using namespace std;
using namespace ukorg;

int main(int argc,char *argv[]) {

  try {
    MidiDevice midiDev;

    while(true) {
      MidiEvent *ev = 0;

      midiDev.nextEvent(&ev);

      ev->action();

      MidiEvent::free(ev);
    }
  } catch (exception &e) {
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}



