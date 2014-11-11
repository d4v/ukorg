#include <stdlib.h>
#include "patch_panel.h"

typedef struct _PatchPanel {
  VoiceLayer     layer;
  GtkWidget     *combobox_patch_src[4];
  GtkWidget     *combobox_patch_dst[4];
  GtkWidget     *adjust_patch_int[4];
} PatchPanel;

PatchPanel * patch_panel_build(GtkBuilder *builder, VoiceLayer layer) {
  PatchPanel *panel = (PatchPanel *) malloc(sizeof(PatchPanel));

  static const char *src_types[] = {
    "FilterEG", "AmpEG", "LFO1", "LFO2", "Velocity",
    "Kbd track", "Pitch bend", "Mod wheel"};
  static const char src_types_nb = 8;

  static const char *dst_types[] = {
    "Pitch", "Osc2 Tune", "Osc1 Ctrl 1", "NoiseLevel",
    "Cut off", "Amp", "Pan", "LFO2 freq"};
  static const char dst_types_nb = 8;

  static const char * src_names[] = {
    "combobox_patch1_src","combobox_patch2_src",
    "combobox_patch3_src","combobox_patch4_src"};

  static const char * dst_names[] = {
    "combobox_patch1_dst","combobox_patch2_dst",
    "combobox_patch3_dst","combobox_patch4_dst"};

  static const char * int_names[] = {
    "adjust_patch1","adjust_patch2",
    "adjust_patch3","adjust_patch4"};

  static const int patch_names_nb = 4;

  int nameIdx = 0,srcIdx = 0,dstIdx = 0;

  panel->layer = layer;

  for(nameIdx = 0; nameIdx < patch_names_nb; nameIdx++) {
    panel->combobox_patch_src[nameIdx] =
      (GtkWidget*) gtk_builder_get_object(builder,src_names[nameIdx]);
    panel->combobox_patch_dst[nameIdx] =
      (GtkWidget*) gtk_builder_get_object(builder,dst_names[nameIdx]);
    panel->adjust_patch_int[nameIdx] =
      (GtkWidget*) gtk_builder_get_object(builder,int_names[nameIdx]);

    for(srcIdx = 0; srcIdx < src_types_nb; srcIdx++) {
      gtk_combo_box_text_append_text(
          GTK_COMBO_BOX_TEXT(panel->combobox_patch_src[nameIdx]),
          src_types[srcIdx]);
    }

    for(dstIdx = 0; dstIdx < dst_types_nb; dstIdx++) {
      gtk_combo_box_text_append_text(
          GTK_COMBO_BOX_TEXT(panel->combobox_patch_dst[nameIdx]),
          dst_types[dstIdx]);
    }
  }

  return panel;
}

void patch_panel_set(PatchPanel *panel,const ProgMsg *progMsg) {
  int idx = 0;
  
  for(idx = 0; idx < 4; idx++) {
    gtk_combo_box_set_active(
        GTK_COMBO_BOX(panel->combobox_patch_src[idx]),
        getPatchSrc(panel->layer,idx,progMsg));

    gtk_combo_box_set_active(
        GTK_COMBO_BOX(panel->combobox_patch_dst[idx]),
        getPatchDst(panel->layer,idx,progMsg));

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->adjust_patch_int[idx]),
        getPatchModInt(panel->layer,idx,progMsg));
  }
}

