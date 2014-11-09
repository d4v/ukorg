#include <stdlib.h>
#include <gtk/gtk.h>
#include "basics_panel.h"
#include "util.h"
#include "ProgMsg.h"

typedef struct _CbHandlers {
  gulong voice_changed;
  gulong layer_changed;
} CbHandlers;

typedef struct _BasicsPanel {
  VoiceMode  voiceMode;
  CbHandlers cbHandlers;
  GtkWidget *combobox_voice;
  GtkWidget *combobox_layering;
  GtkWidget *notebook_layers;
  GtkWidget *label_layer_name[2];
  GtkWidget *box_timbre[2];
  GtkWidget *box_params_slot;
} BasicsPanel;

enum {
  GTK_VOICE_SYNTH,
  GTK_VOICE_VOCODER,
};

enum {
  GTK_LAYER_SINGLE,
  GTK_LAYER_DOUBLE,
};

BasicsPanel * basics_panel_build(
    GtkBuilder *basics,GtkBuilder *voice1, GtkBuilder *voice2) {

  BasicsPanel *panel = (BasicsPanel*) malloc(sizeof(BasicsPanel));

  panel->box_params_slot = (GtkWidget*) gtk_builder_get_object(basics,"box_params_slot"); 
  panel->box_timbre[0] =   (GtkWidget*) gtk_builder_get_object(voice1,"box_timbre");
  panel->box_timbre[1] =   (GtkWidget*) gtk_builder_get_object(voice2,"box_timbre");
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
    (GtkWidget*) gtk_builder_get_object(basics,"combobox_voice");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_voice),"Synthesizer");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_voice),"Vocoder");

  panel->combobox_layering = 
    (GtkWidget*) gtk_builder_get_object(basics,"combobox_layering");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_layering),"Single");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_layering),"Layer");

  panel->voiceMode = -1;

  set_combo_box_value(panel->combobox_voice,-1);
  set_combo_box_value(panel->combobox_layering,-1);
  gtk_widget_set_sensitive(panel->combobox_layering,0);

  return panel;
}

void basics_panel_unset_layout(BasicsPanel *panel) {
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

void basics_panel_set_layout(BasicsPanel *panel) {

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

void basics_panel_change_layout(BasicsPanel *panel, VoiceMode newMode) {
  basics_panel_unset_layout(panel);
  panel->voiceMode = newMode;
  basics_panel_set_layout(panel);
}

void basics_panel_set(BasicsPanel *panel, const ProgMsg *msg) {
  VoiceMode newMode = getVoiceMode(msg);
  if(newMode != panel->voiceMode) {
    basics_panel_change_layout(panel, newMode);
  }
}

void freeze_signals(BasicsPanel *panel) {
  g_signal_handler_block(
      panel->combobox_voice,panel->cbHandlers.voice_changed);
  g_signal_handler_block(
      panel->combobox_layering,panel->cbHandlers.layer_changed);
}

void unfreeze_signals(BasicsPanel *panel) {
  g_signal_handler_unblock(
      panel->combobox_voice,panel->cbHandlers.voice_changed);
  g_signal_handler_unblock(
      panel->combobox_layering,panel->cbHandlers.layer_changed);
}

void on_voice_mode_changed(GtkComboBox *combobox,gpointer user_data) {
  BasicsPanel *panel = (BasicsPanel*) user_data;
  VoiceMode mode = VOICE_MODE_SINGLE;

  freeze_signals(panel);

  if(gtk_combo_box_get_active(GTK_COMBO_BOX(panel->combobox_voice)) == GTK_VOICE_VOCODER)
    mode = VOICE_MODE_VOCODER;
  else if(gtk_combo_box_get_active(GTK_COMBO_BOX(panel->combobox_layering)) == GTK_LAYER_DOUBLE)
    mode = VOICE_MODE_LAYER;

  basics_panel_change_layout(panel,mode);

  unfreeze_signals(panel);
}

void basics_panel_cb_build(BasicsPanel *panel) {
  panel->cbHandlers.voice_changed = 
  g_signal_connect(panel->combobox_voice,"changed",
                   (GCallback) on_voice_mode_changed,panel);

  panel->cbHandlers.layer_changed = 
  g_signal_connect(panel->combobox_layering,"changed",
                   (GCallback) on_voice_mode_changed,panel);
}

