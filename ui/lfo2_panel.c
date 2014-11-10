#include <stdbool.h>
#include <stdlib.h>
#include "lfo2_panel.h"

typedef struct _Lfo2Panel {
  VoiceLayer     layer;
  TempoSync      tempo_sync;
  SyncNote       sync_note;
  GtkWidget     *combobox_wave;
  GtkWidget     *combobox_keySync;
  GtkWidget     *switch_tempoSync;
  GtkWidget     *label_slot4;
  GtkWidget     *align_slot4;
  GtkWidget     *scale_frequency;
  GtkAdjustment *adjust_frequency;
  GtkWidget     *combobox_syncNote;
} Lfo2Panel;

Lfo2Panel * lfo2_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  Lfo2Panel *panel = (Lfo2Panel*) malloc(sizeof(Lfo2Panel));
  int idx = 0;

  static const char *wave_types[] = {
    "Saw", "Square2", "Sine", "Sample&Hold"};
  static const int wave_types_nb = 4;

  static const char *key_syncs[] = {
    "Off", "Timbre", "Voice"};
  static const int key_syncs_nb = 3;

  static const char *sync_notes[] = {
    "1/1" ,"3/4" ,"2/3" ,"1/2" ,
    "3/8" ,"1/3" ,"1/4" ,"3/16", // 8
    "1/6" ,"1/8" ,"3/32","1/12",
    "1/16","1/24","1/32"};       // 15
  static const int sync_notes_nb = 15;

  panel->layer = layer;

  panel->combobox_wave =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_lfo2wave");
  panel->combobox_keySync =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_lfo2ksync");
  panel->switch_tempoSync =
    (GtkWidget*) gtk_builder_get_object(builder,"switch_lfo2tsync");
  panel->label_slot4 =
    (GtkWidget*) gtk_builder_get_object(builder,"label_lfo2slot4");
  panel->align_slot4 =
    (GtkWidget*) gtk_builder_get_object(builder,"align_lfo2slot4");
  panel->scale_frequency =
    (GtkWidget*) gtk_builder_get_object(builder,"scale_lfo2freq");
  panel->adjust_frequency =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_lfo2freq");

  panel->combobox_syncNote =
    (GtkWidget*) gtk_combo_box_text_new();

  // Keep a reference on those object so they are not destroyed when
  // temporary detached
  g_object_ref(panel->combobox_syncNote);
  g_object_ref(panel->scale_frequency);

  for(idx = 0; idx < wave_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_wave),wave_types[idx]);
  }

  for(idx = 0; idx < key_syncs_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_keySync),key_syncs[idx]);
  }

  for(idx = 0; idx < sync_notes_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_syncNote),sync_notes[idx]);
  }

  panel->tempo_sync = 0;
  panel->sync_note = 0;

  gtk_switch_set_active(
      GTK_SWITCH(panel->switch_tempoSync),panel->tempo_sync);
  
  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_syncNote),panel->sync_note);

  return panel;
}

void lfo2_panel_unset_layout(Lfo2Panel *panel) {
  if(panel->tempo_sync == TSYNC_OFF) {
    gtk_container_remove(GTK_CONTAINER(panel->align_slot4),
                         panel->scale_frequency);
  } else {
    gtk_container_remove(GTK_CONTAINER(panel->align_slot4),
                         panel->combobox_syncNote);
  }
}

void lfo2_panel_set_layout(Lfo2Panel *panel) {
  if(panel->tempo_sync == TSYNC_OFF) {
    gtk_container_add(GTK_CONTAINER(panel->align_slot4),
                      panel->scale_frequency);
  } else {
    gtk_container_add(GTK_CONTAINER(panel->align_slot4),
                      panel->combobox_syncNote);
  }

  gtk_widget_show_all(panel->align_slot4);
}

void lfo2_panel_change_layout(Lfo2Panel *panel,TempoSync tempo_sync) {
    lfo2_panel_unset_layout(panel);
    panel->tempo_sync = tempo_sync;
    lfo2_panel_set_layout(panel);
}

void lfo2_panel_set(Lfo2Panel *panel,const ProgMsg *progMsg) {
  TempoSync newStatus = getLfo2TempoSync(panel->layer,progMsg);

  if(newStatus != panel->tempo_sync) {
    lfo2_panel_change_layout(panel,newStatus);
  }

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_wave),
      getLfo2WaveType(panel->layer,progMsg));

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_keySync),
      getLfo2KeySync(panel->layer,progMsg));

  gtk_switch_set_active(
      GTK_SWITCH(panel->switch_tempoSync),
      getLfo2TempoSync(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_frequency),
      getLfo2Frequency(panel->layer,progMsg));
  
  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_syncNote),
      getLfo2SyncNote(panel->layer,progMsg));

}

void lfo2_on_tempo_sync_changed(GtkSwitch *tsyncSwitch, GParamSpec *pspec, gpointer user_data) {
  Lfo2Panel *panel = (Lfo2Panel*) user_data;

  TempoSync newStatus = gtk_switch_get_active(tsyncSwitch);

  if(newStatus != panel->tempo_sync) {
    lfo2_panel_change_layout(panel,newStatus);
  }
}

void lfo2_panel_cb_build(Lfo2Panel *panel) {
  g_signal_connect(panel->switch_tempoSync,"notify::active",
      (GCallback) lfo2_on_tempo_sync_changed,panel);
}

