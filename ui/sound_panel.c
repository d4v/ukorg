#include "sound_panel.h"

typedef struct _VoicePanel {
  GtkWidget *combobox_voice;
  GtkWidget *combobox_layer;
  GtkWidget *combobox_assign;
  GtkWidget *combobox_trigger;
  GtkWidget *scale_detune;
} VoicePanel;

static VoicePanel voice_panel;

enum {
  VOICE_SYNTH,
  VOICE_VOCODER,
};

enum {
  LAYER_SINGLE,
  LAYER_LAYER,
};

enum {
  ASSIGN_MONO,
  ASSIGN_POLY,
  ASSIGN_UNISON,
};

enum {
  TRIGGER_SINGLE,
  TRIGGER_MULTI,
};

#define GET_BUILDER_OBJ(obj) \
  voice_panel.obj = (GtkWidget*) gtk_builder_get_object(builder,#obj);

#define ADD_COMBOBOX_ITEM(box,text) \
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(voice_panel.box),text)  

void sound_panel_build(GtkBuilder *builder) {

  GET_BUILDER_OBJ(combobox_voice);
  ADD_COMBOBOX_ITEM(combobox_voice,"Synthesizer");
  ADD_COMBOBOX_ITEM(combobox_voice,"Vocoder");

  GET_BUILDER_OBJ(combobox_layer);
  ADD_COMBOBOX_ITEM(combobox_layer,"Single");
  ADD_COMBOBOX_ITEM(combobox_layer,"Layer");

  GET_BUILDER_OBJ(combobox_assign);
  ADD_COMBOBOX_ITEM(combobox_assign,"Mono");
  ADD_COMBOBOX_ITEM(combobox_assign,"Poly");
  ADD_COMBOBOX_ITEM(combobox_assign,"Unison");

  GET_BUILDER_OBJ(combobox_trigger);
  ADD_COMBOBOX_ITEM(combobox_trigger,"Single");
  ADD_COMBOBOX_ITEM(combobox_trigger,"Multi");

  GET_BUILDER_OBJ(scale_detune);
}

void sound_panel_set(const ProgMsg *progMsg) {

  switch(getVoiceMode(progMsg)) {
    case VOICE_MODE_SINGLE :
      gtk_combo_box_set_active(
          GTK_COMBO_BOX(voice_panel.combobox_voice),VOICE_SYNTH);
      gtk_widget_set_sensitive(voice_panel.combobox_layer,1);
      gtk_combo_box_set_active(
          GTK_COMBO_BOX(voice_panel.combobox_layer),LAYER_SINGLE);
      break;
    case VOICE_MODE_LAYER :
      gtk_combo_box_set_active(
          GTK_COMBO_BOX(voice_panel.combobox_voice),VOICE_SYNTH);
      gtk_widget_set_sensitive(voice_panel.combobox_layer,1);
      gtk_combo_box_set_active(
          GTK_COMBO_BOX(voice_panel.combobox_layer),LAYER_DOUBLE);
      break;
    case VOICE_MODE_VOCODER :
      gtk_combo_box_set_active(
          GTK_COMBO_BOX(voice_panel.combobox_voice),VOICE_VOCODER);
      gtk_widget_set_sensitive(voice_panel.combobox_layer,0);
      gtk_combo_box_set_active(
          GTK_COMBO_BOX(voice_panel.combobox_layer),-1);
      break;
  };
}


