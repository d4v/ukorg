#include "patch_panel.h"

typedef struct _PatchPanel {
  VoiceLayer     layer;
  TempoSync      tempo_sync;
  GtkWidget     *combobox_patch1_src;
  GtkWidget     *combobox_patch1_dst;
  GtkWidget     *combobox_patch1_mod;
  GtkWidget     *combobox_patch2_src;
  GtkWidget     *combobox_patch2_dst;
  GtkWidget     *combobox_patch2_mod;
  GtkWidget     *combobox_patch3_src;
  GtkWidget     *combobox_patch3_dst;
  GtkWidget     *combobox_patch3_mod;
  GtkWidget     *combobox_patch4_src;
  GtkWidget     *combobox_patch4_dst;
  GtkWidget     *combobox_patch4_mod;
} PatchPanel;

void patch_panel_build_timbre_1(PatchPanel *panel, GtkBuilder *builder) {
  panel->combobox_patch1_src =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch1_src0");
  panel->combobox_patch1_dst =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch1_dst0");
  panel->combobox_patch1_mod =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch1_mod0");
  panel->combobox_patch2_src =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch2_src0");
  panel->combobox_patch2_dst =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch2_dst0");
  panel->combobox_patch2_mod =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch2_mod0");
  panel->combobox_patch3_src =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch3_src0");
  panel->combobox_patch3_dst =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch3_dst0");
  panel->combobox_patch3_mod =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch3_mod0");
  panel->combobox_patch4_src =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch4_src0");
  panel->combobox_patch4_dst =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch4_dst0");
  panel->combobox_patch4_mod =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch4_mod0");
}

void patch_panel_build_timbre_2(PatchPanel *panel, GtkBuilder *builder) {
  panel->combobox_patch1_src =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch1_src1");
  panel->combobox_patch1_dst =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch1_dst1");
  panel->combobox_patch1_mod =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch1_mod1");
  panel->combobox_patch2_src =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch2_src1");
  panel->combobox_patch2_dst =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch2_dst1");
  panel->combobox_patch2_mod =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch2_mod1");
  panel->combobox_patch3_src =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch3_src1");
  panel->combobox_patch3_dst =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch3_dst1");
  panel->combobox_patch3_mod =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch3_mod1");
  panel->combobox_patch4_src =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch4_src1");
  panel->combobox_patch4_dst =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch4_dst1");
  panel->combobox_patch4_mod =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_patch4_mod1");
}

PatchPanel * patch_panel_build(GtkBuilder *builder, VoiceLayer layer) {
  PatchPanel *panel = (PatchPanel *) malloc(sizeof(PatchPanel));
  int idx = 0;

  static const char *src_types[] = {
    "FilterEG", "AmpEG", "LFO1", "LFO2", "Velocity",
    "Kbd track", "Pitch bend", "Mod wheel"};
  static const char src_types_nb = 8;

  static const char *dst_types[] = {
    "Pitch", "Osc2 Tune", "Osc1 Ctrl 1", "NoiseLevel",
    "Cut off", "Amp", "Pan", "LFO2 freq"};
  static const char dst_types_nb = 8;

  panel->layer = layer;

  switch (layer) {
    case TIMBRE_1:
      patch_panel_build_timbre_1(panel,builder);
      break;
    case TIMBRE_2:
      patch_panel_build_timbre_2(panel,builder);
      break;
  }

ICIIII optimiser cette horreur...

  for(idx = 0; idx < src_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_patch1_src),src_types[idx]);
  }

  for(idx = 0; idx < src_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_patch2_src),src_types[idx]);
  }

  for(idx = 0; idx < src_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_patch2_src),src_types[idx]);
  }

  for(idx = 0; idx < src_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_patch2_src),src_types[idx]);
  }






