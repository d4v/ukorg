#ifndef PROG_MSG_H
#define PROG_MSG_H

typedef struct _ProgMsg ProgMsg;

extern const size_t c_ProgMsgSize;

//
// Basics
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
// Voice
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
// Pitch
//

int getTranspose(VoiceLayer layer, const ProgMsg *msg);
int getTune(VoiceLayer layer, const ProgMsg *msg);
int getPortamento(VoiceLayer layer, const ProgMsg *msg);
int getBendRange(VoiceLayer layer, const ProgMsg *msg);
int getVibratoInt(VoiceLayer layer, const ProgMsg *msg);

//
// Oscillator 1
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

//
// LFO 1
//

typedef enum {
  LFO1_SAW,LFO1_SQUARE1,
  LFO1_TRIANGLE,LFO1_SH
} Lfo1WaveType;

Lfo1WaveType getLfo1WaveType(VoiceLayer layer, const ProgMsg *msg);

typedef enum {
  KSYNC_OFF,KSYNC_TIMBRE,KSYNC_VOICE
} KeySync;

KeySync getLfo1KeySync(VoiceLayer layer, const ProgMsg *msg);

typedef enum {
  TSYNC_OFF,TSYNC_ON
} TempoSync;

TempoSync getLfo1TempoSync(VoiceLayer layer, const ProgMsg *msg);

int getLfo1Frequency(VoiceLayer layer, const ProgMsg *msg);

typedef enum {
  SYNC_1_1 ,SYNC_3_4 ,SYNC_2_3 ,SYNC_1_2 ,
  SYNC_3_8 ,SYNC_1_3 ,SYNC_1_4 ,SYNC_3_16,
  SYNC_1_6 ,SYNC_1_8 ,SYNC_3_32,SYNC_1_12,
  SYNC_1_16,SYNC_1_24,SYNC_1_32
} SyncNote;

SyncNote getLfo1SyncNote(VoiceLayer layer, const ProgMsg *msg);

//
// LFO 2
//

typedef enum {
  LFO2_SAW,LFO2_SQUARE2,
  LFO2_SINE,LFO2_SH
} Lfo2WaveType;

Lfo2WaveType getLfo2WaveType(VoiceLayer layer, const ProgMsg *msg);
KeySync getLfo2KeySync(VoiceLayer layer, const ProgMsg *msg);
TempoSync getLfo2TempoSync(VoiceLayer layer, const ProgMsg *msg);
int getLfo2Frequency(VoiceLayer layer, const ProgMsg *msg);
SyncNote getLfo2SyncNote(VoiceLayer layer, const ProgMsg *msg);

//
// Patch
//

typedef enum {
  PATCH_SRC_FILTER_EG,
  PATCH_SRC_AMP_EG,
  PATCH_SRC_LFO1,
  PATCH_SRC_LFO2,
  PATCH_SRC_VELOCITY,
  PATCH_SRC_KBD_TRACK,
  PATCH_SRC_PITCH_BEND,
  PATCH_SRC_MOD_WHEEL
} PatchSrcType;

typedef enum {
  PATCH_DST_PITCH,
  PATCH_DST_OSC2_TUNE,
  PATCH_DST_OSC1_CTRL1,
  PATCH_DST_NOISE_LEVEL,
  PATCH_DST_CUTOFF,
  PATCH_DST_AMP,
  PATCH_DST_PAN,
  PATCH_DST_LFO2_FREQ
} PatchDstType;

typedef enum {
  PATCH_ID_1 = 0,
  PATCH_ID_2,
  PATCH_ID_3,
  PATCH_ID_4
} PatchIdType;

PatchSrcType getPatchSrc(VoiceLayer, PatchIdType, const ProgMsg *);
PatchDstType getPatchDst(VoiceLayer, PatchIdType, const ProgMsg *);
int getPatchModInt(VoiceLayer, PatchIdType, const ProgMsg *);

#endif // PROG_MSG_H
