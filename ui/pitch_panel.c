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

void pitch_panel_build_timbre_1(GtkBuilder *builder, PitchPanel *panel) {
  panel->layer = TIMBRE_1;

  panel->adjust_tune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_tune0");
  panel->adjust_transpose =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_transpose0");
  panel->adjust_portamento =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_portamento0");
  panel->adjust_bendrange =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_bendrange0");
  panel->adjust_vibratoint =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_vibratoint0");
}

void pitch_panel_build_timbre_2(GtkBuilder *builder, PitchPanel *panel) {
  panel->layer = TIMBRE_2;

  panel->adjust_tune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_tune1");
  panel->adjust_transpose =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_transpose1");
  panel->adjust_portamento =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_portamento1");
  panel->adjust_bendrange =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_bendrange1");
  panel->adjust_vibratoint =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_vibratoint1");
}

PitchPanel * pitch_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  PitchPanel *panel = (PitchPanel*) malloc(sizeof(PitchPanel));
  switch (layer) {
    case TIMBRE_1:
      pitch_panel_build_timbre_1(builder,panel);
      break;
    case TIMBRE_2:
      pitch_panel_build_timbre_2(builder,panel);
      break;
  }
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

