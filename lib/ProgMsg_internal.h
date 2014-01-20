#ifndef PROG_MSG_INTERNAL_H
#define PROG_MSG_INTERNAL_H

typedef struct _SynthParams {
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
} SynthParams;

typedef struct _LayeredParams {
  SynthParams timbre1;
  SynthParams timbre2;
} LayeredParams;

typedef struct _VocoderParams {
  // TODO
} VocoderParams;

typedef struct _ProgMsg {
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
//  char params[216];
  union {
    LayeredParams synths;
    VocoderParams vocoder;
  } params;

} ProgMsg;

#endif // PROG_MSG_INTERNAL_H
