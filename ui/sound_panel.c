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
  
  panel->libSignalHook = gtk_label_new(0);

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

  basics_panel_build(builder,&panel->basics);

  gtk_widget_set_sensitive(panel->voice[0].scale_detune,0);
  gtk_widget_set_sensitive(panel->voice[1].scale_detune,0);

  panel->pitch[0].adjust_tune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_tune0");
  panel->pitch[1].adjust_tune =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_tune1");

  panel->pitch[0].adjust_transpose =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_transpose0");
  panel->pitch[1].adjust_transpose =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_transpose1");

  panel->pitch[0].adjust_portamento =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_portamento0");
  panel->pitch[1].adjust_portamento =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_portamento1");

  panel->pitch[0].adjust_bendrange =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_bendrange0");
  panel->pitch[1].adjust_bendrange =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_bendrange1");

  panel->pitch[0].adjust_vibratoint =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_vibratoint0");
  panel->pitch[1].adjust_vibratoint =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_vibratoint1");

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
  

  basics_panel_change_mode(&panel->basics,getVoiceMode(progMsg));

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

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->pitch[layer].adjust_transpose),
        getTranspose(layer,progMsg));

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->pitch[layer].adjust_tune),
        getTune(layer,progMsg));

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->pitch[layer].adjust_portamento),
        getPortamento(layer,progMsg));

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->pitch[layer].adjust_bendrange),
        getBendRange(layer,progMsg));

    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->pitch[layer].adjust_vibratoint),
        getVibratoInt(layer,progMsg));

  }

}


