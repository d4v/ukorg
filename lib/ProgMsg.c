#include "ProgMsg_internal.h"
#include "ProgMsg.h"

VoiceMode getVoiceMode(const ProgMsg *msg) {
  int mode = msg->voiceMode & 0x30; // 0011 0000
  return (VoiceMode) (mode >> 4);
}

TriggerMode getTriggerMode(VoiceLayer layer, const ProgMsg *msg) {
  int mode = 0;
  switch(layer) {
    case TIMBRE_1:
      mode = msg->params.synths.timbre1.assignMode;
      break;
    case TIMBRE_2:
      mode = msg->params.synths.timbre2.assignMode;
      break;
  }

  mode &= 0x08; // 0000 1000
  return (TriggerMode) (mode >> 3);
}

AssignMode getAssignMode(VoiceLayer layer,const ProgMsg *msg) {
  int mode = 0;
  switch(layer) {
    case TIMBRE_1:
      mode = msg->params.synths.timbre1.assignMode;
      break;
    case TIMBRE_2:
      mode = msg->params.synths.timbre2.assignMode;
  }

  mode &= 0xB0; // 1100 0000
  return (AssignMode) (mode >> 6);
}

int getUnisonDetune(VoiceLayer layer, const ProgMsg *msg) {
  switch(layer) {
    case TIMBRE_1:
    default:
      return msg->params.synths.timbre1.unisonDetune;
    case TIMBRE_2:
      return msg->params.synths.timbre2.unisonDetune;
  }
}

