#include <stdbool.h>
#include <stdlib.h>
#include "osc1_panel.h"

typedef struct _Osc1Panel {
  VoiceLayer     layer;
  GtkAdjustment *adjust_level;
  GtkWidget     *combobox_wave;
  WaveType       wave_type;
  GtkWidget     *scale_ctrl1;
  GtkAdjustment *adjust_ctrl1;
  GtkWidget     *slot_ctrl2;
  GtkWidget     *scale_ctrl2;
  GtkAdjustment *adjust_ctrl2;
  GtkWidget     *combobox_dwgs;
} Osc1Panel;

Osc1Panel * osc1_panel_build(GtkBuilder *builder,VoiceLayer layer) {
  Osc1Panel *panel = (Osc1Panel*) malloc(sizeof(Osc1Panel));
  int idx = 0;

  static const char *wave_types[] = {
    "Saw","Square","Triangle","Sine"    ,
    "Vox","DWGS"  ,"Noise"   ,"Audio In"}; // 8
  static const int wave_types_nb = 8;

  static const char *dwgs_sounds[] = {
    "SynSine1","SynSine2","SynSine3","SynSine4",
    "SynSine5","SynSine6","SynSine7","SynBass1", // 8
    "SynBass2","SynBass3","SynBass4","SynBass5",
    "SynBass6","SynBass7","SynWave1","SynWave2", // 16
    "SynWave3","SynWave4","SynWave5","SynWave6",
    "SynWave7","SynWave8","SynWave9","5thWave1", // 24
    "5thWave2","5thWave3","Digi1"   ,"Digi2"   ,
    "Digi3"   ,"Digi4"   ,"Digi5"   ,"Digi6"   , // 32
    "Digi7"   ,"Digi8"   ,"Endless" ,"E.Piano1",
    "E.Piano2","E.Piano3","E.Piano4","Organ1"  , // 40
    "Organ2"  ,"Organ3"  ,"Organ4"  ,"Organ5"  ,
    "Organ6"  ,"Organ7"  ,"Clav1"   ,"Clav2"   , // 48
    "Guitar1" ,"Guitar2" ,"Guitar3" ,"Bass1"   ,
    "Bass2"   ,"Bass3"   ,"Bass4"   ,"Bass5"   , // 56
    "Bell1"   ,"Bell2"   ,"Bell3"   ,"Bell4"   ,
    "Voice1"  ,"Voice2"  ,"Voice3"  ,"Voice4" }; // 64
  static const int dwgs_sounds_nb = 64;

  panel->layer = layer;

  panel->adjust_level =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc1level");

  panel->combobox_wave =
    (GtkWidget*) gtk_builder_get_object(builder,"combobox_osc1wave");
  panel->scale_ctrl1 =
    (GtkWidget*) gtk_builder_get_object(builder,"scale_osc1ctrl1");
  panel->adjust_ctrl1 =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc1ctrl1");

  panel->slot_ctrl2 = 
    (GtkWidget*) gtk_builder_get_object(builder,"slot_osc1ctrl2");
  panel->scale_ctrl2 =
    (GtkWidget*) gtk_builder_get_object(builder,"scale_osc1ctrl2");
  panel->adjust_ctrl2 =
    (GtkAdjustment*) gtk_builder_get_object(builder,"adjust_osc1ctrl2");

  panel->combobox_dwgs =
    (GtkWidget*) gtk_combo_box_text_new();

  // Keep a reference on those object so they are not destroyed when
  // temporary detached
  g_object_ref(panel->combobox_dwgs);
  g_object_ref(panel->scale_ctrl2);

  for(idx = 0; idx < wave_types_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_wave),wave_types[idx]);
  }

  for(idx = 0; idx < dwgs_sounds_nb; idx++) {
    gtk_combo_box_text_append_text(
        GTK_COMBO_BOX_TEXT(panel->combobox_dwgs),dwgs_sounds[idx]);
  }

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_wave),-1);

  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_dwgs),-1);

  return panel;
}

void osc1_panel_unset_layout(Osc1Panel *panel) {
  if(panel->wave_type == WAV_DWGS) {
    gtk_container_remove(GTK_CONTAINER(panel->slot_ctrl2),
                         panel->combobox_dwgs);
  } else {
    gtk_container_remove(GTK_CONTAINER(panel->slot_ctrl2),
                         panel->scale_ctrl2);
  }
}

void osc1_panel_set_layout(Osc1Panel *panel) {
  if(panel->wave_type == WAV_DWGS) {
    gtk_container_add(GTK_CONTAINER(panel->slot_ctrl2),
                      panel->combobox_dwgs);
    gtk_widget_set_sensitive(GTK_WIDGET(panel->scale_ctrl1),0);
  } else {
    gtk_container_add(GTK_CONTAINER(panel->slot_ctrl2),
                      panel->scale_ctrl2);
    gtk_widget_set_sensitive(GTK_WIDGET(panel->scale_ctrl1),1);
  }

  gtk_widget_show_all(panel->slot_ctrl2);
}

void osc1_panel_change_layout(Osc1Panel *panel,WaveType wave_type) {
  osc1_panel_unset_layout(panel);
  panel->wave_type = wave_type;
  osc1_panel_set_layout(panel);
}

/**
 * Shall we switch the layout between dwgs combobox and ctrl2 scale?
 */
static inline
bool osc1_layout_switch_test(WaveType old, WaveType new) {
  return (    new != old
           && (    new == WAV_DWGS
                || old == WAV_DWGS));
}

void osc1_panel_set(Osc1Panel *panel,const ProgMsg *progMsg) {
  WaveType newType = getOsc1WaveType(panel->layer,progMsg);

  if(osc1_layout_switch_test(panel->wave_type,newType)) {
    osc1_panel_change_layout(panel,newType);
  }

  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_level),
      getOsc1Level(panel->layer,progMsg));
  
  gtk_combo_box_set_active(
      GTK_COMBO_BOX(panel->combobox_wave),
      getOsc1WaveType(panel->layer,progMsg));
  gtk_adjustment_set_value(
      GTK_ADJUSTMENT(panel->adjust_ctrl1),
      getOsc1Ctrl1(panel->layer,progMsg));

  if(newType == WAV_DWGS) {
    gtk_combo_box_set_active(
        GTK_COMBO_BOX(panel->combobox_dwgs),
        getOsc1DwgsWave(panel->layer,progMsg));
  } else {
    gtk_adjustment_set_value(
        GTK_ADJUSTMENT(panel->adjust_ctrl2),
        getOsc1Ctrl2(panel->layer,progMsg));
  }
}

void osc1_on_wave_type_changed(GtkComboBox *combobox,gpointer user_data) {
  Osc1Panel *panel = (Osc1Panel*) user_data;
  WaveType newType = gtk_combo_box_get_active(combobox);

  if(osc1_layout_switch_test(panel->wave_type,newType)) {
    osc1_panel_change_layout(panel,newType);
  }
}

void osc1_panel_cb_build(Osc1Panel *panel) {
  g_signal_connect(panel->combobox_wave,"changed",
      (GCallback) osc1_on_wave_type_changed,panel);
}

