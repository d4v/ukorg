#include "sound_panel.h"

typedef struct _BasicsPanel {
  GtkWidget *combobox_voice;
  GtkWidget *combobox_layer;
} BasicsPanel;

typedef struct _VoicePanel {
  GtkWidget *combobox_assign;
  GtkWidget *combobox_trigger;
  GtkWidget *scale_detune;
} VoicePanel;

static BasicsPanel basics_panel;
static VoicePanel  voice_panel[2];
static GtkWidget *notebook_layers;
static GtkWidget *box_timbre[2];
static GtkWidget *box_params_slot;

#define GET_BUILDER_OBJ_S(panel,obj) \
  panel.obj = (GtkWidget*) gtk_builder_get_object(builder,#obj);

#define ADD_COMBOBOX_ITEM_S(panel,box,text) \
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(panel.box),text)  

#define GET_BUILDER_OBJ(panel,layer,obj) \
  panel[layer].obj = (GtkWidget*) gtk_builder_get_object(builder,#obj#layer);

#define ADD_COMBOBOX_ITEM(panel,box,text) \
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(panel[layer].box),text)  

void sound_panel_build(GtkBuilder *builder) {
  int layer = 0;

  box_params_slot = (GtkWidget*) gtk_builder_get_object(builder,"box_params_slot"); 
  box_timbre[0] =   (GtkWidget*) gtk_builder_get_object(builder,"box_timbre0");
  box_timbre[1] =   (GtkWidget*) gtk_builder_get_object(builder,"box_timbre1");
  notebook_layers = gtk_notebook_new();

  GET_BUILDER_OBJ_S(basics_panel,combobox_voice);
  ADD_COMBOBOX_ITEM_S(basics_panel,combobox_voice,"Synthesizer");
  ADD_COMBOBOX_ITEM_S(basics_panel,combobox_voice,"Vocoder");

  GET_BUILDER_OBJ_S(basics_panel,combobox_layer);
  ADD_COMBOBOX_ITEM_S(basics_panel,combobox_layer,"Single");
  ADD_COMBOBOX_ITEM_S(basics_panel,combobox_layer,"Layer");

  GET_BUILDER_OBJ(voice_panel,0,combobox_assign);
  GET_BUILDER_OBJ(voice_panel,1,combobox_assign);

  GET_BUILDER_OBJ(voice_panel,0,combobox_trigger);
  GET_BUILDER_OBJ(voice_panel,1,combobox_trigger);

  GET_BUILDER_OBJ(voice_panel,0,scale_detune);
  GET_BUILDER_OBJ(voice_panel,1,scale_detune);

  for(layer = 0; layer < 2; layer++) {
    ADD_COMBOBOX_ITEM(voice_panel,combobox_assign,"Mono");
    ADD_COMBOBOX_ITEM(voice_panel,combobox_assign,"Poly");
    ADD_COMBOBOX_ITEM(voice_panel,combobox_assign,"Unison");
  
    ADD_COMBOBOX_ITEM(voice_panel,combobox_trigger,"Single");
    ADD_COMBOBOX_ITEM(voice_panel,combobox_trigger,"Multi");
  }

}

#undef GET_BUILDER_OBJ_S
#undef GET_BUILDER_OBJ
#undef ADD_COMBOBOX_ITEM_S
#undef ADD_COMBOBOX_ITEM

enum {
  GTK_VOICE_SYNTH,
  GTK_VOICE_VOCODER,
};

enum {
  GTK_LAYER_SINGLE,
  GTK_LAYER_DOUBLE,
};

enum {
  GTK_ASSIGN_MONO,
  GTK_ASSIGN_POLY,
  GTK_ASSIGN_UNISON,
};

enum {
  GTK_TRIGGER_SINGLE,
  GTK_TRIGGER_MULTI,
};

#define SET_COMBOBOX_VALUE_S(panel,box,value) \
  gtk_combo_box_set_active( \
      GTK_COMBO_BOX(panel.box),value);

#define SET_COMBOBOX_VALUE(panel,box,value) \
  gtk_combo_box_set_active( \
      GTK_COMBO_BOX(panel[layer].box),value);

void sound_panel_set(const ProgMsg *progMsg) {
  VoiceLayer layer = TIMBRE_1;

  gtk_widget_unparent(box_timbre[0]);
  gtk_widget_unparent(box_timbre[1]);
  gtk_widget_unparent(notebook_layers);

  switch(getVoiceMode(progMsg)) {
    case VOICE_MODE_SINGLE :
      SET_COMBOBOX_VALUE_S(basics_panel,combobox_voice,GTK_VOICE_SYNTH);
      gtk_widget_set_sensitive(basics_panel.combobox_layer,1);
      SET_COMBOBOX_VALUE_S(basics_panel,combobox_layer,GTK_LAYER_SINGLE);
      gtk_box_pack_start(GTK_BOX(box_params_slot),box_timbre[TIMBRE_1],0,0,0);
      break;
    case VOICE_MODE_LAYER :
      SET_COMBOBOX_VALUE_S(basics_panel,combobox_voice,GTK_VOICE_SYNTH);
      gtk_widget_set_sensitive(basics_panel.combobox_layer,1);
      SET_COMBOBOX_VALUE_S(basics_panel,combobox_layer,GTK_LAYER_DOUBLE);
      gtk_notebook_append_page(
          GTK_NOTEBOOK(notebook_layers),box_timbre[TIMBRE_1],NULL);
      gtk_notebook_append_page(
          GTK_NOTEBOOK(notebook_layers),box_timbre[TIMBRE_2],NULL);
      gtk_box_pack_start(GTK_BOX(box_params_slot),notebook_layers,0,0,0);
      break;
    case VOICE_MODE_VOCODER :
      SET_COMBOBOX_VALUE_S(basics_panel,combobox_voice,GTK_VOICE_VOCODER);
      gtk_widget_set_sensitive(basics_panel.combobox_layer,0);
      SET_COMBOBOX_VALUE_S(basics_panel,combobox_layer,-1);
      break;
  };

  for(layer = 0; layer < 2; layer++) {
    switch(getAssignMode(layer,progMsg)) {
      case ASSIGN_MODE_MONO :
        SET_COMBOBOX_VALUE(voice_panel,combobox_assign,GTK_ASSIGN_MONO);
        break;
      case ASSIGN_MODE_POLY :
        SET_COMBOBOX_VALUE(voice_panel,combobox_assign,GTK_ASSIGN_POLY);
        break;
      case ASSIGN_MODE_UNISON :
        SET_COMBOBOX_VALUE(voice_panel,combobox_assign,GTK_ASSIGN_UNISON);
        break;
    };
  }

  gtk_widget_show_all(box_params_slot);
}


