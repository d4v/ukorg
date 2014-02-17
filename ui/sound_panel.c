#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "basics_panel.h"
#include "voice_panel.h"
#include "pitch_panel.h"
#include "osc1_panel.h"
#include "osc2_panel.h"
#include "mixer_panel.h"
#include "filter_panel.h"
#include "filtereg_panel.h"
#include "amp_panel.h"
#include "ampeg_panel.h"
#include "lfo1_panel.h"
#include "sound_panel.h"
#include "sound_panel_internal.h"
#include "sound_panel_cb.h"
#include "lib_bindings.h"

SoundPanel *sound_panel_build(GtkBuilder *builder) {

  int layer = 0;
  SoundPanel *panel = (SoundPanel*) malloc(sizeof(SoundPanel));
  
  panel->libSignalHook = gtk_label_new(0);

  panel->basics = basics_panel_build(builder);

  for(layer = 0; layer < 2; layer++) {
    panel->voice[layer]    = voice_panel_build(builder,layer);
    panel->pitch[layer]    = pitch_panel_build(builder,layer);
    panel->osc1[layer]     = osc1_panel_build(builder,layer);
    panel->osc2[layer]     = osc2_panel_build(builder,layer);
    panel->mixer[layer]    = mixer_panel_build(builder,layer);
    panel->filter[layer]   = filter_panel_build(builder,layer);
    panel->filterEg[layer] = filtereg_panel_build(builder,layer);
    panel->amp[layer]      = amp_panel_build(builder,layer);
    panel->ampEg[layer]    = ampeg_panel_build(builder,layer);
    panel->lfo1[layer]     = lfo1_panel_build(builder,layer);
//    panel->lfo2[layer]     = lfo2_panel_build(builder,layer);
  }

  lib_bindings_build(panel);

  sound_panel_cb_build(panel);

  return panel;
}

void sound_panel_set(SoundPanel *panel,const ProgMsg *progMsg) {
  VoiceLayer layer = TIMBRE_1;

  basics_panel_set(panel->basics,progMsg);

  for(layer = 0; layer < 2; layer++) {
    voice_panel_set(panel->voice[layer],progMsg);
    pitch_panel_set(panel->pitch[layer],progMsg);
    osc1_panel_set(panel->osc1[layer],progMsg);
    osc2_panel_set(panel->osc2[layer],progMsg);
    mixer_panel_set(panel->mixer[layer],progMsg);
    filter_panel_set(panel->filter[layer],progMsg);
    filtereg_panel_set(panel->filterEg[layer],progMsg);
    amp_panel_set(panel->amp[layer],progMsg);
    ampeg_panel_set(panel->ampEg[layer],progMsg);
    lfo1_panel_set(panel->lfo1[layer],progMsg);
  }
}

