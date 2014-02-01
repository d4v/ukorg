#include <stdbool.h>
#include <stdlib.h>
#include "mixer_panel.h"

typedef struct _MixerPanel {
  VoiceLayer     layer;
  GtkAdjustment *adjust_osc1Level;
  GtkAdjustment *adjust_osc2Level;
  GtkAdjustment *adjust_noiseLevel;
} MixerPanel;

void mixer_panel_build_timbre_1(MixerPanel *panel, GtkBuilder *builder) {
  
  panel->adjust_osc1Level =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc1level0");
  panel->adjust_osc2Level =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc2level0");
  panel->adjust_noiseLevel =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_noiselevel0");

}

void mixer_panel_build_timbre_2(MixerPanel *panel, GtkBuilder *builder) {
  
  panel->adjust_osc1Level =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc1level1");
  panel->adjust_osc2Level =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc2level1");
  panel->adjust_noiseLevel =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_noiselevel1");

}

MixerPanel * mixer_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  MixerPanel *panel = (MixerPanel*) malloc(sizeof(MixerPanel));

  panel->layer = layer;

  switch (layer) {
    case TIMBRE_1:
      mixer_panel_build_timbre_1(panel,builder);
      break;
    case TIMBRE_2:
      mixer_panel_build_timbre_2(panel,builder);
      break;
  }

  return panel;
}

void mixer_panel_set(MixerPanel *panel,const ProgMsg *progMsg) {

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_osc1Level),
      getOsc1Level(panel->layer,progMsg));
  
  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_osc2Level),
      getOsc2Level(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_noiseLevel),
      getNoiseLevel(panel->layer,progMsg));

}

