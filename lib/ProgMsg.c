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
  int mode = msg->params.synths.timbre[layer].assignMode;

  mode >>= 3;
  mode &= 0x01; // 0000 0001
  return (TriggerMode) (mode);
}

AssignMode getAssignMode(VoiceLayer layer,const ProgMsg *msg) {
  int mode = msg->params.synths.timbre[layer].assignMode;

  mode >>= 6;
  mode &= 0x03; // 0000 0011
  return (AssignMode) mode;
}

int getUnisonDetune(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].unisonDetune;
}

int getTranspose(VoiceLayer layer, const ProgMsg *msg) {
  return (msg->params.synths.timbre[layer].pitchBendTranspose - 64);
}

int getTune(VoiceLayer layer, const ProgMsg *msg) {
  return (msg->params.synths.timbre[layer].pitchTune - 64);
}

int getPortamento(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].portamentoTime;
}

int getBendRange(VoiceLayer layer, const ProgMsg *msg) {
  return (msg->params.synths.timbre[layer].pitchBendRange - 64);
}

int getVibratoInt(VoiceLayer layer, const ProgMsg *msg) {
  return (msg->params.synths.timbre[layer].pitchVibratoInt - 64);
}

