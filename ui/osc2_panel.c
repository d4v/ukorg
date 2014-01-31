#include <stdbool.h>
#include <stdlib.h>
#include "osc2_panel.h"

typedef struct _Osc2Panel {
  VoiceLayer     layer;
  GtkAdjustment *adjust_level;
  GtkWidget     *combobox_wave;
  WaveType       wave_type;
  GtkWidget     *combobox_mod;
  GtkAdjustment *adjust_semitone;
  GtkAdjustment *adjust_tune;
} Osc2Panel;

void osc2_panel_build_timbre_1(Osc2Panel *panel, GtkBuilder *builder) {
  
  panel->adjust_level =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc2level0");
  panel->combobox_wave =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_osc2wave0");
  panel->combobox_mod =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_osc2mod0");
  panel->adjust_semitone =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc2semitone0");
  panel->adjust_tune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc2tune0");

}

void osc2_panel_build_timbre_2(Osc2Panel *panel, GtkBuilder *builder) {

  panel->adjust_level =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc2level1");
  panel->combobox_wave =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_osc2wave1");
  panel->combobox_mod =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_osc2mod1");
  panel->adjust_semitone =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc2semitone1");
  panel->adjust_tune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc2tune1");

}

Osc2Panel * osc2_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  Osc2Panel *panel = (Osc2Panel*) malloc(sizeof(Osc2Panel));
  int idx = 0;

  static const char *wave_types[] = {"Saw","Square","Triangle"};
  static const int wave_types_nb = 3;

  static const char *mod_types[] = {"OFF","Ring","Sync","RingSync"};
  static const int mod_types_nb = 4;

  panel->layer = layer;

  switch (layer) {
    case TIMBRE_1:
      osc2_panel_build_timbre_1(panel,builder);
      break;
    case TIMBRE_2:
      osc2_panel_build_timbre_2(panel,builder);
      break;
  }

  for(idx = 0; idx < wave_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_wave),wave_types[idx]);
  }
 
  for(idx = 0; idx < mod_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_mod),mod_types[idx]);
  }

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_wave),-1);

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_mod),-1);

  return panel;
}

void osc2_panel_set(Osc2Panel *panel,const ProgMsg *progMsg) {

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_level),
      getOsc2Level(panel->layer,progMsg));
  
  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_wave),
      getOsc2WaveType(panel->layer,progMsg));
  
  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_mod),
      getOsc2ModType(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_semitone),
      getOsc2Semitone(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_tune),
      getOsc2Tune(panel->layer,progMsg));

}

