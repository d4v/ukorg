#include "basics_panel.h"
#include "util.h"
#include "sound_panel_internal.h"

void basics_panel_unset(SoundPanel *panel) {
  switch(panel->voiceMode) {
    case VOICE_MODE_SINGLE :
      gtk_container_remove(GTK_CONTAINER(panel->box_params_slot),panel->box_timbre[TIMBRE_1]);
      break;
    case VOICE_MODE_LAYER :
      gtk_container_remove(GTK_CONTAINER(panel->notebook_layers),panel->box_timbre[TIMBRE_1]);
      gtk_container_remove(GTK_CONTAINER(panel->notebook_layers),panel->box_timbre[TIMBRE_2]);
      gtk_container_remove(GTK_CONTAINER(panel->box_params_slot),panel->notebook_layers);
      break;
    case VOICE_MODE_VOCODER :
      break;
  }
}

void basics_panel_set(SoundPanel *panel) {
  switch(panel->voiceMode) {
    case VOICE_MODE_SINGLE :
      gtk_box_pack_start(GTK_BOX(panel->box_params_slot),panel->box_timbre[TIMBRE_1],0,0,0);

      set_combo_box_value(panel->basics.combobox_voice,GTK_VOICE_SYNTH);
      set_combo_box_value(panel->basics.combobox_layer,GTK_LAYER_SINGLE);
      gtk_widget_set_sensitive(panel->basics.combobox_layer,1);
      break;
    case VOICE_MODE_LAYER :
      gtk_notebook_append_page(
          GTK_NOTEBOOK(panel->notebook_layers),
          panel->box_timbre[TIMBRE_1],panel->label_layer_name[TIMBRE_1]);
      gtk_notebook_append_page(
          GTK_NOTEBOOK(panel->notebook_layers),
          panel->box_timbre[TIMBRE_2],panel->label_layer_name[TIMBRE_2]);
      gtk_box_pack_start(GTK_BOX(panel->box_params_slot),panel->notebook_layers,0,0,0);

      set_combo_box_value(panel->basics.combobox_voice,GTK_VOICE_SYNTH);
      set_combo_box_value(panel->basics.combobox_layer,GTK_LAYER_DOUBLE);
      gtk_widget_set_sensitive(panel->basics.combobox_layer,1);
      break;
    case VOICE_MODE_VOCODER :
      set_combo_box_value(panel->basics.combobox_voice,GTK_VOICE_VOCODER);
      gtk_widget_set_sensitive(panel->basics.combobox_layer,0);
      set_combo_box_value(panel->basics.combobox_layer,-1);
      break;
  }
  gtk_widget_show_all(panel->box_params_slot);
}

void basics_panel_build(SoundPanel *panel) {
  panel->voiceMode = -1;
  set_combo_box_value(panel->basics.combobox_voice,-1);
  set_combo_box_value(panel->basics.combobox_layer,-1);
  gtk_widget_set_sensitive(panel->basics.combobox_layer,0);
}

void basics_panel_change_mode(SoundPanel *panel, VoiceMode newMode) {
  if(newMode == panel->voiceMode)
    return; // Nothing to do

  basics_panel_unset(panel);
  panel->voiceMode = newMode;
  basics_panel_set(panel);
}

