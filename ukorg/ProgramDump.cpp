#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "utils.h"
#include "ProgramDump.h"
#include "ProgMsg.h"

using namespace std;
using namespace ukorg;

ProgramDump::ProgramDump(void *msg) {
  progMsg = (ProgMsg*) malloc(sizeof(ProgMsg));
  *progMsg = *((ProgMsg*) msg);
}

ProgramDump::~ProgramDump() {
  free(progMsg);
}

void ProgramDump::action() {
  print();
  save();
}

void ProgramDump::save() {

  ofstream ofs;
  ofs.open ("out.out", ofstream::out | ofstream::binary);

  ofs.write((char*) progMsg,sizeof(ProgMsg));

  ofs.close();

}

void ProgramDump::print() {

  cout << "ProgramDump::ProgramDump" << endl;
  cout << "Program name : " << progMsg->name << endl;

  VoiceMode mode = getVoiceMode(progMsg);

  switch(mode) {
    case VOICE_MODE_SINGLE :
      cout << "voice mode single" << endl;
      break;
    case VOICE_MODE_LAYER:
      cout << "voice mode layer" << endl;
      break;
    case VOICE_MODE_VOCODER:
      cout << "voice mode vocoder" << endl;
      break;
    default:
      cout << "Voice mode wtf?" << endl;
      break;
  }

  cout << "Arpeggio byte : " << bitdump(progMsg->arpOnOff) << endl;
  bool arpOnOff = (progMsg->arpOnOff & 0x80) >> 7;
  cout << "  on/off : " << arpOnOff << endl;

  bool arpSync = progMsg->arpOnOff & 0x01;
  cout << "  key sync : " << arpSync << endl;

  bool arpLatch = (progMsg->arpOnOff & 0x40) >> 6;
  cout << "  latch : " << arpLatch << endl;

  cout << "  swing : " << dec << (int) (progMsg->arpSwing) << endl;

  cout << "ArpType byte : " << bitdump(progMsg->arpType) << endl;
  int arpType = progMsg->arpType & 0x07;
  cout << "  arpType : " << arpType << endl;
  int range = (progMsg->arpType & 0xF0) >> 4; 
  cout << "  range : " << range << endl;

  cout << "Kbd octave : " << (int) progMsg->kbdOctave << endl;

  bool delaySync = (progMsg->delayTime & 0x80) >> 7;

  cout << "DelaySync : " << delaySync << endl;
}
