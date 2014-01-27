#include "pitch_panel.h"
#include "sound_panel_internal.h"

void pitch_panel_build_timbre_1(GtkBuilder *builder, PitchPanel *panel) {
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

void pitch_panel_build(GtkBuilder *builder,VoiceLayer layer,PitchPanel *panel) {
  switch (layer) {
    case TIMBRE_1:
      pitch_panel_build_timbre_1(builder,panel);
      break;
    case TIMBRE_2:
      pitch_panel_build_timbre_2(builder,panel);
      break;
  }
}

