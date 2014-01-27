#include "voice_panel.h"
#include "sound_panel_internal.h"

void voice_panel_build_timbre_1(GtkBuilder *builder,VoicePanel *panel) {
  panel->combobox_assign =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_assign0");
  panel->combobox_trigger =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_trigger0");
  panel->scale_detune =
    (GtkWidget*) gtk_builder_get_object(builder,"scale_detune0");
  panel->adjust_detune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_detune0");
}

void voice_panel_build_timbre_2(GtkBuilder *builder,VoicePanel *panel) {
  panel->combobox_assign =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_assign1");
  panel->combobox_trigger =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_trigger1");
  panel->scale_detune =
    (GtkWidget*) gtk_builder_get_object(builder,"scale_detune1");
  panel->adjust_detune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_detune1");
}

void voice_panel_build(GtkBuilder *builder,
                       VoiceLayer layer,
                       VoicePanel *panel) {
  switch (layer) {
    case TIMBRE_1:
      voice_panel_build_timbre_1(builder,panel);
      break;
    case TIMBRE_2:
      voice_panel_build_timbre_2(builder,panel);
      break;
  }

  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_assign),"Mono");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_assign),"Poly");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_assign),"Unison");
    
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_trigger),"Single");
  gtk_combo_box_text_append_text(
      GTK_COMBO_BOX_TEXT(panel->combobox_trigger),"Multi");
 
  gtk_widget_set_sensitive(panel->scale_detune,0);

}

