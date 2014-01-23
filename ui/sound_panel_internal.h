#ifndef SOUND_PANEL_INTERNAL_H
#define SOUND_PANEL_INTERNAL_H

#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _BasicsPanel {
  GtkWidget *combobox_voice;
  GtkWidget *combobox_layer;
} BasicsPanel;

typedef struct _VoicePanel {
  GtkWidget *combobox_assign;
  GtkWidget *combobox_trigger;
  GtkWidget *scale_detune;
  GtkAdjustment *adjust_detune;
} VoicePanel;

typedef struct _PitchPanel {
  GtkAdjustment *adjust_tune;
  GtkAdjustment *adjust_transpose;
  GtkAdjustment *adjust_portamento;
  GtkAdjustment *adjust_bendrange;
  GtkAdjustment *adjust_vibratoint;
} PitchPanel;

typedef struct _CbHandlers {
  gulong voice_changed;
  gulong layer_changed;
} CbHandlers;

typedef struct _SoundPanel {
  GtkWidget  *libSignalHook; //!< Not a real widget, will receive lib signal
  VoiceMode   voiceMode;
  CbHandlers  cbHandlers;
  BasicsPanel basics;
  VoicePanel  voice[2];
  PitchPanel  pitch[2];
  GtkWidget  *notebook_layers;
  GtkWidget  *label_layer_name[2];
  GtkWidget  *box_timbre[2];
  GtkWidget  *box_params_slot;
} SoundPanel;

enum {
  GTK_VOICE_SYNTH,
  GTK_VOICE_VOCODER,
};

enum {
  GTK_LAYER_SINGLE,
  GTK_LAYER_DOUBLE,
};

#endif // SOUND_PANEL_INTERNAL_H
