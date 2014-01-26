#include <gtk/gtk.h>
#include "basics_panel.h"
#include "util.h"
#include "sound_panel_internal.h"

void basics_panel_unset(BasicsPanel *panel) {
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

void basics_panel_set(BasicsPanel *panel) {
  switch(panel->voiceMode) {
    case VOICE_MODE_SINGLE :
      gtk_box_pack_start(GTK_BOX(panel->box_params_slot),panel->box_timbre[TIMBRE_1],0,0,0);

      set_combo_box_value(panel->combobox_voice,GTK_VOICE_SYNTH);
      set_combo_box_value(panel->combobox_layering,GTK_LAYER_SINGLE);
      gtk_widget_set_sensitive(panel->combobox_layering,1);
      break;
    case VOICE_MODE_LAYER :
      gtk_notebook_append_page(
          GTK_NOTEBOOK(panel->notebook_layers),
          panel->box_timbre[TIMBRE_1],panel->label_layer_name[TIMBRE_1]);
      gtk_notebook_append_page(
          GTK_NOTEBOOK(panel->notebook_layers),
          panel->box_timbre[TIMBRE_2],panel->label_layer_name[TIMBRE_2]);
      gtk_box_pack_start(GTK_BOX(panel->box_params_slot),panel->notebook_layers,0,0,0);

      set_combo_box_value(panel->combobox_voice,GTK_VOICE_SYNTH);
      set_combo_box_value(panel->combobox_layering,GTK_LAYER_DOUBLE);
      gtk_widget_set_sensitive(panel->combobox_layering,1);

      break;
    case VOICE_MODE_VOCODER :
      set_combo_box_value(panel->combobox_voice,GTK_VOICE_VOCODER);
      gtk_widget_set_sensitive(panel->combobox_layering,0);
      set_combo_box_value(panel->combobox_layering,-1);
      break;
  }
}

void basics_panel_build(GtkBuilder *builder, BasicsPanel *panel) {

  panel->box_params_slot = (GtkWidget*) gtk_builder_get_object(builder,"box_params_slot"); 
  panel->box_timbre[0] =   (GtkWidget*) gtk_builder_get_object(builder,"box_timbre0");
  panel->box_timbre[1] =   (GtkWidget*) gtk_builder_get_object(builder,"box_timbre1");
  panel->notebook_layers = gtk_notebook_new();
  panel->label_layer_name[0] = gtk_label_new("Timbre 1"); 
  panel->label_layer_name[1] = gtk_label_new("Timbre 2"); 
  gtk_widget_show(panel->box_timbre[TIMBRE_1]);
  gtk_widget_show(panel->box_timbre[TIMBRE_2]);
  gtk_widget_show(panel->notebook_layers);
  gtk_widget_show(panel->box_params_slot);

  // Keep a reference on the moving panels so they are not destroyed when
  // temporary detached
  g_object_ref(panel->box_timbre[0]);
  g_object_ref(panel->box_timbre[1]);
  g_object_ref(panel->notebook_layers);
  g_object_ref(panel->label_layer_name[0]);
  g_object_ref(panel->label_layer_name[1]);

  panel->combobox_voice = 
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_voice");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_voice),"Synthesizer");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_voice),"Vocoder");

  panel->combobox_layering = 
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_layering");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_layering),"Single");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_layering),"Layer");

  panel->voiceMode = -1;

  set_combo_box_value(panel->combobox_voice,-1);
  set_combo_box_value(panel->combobox_layering,-1);
  gtk_widget_set_sensitive(panel->combobox_layering,0);
}

void basics_panel_change_mode(BasicsPanel *panel, VoiceMode newMode) {
  if(newMode == panel->voiceMode)
    return; // Nothing to do

  basics_panel_unset(panel);
  panel->voiceMode = newMode;
  basics_panel_set(panel);
}

