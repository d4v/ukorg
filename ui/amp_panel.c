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

AmpPanel * amp_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  AmpPanel *panel = (AmpPanel*) malloc(sizeof(AmpPanel));

  panel->layer = layer;

  panel->adjust_level =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_amplevel");
  panel->adjust_pan =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_amppan");
  panel->switch_distortion =
    (GtkWidget*) gtk_builder_get_object(builder,"switch_ampdist");
  panel->adjust_kbdTrack =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampkbdtrack");
  
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

