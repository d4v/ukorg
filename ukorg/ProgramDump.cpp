#include <iostream>
#include "utils.h"
#include "ProgramDump.h"

using namespace std;
using namespace ukorg;

struct ukorg::_ProgMsg {
  // Program name
  char name[12];
  char pad1[2];

  // 14 ~ 15 Arpeggio
  char trigger;
  char pattern;

  // 16 Voice mode
  char voiceMode;

  // 17 Scale
  char scale;
  char pad2;

  // 19 ~ 22 Delay FX
  char delaySync;
  char delayTime;
  char delayDepth;
  char delayType;

  // 23 ~ 25 Mod FX
  char modLfoSpeed;
  char modDepth;
  char modType;

  // 26 ~ 29 EQ
  char eqHiFreq;
  char eqHiGain;
  char eqLoFreq;
  char eqLoGain;

  // 30 ~ 36 Arpeggio
  char arpTempo[2];
  char arpOnOff;
  char arpType;
  char arpGateTime;
  char arpResolution;
  char arpSwing;

  // 37 KBD octave
  char kbdOctave;

  // 38 ~ 253 timbre 1,2,vocoder
  char params[216];
};

struct ukorg::_SynthParams {
  char midiChannel;
  char assignMode;
  char unisonDetune;

  // 3 ~ 6 PITCH
  char pitchTune;
  char pitchBendRange;
  char pitchBendTranspose;
  char pitchVibratoInt;

  // 7 ~ 11 OSC1
  char osc1Wave;
  char osc1WaveformCtrl1;
  char osc1WaveformCtrl2;
  char osc1DgwsWave;

  char pad1;

  // 12 ~ 14 OSC2
  char osc2Wave;
  char osc2Semitone;
  char osc2Tune;

  // 15 PITCH 2
  char portamentoTime;

  // 16 ~ 18 MIXER
  char osc1Level;
  char osc2Level;
  char noise;


  // 19 ~ 24 FILTER
  char filterType;
  char filterCutoff;
  char filterResonance;
  char filterEg1Int;
  char filterVelocitySense;
  char filterKbdTrack;

  // 25 ~ 29 AMP
  char ampLevel;
  char ampPanpot;
  char ampDistortion;
  char ampVelocitySense;
  char ampKeyboardTrack;

  // 30 ~ 33 EG1
  char eg1Attack;
  char eg1Decay;
  char eg1Sustain;
  char eg1Release;

  // 34 ~ 37 EG2
  char eg2Attack;
  char eg2Decay;
  char eg2Sustain;
  char eg2Release;

  // 38 ~ 40 LFO1
  char lfo1Wave;
  char lfo1Freq;
  char lfo1Sync;

  // 41 ~ 43 LFO2
  char lfo2Wave;
  char lfo2Freq;
  char lfo2Sync;

  // 44 ~ 51 PATCH
  char patch1SrcDst;
  char patch1Int;
  char patch2SrcDst;
  char patch2Int;
  char patch3SrcDst;
  char patch3Int;
  char patch4SrcDst;
  char patch4Int;
  
  // 52 ~ 107 dummy
  char pad2[46];
};


typedef enum {
  VOICE_MODE_SINGLE  = 0,
  VOICE_MODE_LAYER   = 2,
  VOICE_MODE_VOCODER = 3
} VoiceMode;

VoiceMode getVoiceMode(unsigned char byte) {
  byte &= 0x30; // 0011 0000
  return (VoiceMode) (byte >> 4);
}

typedef enum {
  ARP_TYPE_UP,
  ARP_TYPE_DOWN,
  ARP_TYPE_ALT1,
  ARP_TYPE_ALT2,
  ARP_TYPE_RND,
  ARP_TYPE_TRG
} ArpType;

void ProgramDump::init(void *msg) {
  progMsg = new ProgMsg;
  *progMsg = *((ProgMsg*) msg);

  cout << "ProgramDump::init" << endl;
  cout << "Program name : " << progMsg->name << endl;

  VoiceMode mode = getVoiceMode(progMsg->voiceMode);

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
