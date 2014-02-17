#include <stdbool.h>
#include <stdlib.h>
#include "lfo1_panel.h"

typedef struct _Lfo1Panel {
  VoiceLayer     layer;
  TempoSync      tempo_sync;
  GtkWidget     *combobox_wave;
  GtkWidget     *combobox_keySync;
  GtkWidget     *combobox_tempoSync;
  GtkWidget     *label_slot4;
  GtkWidget     *align_slot4;
  GtkWidget     *scale_frequency;
  GtkAdjustment *adjust_frequency;
  GtkWidget     *combobox_syncNote;
} Lfo1Panel;

void lfo1_panel_build_timbre_1(Lfo1Panel *panel, GtkBuilder *builder) {

  panel->combobox_wave =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_lfo1wave0");
  panel->combobox_keySync =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_lfo1ksync0");
  panel->combobox_tempoSync =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_lfo1tsync0");
  panel->label_slot4 =
    (GtkWidget*) gtk_builder_get_object(builder,"label_lfo1slot4_0");
  panel->align_slot4 =
    (GtkWidget*) gtk_builder_get_object(builder,"align_lfo1slot4_0");
  panel->scale_frequency =
    (GtkWidget*) gtk_builder_get_object(builder,"scale_lfo1freq0");
  panel->adjust_frequency =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_lfo1freq0");

}

void lfo1_panel_build_timbre_2(Lfo1Panel *panel, GtkBuilder *builder) {
  
  panel->combobox_wave =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_lfo1wave1");
  panel->combobox_keySync =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_lfo1ksync1");
  panel->combobox_tempoSync =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_lfo1tsync1");
  panel->label_slot4 =
    (GtkWidget*) gtk_builder_get_object(builder,"label_lfo1slot4_1");
  panel->align_slot4 =
    (GtkWidget*) gtk_builder_get_object(builder,"align_lfo1slot4_1");
  panel->scale_frequency =
    (GtkWidget*) gtk_builder_get_object(builder,"scale_lfo1freq1");
  panel->adjust_frequency =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_lfo1freq1");

}

Lfo1Panel * lfo1_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  Lfo1Panel *panel = (Lfo1Panel*) malloc(sizeof(Lfo1Panel));
  int idx = 0;

  static const char *wave_types[] = {
    "Saw", "Square1", "Triangle", "Sample&Hold"};
  static const int wave_types_nb = 4;

  static const char *key_syncs[] = {
    "Off", "Timbre", "Voice"};
  static const int key_syncs_nb = 3;

  static const char *tempo_syncs[] = {
    "Off", "On"};
  static const int tempo_syncs_nb = 2;

  static const char *sync_notes[] = {
    "1/1" ,"3/4" ,"2/3" ,"1/2" ,
    "3/8" ,"1/3" ,"1/4" ,"3/16", // 8
    "1/6" ,"1/8" ,"3/32","1/12",
    "1/16","1/24","1/32"};       // 15
  static const int sync_notes_nb = 15;

  panel->layer = layer;

  switch (layer) {
    case TIMBRE_1:
      lfo1_panel_build_timbre_1(panel,builder);
      break;
    case TIMBRE_2:
      lfo1_panel_build_timbre_2(panel,builder);
      break;
  }

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

  for(idx = 0; idx < tempo_syncs_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_tempoSync),tempo_syncs[idx]);
  }

  for(idx = 0; idx < sync_notes_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_syncNote),sync_notes[idx]);
  }

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_syncNote),0);

  return panel;
}

void lfo1_panel_unset_layout(Lfo1Panel *panel) {
  if(panel->tempo_sync == TSYNC_OFF) {
    gtk_container_remove(GTK_CONTAINER(panel->align_slot4),
                         panel->scale_frequency);
  } else {
    gtk_container_remove(GTK_CONTAINER(panel->align_slot4),
                         panel->combobox_syncNote);
  }
}

void lfo1_panel_set_layout(Lfo1Panel *panel) {
  if(panel->tempo_sync == TSYNC_OFF) {
    gtk_container_add(GTK_CONTAINER(panel->align_slot4),
                      panel->scale_frequency);
  } else {
    gtk_container_add(GTK_CONTAINER(panel->align_slot4),
                      panel->combobox_syncNote);
  }

  gtk_widget_show_all(panel->align_slot4);
}

void lfo1_panel_change_layout(Lfo1Panel *panel,TempoSync tempo_sync) {
    lfo1_panel_unset_layout(panel);
    panel->tempo_sync = tempo_sync;
    lfo1_panel_set_layout(panel);
}

void lfo1_panel_set(Lfo1Panel *panel,const ProgMsg *progMsg) {
  TempoSync newStatus = getLfo1TempoSync(panel->layer,progMsg);

  if(newStatus != panel->tempo_sync) {
    lfo1_panel_change_layout(panel,newStatus);
  }

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_wave),
      getLfo1WaveType(panel->layer,progMsg));

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_keySync),
      getLfo1KeySync(panel->layer,progMsg));

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_tempoSync),
      getLfo1TempoSync(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_frequency),
      getLfo1Frequency(panel->layer,progMsg));
  
  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_syncNote),
      getLfo1SyncNote(panel->layer,progMsg));

}

void lfo1_on_tempo_sync_changed(GtkComboBox *combobox, gpointer user_data) {
  Lfo1Panel *panel = (Lfo1Panel*) user_data;
  TempoSync newStatus = gtk_combo_box_get_active(combobox);

  if(newStatus != panel->tempo_sync) {
    lfo1_panel_change_layout(panel,newStatus);
  }
}

void lfo1_panel_cb_build(Lfo1Panel *panel) {
  g_signal_connect(panel->combobox_tempoSync,"changed",
      (GCallback) lfo1_on_tempo_sync_changed,panel);
}

