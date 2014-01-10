#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sound_panel.h"
#include "sound_panel_internal.h"
#include "sound_panel_cb.h"

#define GET_BUILDER_OBJ_S(panel,obj) \
  panel.obj = (GtkWidget*) gtk_builder_get_object(builder,#obj);

#define ADD_COMBOBOX_ITEM_S(panel,box,text) \
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(panel.box),text)  

#define GET_BUILDER_OBJ(panel,layer,obj) \
  panel[layer].obj = (GtkWidget*) gtk_builder_get_object(builder,#obj#layer);

#define ADD_COMBOBOX_ITEM(panel,box,text) \
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(panel[layer].box),text)  

SoundPanel *sound_panel_build(GtkBuilder *builder) {

  int layer = 0;
  SoundPanel *panel = (SoundPanel*) malloc(sizeof(SoundPanel));

  panel->box_params_slot = (GtkWidget*) gtk_builder_get_object(builder,"box_params_slot"); 
  panel->box_timbre[0] =   (GtkWidget*) gtk_builder_get_object(builder,"box_timbre0");
  panel->box_timbre[1] =   (GtkWidget*) gtk_builder_get_object(builder,"box_timbre1");
  panel->notebook_layers = gtk_notebook_new();
  panel->label_layer_name[0] = gtk_label_new("Timbre 1"); 
  panel->label_layer_name[1] = gtk_label_new("Timbre 2"); 

  // Keep a reference on the moving panels so they are not destroyed when
  // temporary detached
  g_object_ref(panel->box_timbre[0]);
  g_object_ref(panel->box_timbre[1]);
  g_object_ref(panel->notebook_layers);
  g_object_ref(panel->label_layer_name[0]);
  g_object_ref(panel->label_layer_name[1]);

  GET_BUILDER_OBJ_S(panel->basics,combobox_voice);
  ADD_COMBOBOX_ITEM_S(panel->basics,combobox_voice,"Synthesizer");
  ADD_COMBOBOX_ITEM_S(panel->basics,combobox_voice,"Vocoder");

  GET_BUILDER_OBJ_S(panel->basics,combobox_layer);
  ADD_COMBOBOX_ITEM_S(panel->basics,combobox_layer,"Single");
  ADD_COMBOBOX_ITEM_S(panel->basics,combobox_layer,"Layer");

  GET_BUILDER_OBJ(panel->voice,0,combobox_assign);
  GET_BUILDER_OBJ(panel->voice,1,combobox_assign);

  GET_BUILDER_OBJ(panel->voice,0,combobox_trigger);
  GET_BUILDER_OBJ(panel->voice,1,combobox_trigger);

  GET_BUILDER_OBJ(panel->voice,0,scale_detune);
  GET_BUILDER_OBJ(panel->voice,1,scale_detune);

  for(layer = 0; layer < 2; layer++) {
    ADD_COMBOBOX_ITEM(panel->voice,combobox_assign,"Mono");
    ADD_COMBOBOX_ITEM(panel->voice,combobox_assign,"Poly");
    ADD_COMBOBOX_ITEM(panel->voice,combobox_assign,"Unison");
  
    ADD_COMBOBOX_ITEM(panel->voice,combobox_trigger,"Single");
    ADD_COMBOBOX_ITEM(panel->voice,combobox_trigger,"Multi");
  }

  ProgMsg progMsg;
  memset(&progMsg,0,sizeof(ProgMsg));

  sound_panel_set(panel,&progMsg);

  sound_panel_set_cb(panel);

  return panel;
}

#undef GET_BUILDER_OBJ_S
#undef GET_BUILDER_OBJ
#undef ADD_COMBOBOX_ITEM_S
#undef ADD_COMBOBOX_ITEM

void set_combo_box_value(GtkWidget *combobox,int value) {
  if(gtk_combo_box_get_active(GTK_COMBO_BOX(combobox)) != value)
    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox),value);
}

void basics_panel_set(SoundPanel *panel,VoiceMode mode) {
  bool layeringChanged = (mode != panel->voiceMode);
  
  if(layeringChanged) {
    switch(panel->voiceMode) {
      case VOICE_MODE_SINGLE :
        gtk_container_remove(GTK_CONTAINER(panel->box_params_slot),panel->box_timbre[TIMBRE_1]);
        break;
      case VOICE_MODE_LAYER :
        gtk_container_remove(GTK_CONTAINER(panel->notebook_layers),panel->box_timbre[TIMBRE_1]);
        gtk_container_remove(GTK_CONTAINER(panel->notebook_layers),panel->box_timbre[TIMBRE_2]);
        gtk_container_remove(GTK_CONTAINER(panel->box_params_slot),panel->notebook_layers);
        break;
      case VOICE_MODE_VOCODER :
        break;
    };
  }

  switch(mode) {
    case VOICE_MODE_SINGLE :
      set_combo_box_value(panel->basics.combobox_voice,GTK_VOICE_SYNTH);
      set_combo_box_value(panel->basics.combobox_layer,GTK_LAYER_SINGLE);
      gtk_widget_set_sensitive(panel->basics.combobox_layer,1);
      gtk_box_pack_start(GTK_BOX(panel->box_params_slot),panel->box_timbre[TIMBRE_1],0,0,0);
      break;
    case VOICE_MODE_LAYER :
      set_combo_box_value(panel->basics.combobox_voice,GTK_VOICE_SYNTH);
      gtk_widget_set_sensitive(panel->basics.combobox_layer,1);
      set_combo_box_value(panel->basics.combobox_layer,GTK_LAYER_DOUBLE);
      gtk_notebook_append_page(
          GTK_NOTEBOOK(panel->notebook_layers),
          panel->box_timbre[TIMBRE_1],panel->label_layer_name[TIMBRE_1]);
      gtk_notebook_append_page(
          GTK_NOTEBOOK(panel->notebook_layers),
          panel->box_timbre[TIMBRE_2],panel->label_layer_name[TIMBRE_2]);
      gtk_box_pack_start(GTK_BOX(panel->box_params_slot),panel->notebook_layers,0,0,0);
      break;
    case VOICE_MODE_VOCODER :
      set_combo_box_value(panel->basics.combobox_voice,GTK_VOICE_VOCODER);
      gtk_widget_set_sensitive(panel->basics.combobox_layer,0);
      set_combo_box_value(panel->basics.combobox_layer,-1);
      break;
  };
  
  panel->voiceMode = mode;

  gtk_widget_show_all(panel->box_params_slot);
}

void sound_panel_set(SoundPanel *panel,const ProgMsg *progMsg) {
  VoiceLayer layer = TIMBRE_1;

  basics_panel_set(panel,getVoiceMode(progMsg));

  for(layer = 0; layer < 2; layer++) {
    switch(getAssignMode(layer,progMsg)) {
      case ASSIGN_MODE_MONO :
        set_combo_box_value(panel->voice[layer].combobox_assign,GTK_ASSIGN_MONO);
        break;
      case ASSIGN_MODE_POLY :
        set_combo_box_value(panel->voice[layer].combobox_assign,GTK_ASSIGN_POLY);
        break;
      case ASSIGN_MODE_UNISON :
        set_combo_box_value(panel->voice[layer].combobox_assign,GTK_ASSIGN_UNISON);
        break;
    };
  }

}


