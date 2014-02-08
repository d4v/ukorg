#ifndef PROG_MSG_H
#define PROG_MSG_H

typedef struct _ProgMsg ProgMsg;

extern const size_t c_ProgMsgSize;

//
// Basics panel
//

typedef enum _VoiceMode {
  VOICE_MODE_SINGLE  = 0,
  VOICE_MODE_LAYER   = 2,
  VOICE_MODE_VOCODER = 3
} VoiceMode;

VoiceMode getVoiceMode(const ProgMsg *msg);

typedef enum {
  TIMBRE_1,
  TIMBRE_2
} VoiceLayer;

typedef enum {
  ARP_TYPE_UP,
  ARP_TYPE_DOWN,
  ARP_TYPE_ALT1,
  ARP_TYPE_ALT2,
  ARP_TYPE_RND,
  ARP_TYPE_TRG
} ArpType;

//
// Voice Panel
//

typedef enum {
  ASSIGN_MODE_MONO,
  ASSIGN_MODE_POLY,
  ASSIGN_MODE_UNISON
} AssignMode;

AssignMode getAssignMode(VoiceLayer layer,const ProgMsg *msg);

typedef enum {
  TRIGGER_MODE_SINGLE,
  TRIGGER_MODE_MULTI
} TriggerMode;

TriggerMode getTriggerMode(VoiceLayer layer, const ProgMsg *msg);
int getUnisonDetune(VoiceLayer layer, const ProgMsg *msg);

//
// Pitch Panel
//

int getTranspose(VoiceLayer layer, const ProgMsg *msg);
int getTune(VoiceLayer layer, const ProgMsg *msg);
int getPortamento(VoiceLayer layer, const ProgMsg *msg);
int getBendRange(VoiceLayer layer, const ProgMsg *msg);
int getVibratoInt(VoiceLayer layer, const ProgMsg *msg);

//
//Oscillator 1
//

typedef enum {
  WAV_SAW,
  WAV_SQUARE,
  WAV_TRIANGLE,
  WAV_SINE,
  WAV_VOX,
  WAV_DWGS, // Digital Waveform Generator System
  WAV_NOISE,
  WAV_AUDIOIN
} WaveType;

WaveType getOsc1WaveType(VoiceLayer layer, const ProgMsg *msg);

int getOsc1Ctrl1(VoiceLayer layer, const ProgMsg *msg);
int getOsc1Ctrl2(VoiceLayer layer, const ProgMsg *msg);

typedef enum {
  DWGS_SYNSINE1,DWGS_SYNSINE2,DWGS_SYNSINE3,DWGS_SYNSINE4,
  DWGS_SYNSINE5,DWGS_SYNSINE6,DWGS_SYNSINE7,DWGS_SYNBASS1,
  DWGS_SYNBASS2,DWGS_SYNBASS3,DWGS_SYNBASS4,DWGS_SYNBASS5,
  DWGS_SYNBASS6,DWGS_SYNBASS7,DWGS_SYNWAVE1,DWGS_SYNWAVE2,
  DWGS_SYNWAVE3,DWGS_SYNWAVE4,DWGS_SYNWAVE5,DWGS_SYNWAVE6,
  DWGS_SYNWAVE7,DWGS_SYNWAVE8,DWGS_SYNWAVE9,DWGS_5THWAVE1,
  DWGS_5THWAVE2,DWGS_5THWAVE3,DWGS_DIGI1   ,DWGS_DIGI2   ,
  DWGS_DIGI3   ,DWGS_DIGI4   ,DWGS_DIGI5   ,DWGS_DIGI6   ,
  DWGS_DIGI7   ,DWGS_DIGI8   ,DWGS_ENDLESS ,DWGS_E_PIANO1,
  DWGS_E_PIANO2,DWGS_E_PIANO3,DWGS_E_PIANO4,DWGS_ORGAN1  ,
  DWGS_ORGAN2  ,DWGS_ORGAN3  ,DWGS_ORGAN4  ,DWGS_ORGAN5  ,
  DWGS_ORGAN6  ,DWGS_ORGAN7  ,DWGS_CLAV1   ,DWGS_CLAV2   ,
  DWGS_GUITAR1 ,DWGS_GUITAR2 ,DWGS_GUITAR3 ,DWGS_BASS1   ,
  DWGS_BASS2   ,DWGS_BASS3   ,DWGS_BASS4   ,DWGS_BASS5   ,
  DWGS_BELL1   ,DWGS_BELL2   ,DWGS_BELL3   ,DWGS_BELL4   ,
  DWGS_VOICE1  ,DWGS_VOICE2  ,DWGS_VOICE3  ,DWGS_VOICE4
} DwgsWave;

DwgsWave getOsc1DwgsWave(VoiceLayer,const ProgMsg *msg);

//
// Oscillator 2
//

WaveType getOsc2WaveType(VoiceLayer layer, const ProgMsg *msg);

typedef enum {
  MOD_OFF,MOD_RING,MOD_RINGSYNC
} ModType;

ModType getOsc2ModType(VoiceLayer layer, const ProgMsg *msg);
int getOsc2Semitone(VoiceLayer layer, const ProgMsg *msg);
int getOsc2Tune(VoiceLayer layer, const ProgMsg *msg);

//
// Mixer
//

int getOsc1Level(VoiceLayer layer, const ProgMsg *msg);
int getOsc2Level(VoiceLayer layer, const ProgMsg *msg);
int getNoiseLevel(VoiceLayer layer, const ProgMsg *msg);

//
// Filter
//

typedef enum {
  FILTER_24LPF,FILTER_12LPF,
  FILTER_12BPF,FILTER_12HPF
} FilterType;

FilterType getFilterType(VoiceLayer layer, const ProgMsg *msg);
int getFilterCutoff(VoiceLayer layer, const ProgMsg *msg);
int getFilterResonance(VoiceLayer layer, const ProgMsg *msg);
int getFilterEgInt(VoiceLayer layer, const ProgMsg *msg);
int getFilterKeyTrack(VoiceLayer layer, const ProgMsg *msg);

//
// Filter Envelope Generator
//

int getFilterEgAttack(VoiceLayer layer, const ProgMsg *msg);
int getFilterEgDecay(VoiceLayer layer, const ProgMsg *msg);
int getFilterEgSustain(VoiceLayer layer, const ProgMsg *msg);
int getFilterEgRelease(VoiceLayer layer, const ProgMsg *msg);

typedef enum {
  EG_RESET_OFF,EG_RESET_ON
} EgResetStatus;

EgResetStatus getFilterEgReset(VoiceLayer layer, const ProgMsg *msg);

//
// Amplifier
//

int getAmpLevel(VoiceLayer layer, const ProgMsg *msg);
int getAmpPanPot(VoiceLayer layer, const ProgMsg *msg);

typedef enum {
  AMP_DIST_OFF,AMP_DIST_ON
} AmpDistStatus;

AmpDistStatus getAmpDistortion(VoiceLayer layer, const ProgMsg *msg);
int getAmpKbdTrack(VoiceLayer layer, const ProgMsg *msg);

//
// Amplifier Envelope Generator
//

int getAmpEgAttack(VoiceLayer layer, const ProgMsg *msg);
int getAmpEgDecay(VoiceLayer layer, const ProgMsg *msg);
int getAmpEgSustain(VoiceLayer layer, const ProgMsg *msg);
int getAmpEgRelease(VoiceLayer layer, const ProgMsg *msg);
EgResetStatus getAmpEgReset(VoiceLayer layer, const ProgMsg *msg);

#endif // PROG_MSG_H
