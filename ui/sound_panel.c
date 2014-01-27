#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "basics_panel.h"
#include "voice_panel.h"
#include "pitch_panel.h"
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
    voice_panel_build(builder,layer,&panel->voice[layer]);
    pitch_panel_build(builder,layer,&panel->pitch[layer]);
  }

  lib_bindings_build(panel);

  sound_panel_cb_build(panel);

  return panel;
}

void sound_panel_set(SoundPanel *panel,const ProgMsg *progMsg) {
  VoiceLayer layer = TIMBRE_1;
  AssignMode assignMode;
  

  basics_panel_set(panel->basics,progMsg);

  for(layer = 0; layer < 2; layer++) {
    switch(assignMode = getAssignMode(layer,progMsg)) {
      case ASSIGN_MODE_MONO :
        set_combo_box_value(panel->voice[layer].combobox_assign,ASSIGN_MODE_MONO);
        break;
      case ASSIGN_MODE_POLY :
        set_combo_box_value(panel->voice[layer].combobox_assign,ASSIGN_MODE_POLY);
        break;
      case ASSIGN_MODE_UNISON :
        set_combo_box_value(panel->voice[layer].combobox_assign,ASSIGN_MODE_UNISON);
        break;
    };

    switch(getTriggerMode(layer,progMsg)) {
      case TRIGGER_MODE_SINGLE :
        set_combo_box_value(panel->voice[layer].combobox_trigger,TRIGGER_MODE_SINGLE);
        break;
      case TRIGGER_MODE_MULTI :
        set_combo_box_value(panel->voice[layer].combobox_trigger,TRIGGER_MODE_MULTI);
        break;
    }

    gtk_widget_set_sensitive(panel->voice[layer].scale_detune,
        assignMode == ASSIGN_MODE_UNISON ? 1 : 0);
    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->voice[layer].adjust_detune),
        getUnisonDetune(layer,progMsg));

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->pitch[layer].adjust_transpose),
        getTranspose(layer,progMsg));

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->pitch[layer].adjust_tune),
        getTune(layer,progMsg));

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->pitch[layer].adjust_portamento),
        getPortamento(layer,progMsg));

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->pitch[layer].adjust_bendrange),
        getBendRange(layer,progMsg));

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->pitch[layer].adjust_vibratoint),
        getVibratoInt(layer,progMsg));

  }

}


