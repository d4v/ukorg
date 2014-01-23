#include <stdio.h>
#include <stdlib.h>
#include "ProgMsg_internal.h"
#include "ProgMsg.h"

const size_t c_ProgMsgSize = sizeof(ProgMsg);

VoiceMode getVoiceMode(const ProgMsg *msg) {
  int mode = msg->voiceMode;

  mode >>= 4;
  mode &= 0x03; // 0000 0011
  return (VoiceMode) mode;
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

  mode >>= 3;
  mode &= 0x01; // 0000 0001
  return (TriggerMode) (mode);
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

  mode >>= 6;
  mode &= 0x03; // 0000 0011
  return (AssignMode) mode;
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

