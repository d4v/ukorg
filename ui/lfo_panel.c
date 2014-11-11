#include <stdbool.h>
#include <stdlib.h>
#include "lfo_panel.h"
#include "util.h"

typedef struct _LfoPanel_int {
  VoiceLayer     layer;
  LfoId          id;
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
} LfoPanel_int;

typedef struct _LfoPanel {
  LfoPanel_int  *lfo[2];
} LfoPanel;

LfoPanel * lfo_panel_build(GtkBuilder* builder,VoiceLayer layer) {
  LfoPanel_int *panel1 = (LfoPanel_int*) malloc(sizeof(LfoPanel_int));
  LfoPanel_int *panel2 = (LfoPanel_int*) malloc(sizeof(LfoPanel_int));
  LfoPanel *panel = (LfoPanel*) malloc(sizeof(LfoPanel));

  int idx = 0,panelIdx = 0;

  static const char *wave_types[2][4] = {
    {"Saw", "Square1", "Triangle", "Sample&Hold"},
    {"Saw", "Square2", "Sine", "Sample&Hold"}};
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

  GET_GTK_OBJECT(panel1->combobox_wave,GtkWidget,builder,"combobox_lfo1wave");
  GET_GTK_OBJECT(panel1->combobox_keySync,GtkWidget,builder,"combobox_lfo1ksync");
  GET_GTK_OBJECT(panel1->switch_tempoSync,GtkWidget,builder,"switch_lfo1tsync");
  GET_GTK_OBJECT(panel1->label_slot4,GtkWidget,builder,"label_lfo1slot4");
  GET_GTK_OBJECT(panel1->align_slot4,GtkWidget,builder,"align_lfo1slot4");
  GET_GTK_OBJECT(panel1->scale_frequency,GtkWidget,builder,"scale_lfo1freq");
  GET_GTK_OBJECT(panel1->adjust_frequency,GtkAdjustment,builder,"adjust_lfo1freq");

  GET_GTK_OBJECT(panel2->combobox_wave,GtkWidget,builder,"combobox_lfo2wave");
  GET_GTK_OBJECT(panel2->combobox_keySync,GtkWidget,builder,"combobox_lfo2ksync");
  GET_GTK_OBJECT(panel2->switch_tempoSync,GtkWidget,builder,"switch_lfo2tsync");
  GET_GTK_OBJECT(panel2->label_slot4,GtkWidget,builder,"label_lfo2slot4");
  GET_GTK_OBJECT(panel2->align_slot4,GtkWidget,builder,"align_lfo2slot4");
  GET_GTK_OBJECT(panel2->scale_frequency,GtkWidget,builder,"scale_lfo2freq");
  GET_GTK_OBJECT(panel2->adjust_frequency,GtkAdjustment,builder,"adjust_lfo2freq");

  panel1->id = LFO_ID_1;
  panel2->id = LFO_ID_2;
  panel->lfo[0] = panel1;
  panel->lfo[1] = panel2;

  for(panelIdx = 0; panelIdx < 2;panelIdx++) {
    LfoPanel_int *lfo = panel->lfo[panelIdx];

    lfo->layer = layer;

    lfo->combobox_syncNote = (GtkWidget*) gtk_combo_box_text_new();

    // Keep a reference on those object so they are not destroyed when
    // temporary detached
    g_object_ref(lfo->combobox_syncNote);
    g_object_ref(lfo->scale_frequency);

    for(idx = 0; idx < wave_types_nb; idx++) {
      gtk_combo_box_text_append_text(
          GTK_COMBO_BOX_TEXT(lfo->combobox_wave),wave_types[panelIdx][idx]);
    }

    for(idx = 0; idx < key_syncs_nb; idx++) {
      gtk_combo_box_text_append_text(
          GTK_COMBO_BOX_TEXT(lfo->combobox_keySync),key_syncs[idx]);
    }

    for(idx = 0; idx < sync_notes_nb; idx++) {
      gtk_combo_box_text_append_text(
          GTK_COMBO_BOX_TEXT(lfo->combobox_syncNote),sync_notes[idx]);
    }
    lfo->tempo_sync = 0;
    lfo->sync_note = 0;

    gtk_switch_set_active(
        GTK_SWITCH(lfo->switch_tempoSync),lfo->tempo_sync);

    gtk_combo_box_set_active(
        GTK_COMBO_BOX(lfo->combobox_syncNote),lfo->sync_note);
  }
  
  return panel;
}

void lfo_panel_unset_layout(LfoPanel_int *panel) {
  if(panel->tempo_sync == TSYNC_OFF) {
    gtk_container_remove(GTK_CONTAINER(panel->align_slot4),
                         panel->scale_frequency);
  } else {
    gtk_container_remove(GTK_CONTAINER(panel->align_slot4),
                         panel->combobox_syncNote);
  }
}

void lfo_panel_set_layout(LfoPanel_int *panel) {
  if(panel->tempo_sync == TSYNC_OFF) {
    gtk_container_add(GTK_CONTAINER(panel->align_slot4),
                      panel->scale_frequency);
  } else {
    gtk_container_add(GTK_CONTAINER(panel->align_slot4),
                      panel->combobox_syncNote);
  }

  gtk_widget_show_all(panel->align_slot4);
}

void lfo_panel_change_layout(LfoPanel_int *panel,TempoSync tempo_sync) {
    lfo_panel_unset_layout(panel);
    panel->tempo_sync = tempo_sync;
    lfo_panel_set_layout(panel);
}

void lfo_panel_set_int(LfoPanel_int *panel,const ProgMsg *progMsg) {
  VoiceLayer layer = panel->layer;
  LfoId id = panel->id;
  TempoSync newStatus = getLfoTempoSync(layer,id,progMsg);

  if(newStatus != panel->tempo_sync) {
    lfo_panel_change_layout(panel,newStatus);
  }

  switch(id) {
    case LFO_ID_1:
      gtk_combo_box_set_active(
          GTK_COMBO_BOX(panel->combobox_wave),
          getLfo1WaveType(panel->layer,progMsg));
      break;
    case LFO_ID_2:
      gtk_combo_box_set_active(
          GTK_COMBO_BOX(panel->combobox_wave),
          getLfo1WaveType(panel->layer,progMsg));
  }

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_keySync),
      getLfoKeySync(layer,id,progMsg));

  gtk_switch_set_active(
      GTK_SWITCH(panel->switch_tempoSync),
      getLfoTempoSync(layer,id,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_frequency),
      getLfoFrequency(layer,id,progMsg));
  
  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_syncNote),
      getLfoSyncNote(layer,id,progMsg));
}

void lfo_panel_set(LfoPanel *panel,const ProgMsg *progMsg) {
  int idx = 0;
  for(idx = 0; idx < 2; idx++) {
    lfo_panel_set_int(panel->lfo[idx],progMsg);
  }
}

void lfo_on_tempo_sync_changed(
    GtkSwitch *tsyncSwitch, GParamSpec *pspec, gpointer user_data) {

  LfoPanel_int *panel = (LfoPanel_int*) user_data;

  TempoSync newStatus = gtk_switch_get_active(tsyncSwitch);

  if(newStatus != panel->tempo_sync) {
    lfo_panel_change_layout(panel,newStatus);
  }

}

void lfo_panel_cb_build(LfoPanel *panel) {
  int idx=0;
  for(idx = 0; idx < 2; idx++) {
    LfoPanel_int * lfo = panel->lfo[idx];
    g_signal_connect(lfo->switch_tempoSync,"notify::active",
        (GCallback) lfo_on_tempo_sync_changed,lfo);
  }
}


