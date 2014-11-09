#include <stdbool.h>
#include <stdlib.h>
#include "filtereg_panel.h"

typedef struct _FilterEgPanel {
  VoiceLayer     layer;
  GtkAdjustment *adjust_attack;
  GtkAdjustment *adjust_decay;
  GtkAdjustment *adjust_sustain;
  GtkAdjustment *adjust_release;
  GtkWidget     *switch_reset;
} FilterEgPanel;

FilterEgPanel * filtereg_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  FilterEgPanel *panel = (FilterEgPanel*) malloc(sizeof(FilterEgPanel));

  panel->layer = layer;

  panel->adjust_attack  =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filteregattack");
  panel->adjust_decay   =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filteregdecay");
  panel->adjust_sustain =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filteregsustain");
  panel->adjust_release =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filteregrelease");
  panel->switch_reset   =
    (GtkWidget*) gtk_builder_get_object(builder,"switch_filteregreset");

  return panel;
}

void filtereg_panel_set(FilterEgPanel *panel,const ProgMsg *progMsg) {

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_attack),
      getFilterEgAttack(panel->layer,progMsg));
  
  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_decay),
      getFilterEgDecay(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_sustain),
      getFilterEgSustain(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_release),
      getFilterEgRelease(panel->layer,progMsg));
  
  gtk_switch_set_active(
      GTK_SWITCH(panel->switch_reset),
      getFilterEgReset(panel->layer,progMsg));


}

