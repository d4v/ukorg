#ifndef PROG_MSG_H
#define PROG_MSG_H

typedef struct _ProgMsg ProgMsg;

extern const size_t c_ProgMsgSize;

typedef enum _VoiceMode {
  VOICE_MODE_SINGLE  = 0,
  VOICE_MODE_LAYER   = 2,
  VOICE_MODE_VOCODER = 3
} VoiceMode;

#ifdef __cplusplus
extern "C"
#endif
VoiceMode getVoiceMode(const ProgMsg *msg);

typedef enum {
  TIMBRE_1,
  TIMBRE_2
} VoiceLayer;

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

int getTranspose(VoiceLayer layer, const ProgMsg *msg);

int getTune(VoiceLayer layer, const ProgMsg *msg);

int getPortamento(VoiceLayer layer, const ProgMsg *msg);

int getBendRange(VoiceLayer layer, const ProgMsg *msg);

int getVibratoInt(VoiceLayer layer, const ProgMsg *msg);

typedef enum {
  ARP_TYPE_UP,
  ARP_TYPE_DOWN,
  ARP_TYPE_ALT1,
  ARP_TYPE_ALT2,
  ARP_TYPE_RND,
  ARP_TYPE_TRG
} ArpType;

#endif // PROG_MSG_H
