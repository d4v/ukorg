#include "ProgMsg.h"

VoiceMode getVoiceMode(const ProgMsg *msg) {
  int mode = msg->voiceMode & 0x30; // 0011 0000
  return (VoiceMode) (mode >> 4);
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

