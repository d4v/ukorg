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

WaveType getOsc1WaveType(VoiceLayer layer, const ProgMsg *msg) {
  return (WaveType) msg->params.synths.timbre[layer].osc1Wave;
}

int getOsc1Ctrl1(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].osc1WaveformCtrl1;
}

int getOsc1Ctrl2(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].osc1WaveformCtrl2;
}

DwgsWave getOsc1DwgsWave(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].osc1DgwsWave;
}

WaveType getOsc2WaveType(VoiceLayer layer, const ProgMsg *msg) {
  int wave = msg->params.synths.timbre[layer].osc2Wave;

  wave &= 0x03; // 0000 0011
  return (WaveType) wave;
}

ModType getOsc2ModType(VoiceLayer layer, const ProgMsg *msg) {
  int mod = msg->params.synths.timbre[layer].osc2Wave;

  mod >>= 4;
  mod &= 0x03; // 0000 0011
  return (ModType) mod;
}

int getOsc2Semitone(VoiceLayer layer, const ProgMsg *msg) {
  return (msg->params.synths.timbre[layer].osc2Semitone - 64);
}

int getOsc2Tune(VoiceLayer layer, const ProgMsg *msg) {
  return (msg->params.synths.timbre[layer].osc2Tune - 64);
}

int getOsc1Level(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].osc1Level;
}

int getOsc2Level(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].osc2Level;
}

int getNoiseLevel(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].noiseLevel;
}

FilterType getFilterType(VoiceLayer layer, const ProgMsg *msg) {
  return (FilterType) msg->params.synths.timbre[layer].filterType;
}

int getFilterCutoff(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].filterCutoff;
}

int getFilterResonance(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].filterResonance;
}

int getFilterEgInt(VoiceLayer layer, const ProgMsg *msg) {
  return (msg->params.synths.timbre[layer].filterEg1Int - 64);
}

int getFilterKeyTrack(VoiceLayer layer, const ProgMsg *msg) {
  return (msg->params.synths.timbre[layer].filterKbdTrack - 64);
}

int getFilterEgAttack(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].eg1Attack;
}

int getFilterEgDecay(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].eg1Decay;
}

int getFilterEgSustain(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].eg1Sustain;
}

int getFilterEgRelease(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].eg1Release;
}

EgResetStatus getFilterEgReset(VoiceLayer layer, const ProgMsg *msg) {
  int status = msg->params.synths.timbre[layer].assignMode;

  status >>= 4;
  status &= 0x01; // 0000 0001
  return (EgResetStatus) status;
}

int getAmpLevel(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].ampLevel;
}

int getAmpPanPot(VoiceLayer layer, const ProgMsg *msg) {
  return (msg->params.synths.timbre[layer].ampPanpot - 64);
}

AmpDistStatus getAmpDistortion(VoiceLayer layer, const ProgMsg *msg) {
  int status = msg->params.synths.timbre[layer].ampDistortion;

  status &= 0x01; // 0000 0001
  return (AmpDistStatus) status;
}

int getAmpKbdTrack(VoiceLayer layer, const ProgMsg *msg) {
  return (msg->params.synths.timbre[layer].ampKeyboardTrack - 64);
}

int getAmpEgAttack(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].eg2Attack;
}

int getAmpEgDecay(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].eg2Decay;
}

int getAmpEgSustain(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].eg2Sustain;
}

int getAmpEgRelease(VoiceLayer layer, const ProgMsg *msg) {
  return msg->params.synths.timbre[layer].eg2Release;
}

EgResetStatus getAmpEgReset(VoiceLayer layer, const ProgMsg *msg) {
  int status = msg->params.synths.timbre[layer].assignMode;

  status >>= 5;
  status &= 0x01;
  return (EgResetStatus) status;
}

Lfo1WaveType getLfo1WaveType(VoiceLayer layer, const ProgMsg *msg){
  int type = msg->params.synths.timbre[layer].lfo1Wave;

  type &= 0x03; // 0000 0011
  return (Lfo1WaveType) type;
}

KeySync getLfo1KeySync(VoiceLayer layer, const ProgMsg *msg){
  int sync = msg->params.synths.timbre[layer].lfo1Wave;

  sync >>= 4;
  sync &= 0x03;
  return (KeySync) sync;
}

TempoSync getLfo1TempoSync(VoiceLayer layer, const ProgMsg *msg){
  int sync = msg->params.synths.timbre[layer].lfo1Sync;

  sync >>= 7;
  sync &= 0x01;
  return (TempoSync) sync;
}

int getLfo1Frequency(VoiceLayer layer, const ProgMsg *msg){
  return msg->params.synths.timbre[layer].lfo1Freq;
}

SyncNote getLfo1SyncNote(VoiceLayer layer, const ProgMsg *msg){
  int sync = msg->params.synths.timbre[layer].lfo1Sync;

  sync &= 0x1F; // 0001 1111
  return (SyncNote) sync;
}

Lfo2WaveType getLfo2WaveType(VoiceLayer layer, const ProgMsg *msg){
  int type = msg->params.synths.timbre[layer].lfo2Wave;

  type &= 0x03; // 0000 0011
  return (Lfo2WaveType) type;
}

KeySync getLfo2KeySync(VoiceLayer layer, const ProgMsg *msg){
  int sync = msg->params.synths.timbre[layer].lfo2Wave;

  sync >>= 4;
  sync &= 0x03;
  return (KeySync) sync;
}

TempoSync getLfo2TempoSync(VoiceLayer layer, const ProgMsg *msg){
  int sync = msg->params.synths.timbre[layer].lfo2Sync;

  sync >>= 7;
  sync &= 0x01;
  return (TempoSync) sync;
}

int getLfo2Frequency(VoiceLayer layer, const ProgMsg *msg){
  return msg->params.synths.timbre[layer].lfo2Freq;
}

SyncNote getLfo2SyncNote(VoiceLayer layer, const ProgMsg *msg){
  int sync = msg->params.synths.timbre[layer].lfo2Sync;

  sync &= 0x1F; // 0001 1111
  return (SyncNote) sync;
}

