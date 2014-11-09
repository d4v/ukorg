#include <stdbool.h>
#include <stdlib.h>
#include "filter_panel.h"

typedef struct _FilterPanel {
  VoiceLayer     layer;
  GtkWidget     *combobox_type;
  GtkAdjustment *adjust_cutoff;
  GtkAdjustment *adjust_resonance;
  GtkAdjustment *adjust_egInt;
  GtkAdjustment *adjust_keyTrack;
} FilterPanel;

FilterPanel * filter_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  FilterPanel *panel = (FilterPanel*) malloc(sizeof(FilterPanel));
  static const char *filter_types[] = {
    "-24dB LPF", "-12dB LPF", "-12dB BPF", "-12dB HPF"
  };
  static const int filter_types_nb = 4;
  int idx = 0;

  panel->layer = layer;

  panel->combobox_type =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_filtertype");
  panel->adjust_cutoff =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filtercutoff");
  panel->adjust_resonance =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filterresonance");
  panel->adjust_egInt =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filteregint");
  panel->adjust_keyTrack =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filterkeytrack");

  for(idx = 0; idx < filter_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_type),filter_types[idx]);
  }

  return panel;
}

void filter_panel_set(FilterPanel *panel,const ProgMsg *progMsg) {

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_type),
      getFilterType(panel->layer, progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_cutoff),
      getFilterCutoff(panel->layer,progMsg));
  
  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_resonance),
      getFilterResonance(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_egInt),
      getFilterEgInt(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_keyTrack),
      getFilterKeyTrack(panel->layer,progMsg));

}

