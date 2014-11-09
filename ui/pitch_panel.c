#include <stdlib.h>
#include "pitch_panel.h"

typedef struct _PitchPanel {
  VoiceLayer    layer;
  GtkAdjustment *adjust_tune;
  GtkAdjustment *adjust_transpose;
  GtkAdjustment *adjust_portamento;
  GtkAdjustment *adjust_bendrange;
  GtkAdjustment *adjust_vibratoint;
} PitchPanel;

PitchPanel * pitch_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  PitchPanel *panel = (PitchPanel*) malloc(sizeof(PitchPanel));

  panel->layer = layer;

  panel->adjust_tune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_tune");
  panel->adjust_transpose =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_transpose");
  panel->adjust_portamento =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_portamento");
  panel->adjust_bendrange =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_bendrange");
  panel->adjust_vibratoint =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_vibratoint");

  return panel;
}

void pitch_panel_set(PitchPanel *panel,const ProgMsg *progMsg) {
  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_transpose),
      getTranspose(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_tune),
      getTune(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_portamento),
      getPortamento(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_bendrange),
      getBendRange(panel->layer,progMsg));

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_vibratoint),
      getVibratoInt(panel->layer,progMsg));
}

