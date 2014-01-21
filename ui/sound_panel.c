#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "basics_panel.h"
#include "sound_panel.h"
#include "sound_panel_internal.h"
#include "sound_panel_cb.h"
#include "lib_bindings.h"

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
  panel->libSignalHook = gtk_label_new(0);

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

  panel->voice[0].adjust_detune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_detune0");
  panel->voice[1].adjust_detune = 
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_detune1");

  for(layer = 0; layer < 2; layer++) {
    ADD_COMBOBOX_ITEM(panel->voice,combobox_assign,"Mono");
    ADD_COMBOBOX_ITEM(panel->voice,combobox_assign,"Poly");
    ADD_COMBOBOX_ITEM(panel->voice,combobox_assign,"Unison");
  
    ADD_COMBOBOX_ITEM(panel->voice,combobox_trigger,"Single");
    ADD_COMBOBOX_ITEM(panel->voice,combobox_trigger,"Multi");
  }

  basics_panel_build(panel);

  gtk_widget_set_sensitive(panel->voice[0].scale_detune,0);
  gtk_widget_set_sensitive(panel->voice[1].scale_detune,0);

  lib_bindings_build(panel);

  sound_panel_cb_build(panel);

  return panel;
}

#undef GET_BUILDER_OBJ_S
#undef GET_BUILDER_OBJ
#undef ADD_COMBOBOX_ITEM_S
#undef ADD_COMBOBOX_ITEM


void sound_panel_set(SoundPanel *panel,const ProgMsg *progMsg) {
  VoiceLayer layer = TIMBRE_1;
  AssignMode assignMode;
  

  basics_panel_change_mode(panel,getVoiceMode(progMsg));

  for(layer = 0; layer < 2; layer++) {
    switch(assignMode = getAssignMode(layer,progMsg)) {
      case ASSIGN_MODE_MONO :
        set_combo_box_value(panel->voice[layer].combobox_assign,ASSIGN_MODE_MONO);
        break;
      case ASSIGN_MODE_POLY :
        set_combo_box_value(panel->voice[layer].combobox_assign,ASSIGN_MODE_POLY);
        break;
      case ASSIGN_MODE_UNISON :
        set_combo_box_value(panel->voice[layer].combobox_assign,ASSIGN_MODE_UNISON);
        break;
    };

    switch(getTriggerMode(layer,progMsg)) {
      case TRIGGER_MODE_SINGLE :
        set_combo_box_value(panel->voice[layer].combobox_trigger,TRIGGER_MODE_SINGLE);
        break;
      case TRIGGER_MODE_MULTI :
        set_combo_box_value(panel->voice[layer].combobox_trigger,TRIGGER_MODE_MULTI);
        break;
    }

    gtk_widget_set_sensitive(panel->voice[layer].scale_detune,
        assignMode == ASSIGN_MODE_UNISON ? 1 : 0);
    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->voice[layer].adjust_detune),
        getUnisonDetune(layer,progMsg));

  }

}


