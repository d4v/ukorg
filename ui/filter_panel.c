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

void filter_panel_build_timbre_1(FilterPanel *panel, GtkBuilder *builder) {
  
  panel->combobox_type =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_filtertype0");
  panel->adjust_cutoff =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filtercutoff0");
  panel->adjust_resonance =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filterresonance0");
  panel->adjust_egInt =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filteregint0");
  panel->adjust_keyTrack =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filterkeytrack0");

}

void filter_panel_build_timbre_2(FilterPanel *panel, GtkBuilder *builder) {
  
  panel->combobox_type =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_filtertype1");
  panel->adjust_cutoff =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filtercutoff1");
  panel->adjust_resonance =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filterresonance1");
  panel->adjust_egInt =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filteregint1");
  panel->adjust_keyTrack =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_filterkeytrack1");

}

FilterPanel * filter_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  FilterPanel *panel = (FilterPanel*) malloc(sizeof(FilterPanel));
  static const char *filter_types[] = {
    "-24dB LPF", "-12dB LPF", "-12dB BPF", "-12dB HPF"
  };
  static const int filter_types_nb = 4;
  int idx = 0;

  panel->layer = layer;

  switch (layer) {
    case TIMBRE_1:
      filter_panel_build_timbre_1(panel,builder);
      break;
    case TIMBRE_2:
      filter_panel_build_timbre_2(panel,builder);
      break;
  }

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

