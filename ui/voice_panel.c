#include <stdlib.h>
#include "voice_panel.h"
#include "util.h"

typedef struct _VoicePanel {
  VoiceLayer layer;
  GtkWidget *combobox_assign;
  GtkWidget *combobox_trigger;
  GtkWidget *scale_detune;
  GtkAdjustment *adjust_detune;
} VoicePanel;

VoicePanel * voice_panel_build(GtkBuilder *builder,VoiceLayer layer) {

  VoicePanel *panel = (VoicePanel *) malloc(sizeof(VoicePanel));

  static const char * assign_types[] = {"Mono","Poly","Unison"};
  static const int assign_types_nb = 3;
  static const char * trigger_types[] = {"Single","Multi"};
  static const int trigger_types_nb = 2;
  int idx = 0;
    

  panel->layer = layer;

  panel->combobox_assign =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_assign");
  panel->combobox_trigger =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_trigger");
  panel->scale_detune =
    (GtkWidget*) gtk_builder_get_object(builder,"scale_detune");
  panel->adjust_detune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_detune");

  for(idx = 0; idx < assign_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_assign),assign_types[idx]);
  }
  
  for(idx = 0; idx < trigger_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_trigger),trigger_types[idx]);
  }

  gtk_widget_set_sensitive(panel->scale_detune,0);

  return panel;
}

void voice_panel_set(VoicePanel *panel,const ProgMsg *progMsg) {
  AssignMode assignMode;

  switch(assignMode = getAssignMode(panel->layer,progMsg)) {
    case ASSIGN_MODE_MONO :
      set_combo_box_value(panel->combobox_assign,ASSIGN_MODE_MONO);
      break;
    case ASSIGN_MODE_POLY :
      set_combo_box_value(panel->combobox_assign,ASSIGN_MODE_POLY);
      break;
    case ASSIGN_MODE_UNISON :
      set_combo_box_value(panel->combobox_assign,ASSIGN_MODE_UNISON);
      break;
  };

  switch(getTriggerMode(panel->layer,progMsg)) {
    case TRIGGER_MODE_SINGLE :
      set_combo_box_value(panel->combobox_trigger,TRIGGER_MODE_SINGLE);
      break;
    case TRIGGER_MODE_MULTI :
      set_combo_box_value(panel->combobox_trigger,TRIGGER_MODE_MULTI);
      break;
  }

  gtk_widget_set_sensitive(panel->scale_detune,
      assignMode == ASSIGN_MODE_UNISON ? 1 : 0);
  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_detune),
      getUnisonDetune(panel->layer,progMsg));
}

void on_assign_mode_changed(GtkComboBox *combobox,gpointer user_data) {
  VoicePanel *voice_panel = (VoicePanel*) user_data;
  AssignMode mode = gtk_combo_box_get_active(combobox);

  if(mode == ASSIGN_MODE_UNISON)
    gtk_widget_set_sensitive(voice_panel->scale_detune,1);
  else
    gtk_widget_set_sensitive(voice_panel->scale_detune,0);

  if(mode == ASSIGN_MODE_POLY)
    gtk_widget_set_sensitive(voice_panel->combobox_trigger,0);
  else
    gtk_widget_set_sensitive(voice_panel->combobox_trigger,1);
}

void voice_panel_cb_build(VoicePanel *panel) {
  g_signal_connect(panel->combobox_assign,"changed",
                   (GCallback) on_assign_mode_changed,
                   panel);
}

