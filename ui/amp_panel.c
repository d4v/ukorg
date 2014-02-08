#include <stdbool.h>
#include <stdlib.h>
#include "amp_panel.h"

typedef struct _AmpPanel {
  VoiceLayer     layer;
  GtkAdjustment *adjust_level;
  GtkAdjustment *adjust_pan;
  GtkWidget     *switch_distortion;
  GtkAdjustment *adjust_kbdTrack;
} AmpPanel;

void amp_panel_build_timbre_1(AmpPanel *panel, GtkBuilder *builder) {
  
  panel->adjust_level =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_amplevel0");
  panel->adjust_pan =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_amppan0");
  panel->switch_distortion =
    (GtkWidget*) gtk_builder_get_object(builder,"switch_ampdist0");
  panel->adjust_kbdTrack =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampkbdtrack0");

}

void amp_panel_build_timbre_2(AmpPanel *panel, GtkBuilder *builder) {
  
  panel->adjust_level =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_amplevel1");
  panel->adjust_pan =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_amppan1");
  panel->switch_distortion =
    (GtkWidget*) gtk_builder_get_object(builder,"switch_ampdist1");
  panel->adjust_kbdTrack =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampkbdtrack1");

}

AmpPanel * amp_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  AmpPanel *panel = (AmpPanel*) malloc(sizeof(AmpPanel));

  panel->layer = layer;

  switch (layer) {
    case TIMBRE_1:
      amp_panel_build_timbre_1(panel,builder);
      break;
    case TIMBRE_2:
      amp_panel_build_timbre_2(panel,builder);
      break;
  }

  return panel;
}

void amp_panel_set(AmpPanel *panel,const ProgMsg *progMsg) {

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_level),
      getAmpLevel(panel->layer,progMsg));
  
  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_pan),
      getAmpPanPot(panel->layer,progMsg));

  gtk_switch_set_active(
      GTK_SWITCH(panel->switch_distortion),
      getAmpDistortion(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_kbdTrack),
      getAmpKbdTrack(panel->layer,progMsg));

}

