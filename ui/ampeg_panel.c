#include <stdbool.h>
#include <stdlib.h>
#include "ampeg_panel.h"

typedef struct _AmpEgPanel {
  VoiceLayer     layer;
  GtkAdjustment *adjust_attack;
  GtkAdjustment *adjust_decay;
  GtkAdjustment *adjust_sustain;
  GtkAdjustment *adjust_release;
  GtkWidget     *switch_reset;
} AmpEgPanel;

AmpEgPanel * ampeg_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  AmpEgPanel *panel = (AmpEgPanel*) malloc(sizeof(AmpEgPanel));

  panel->layer = layer;

  panel->adjust_attack  =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegattack");
  panel->adjust_decay   =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegdecay");
  panel->adjust_sustain =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegsustain");
  panel->adjust_release =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegrelease");
  panel->switch_reset   =
    (GtkWidget*) gtk_builder_get_object(builder,"switch_ampegreset");

  return panel;
}

void ampeg_panel_set(AmpEgPanel *panel,const ProgMsg *progMsg) {

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_attack),
      getAmpEgAttack(panel->layer,progMsg));
  
  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_decay),
      getAmpEgDecay(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_sustain),
      getAmpEgSustain(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_release),
      getAmpEgRelease(panel->layer,progMsg));
  
  gtk_switch_set_active(
      GTK_SWITCH(panel->switch_reset),
      getAmpEgReset(panel->layer,progMsg));


}

