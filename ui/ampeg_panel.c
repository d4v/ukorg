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

void ampeg_panel_build_timbre_1(AmpEgPanel *panel, GtkBuilder *builder) {

  panel->adjust_attack  =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegattack0");
  panel->adjust_decay   =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegdecay0");
  panel->adjust_sustain =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegsustain0");
  panel->adjust_release =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegrelease0");
  panel->switch_reset   =
    (GtkWidget*) gtk_builder_get_object(builder,"switch_ampegreset0");

}

void ampeg_panel_build_timbre_2(AmpEgPanel *panel, GtkBuilder *builder) {
  
  panel->adjust_attack  =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegattack1");
  panel->adjust_decay   =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegdecay1");
  panel->adjust_sustain =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegsustain1");
  panel->adjust_release =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_ampegrelease1");
  panel->switch_reset   =
    (GtkWidget*) gtk_builder_get_object(builder,"switch_ampegreset1");

}

AmpEgPanel * ampeg_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  AmpEgPanel *panel = (AmpEgPanel*) malloc(sizeof(AmpEgPanel));

  panel->layer = layer;

  switch (layer) {
    case TIMBRE_1:
      ampeg_panel_build_timbre_1(panel,builder);
      break;
    case TIMBRE_2:
      ampeg_panel_build_timbre_2(panel,builder);
      break;
  }

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

