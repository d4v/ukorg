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
} VoicePanel;

typedef struct _CbHandlers {
  gulong voice_changed;
  gulong layer_changed;
} CbHandlers;

typedef struct _SoundPanel {
  VoiceMode   voiceMode;
  CbHandlers  cbHandlers;
  BasicsPanel basics;
  VoicePanel  voice[2];
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

enum {
  GTK_ASSIGN_MONO,
  GTK_ASSIGN_POLY,
  GTK_ASSIGN_UNISON,
};

enum {
  GTK_TRIGGER_SINGLE,
  GTK_TRIGGER_MULTI,
};


#endif // SOUND_PANEL_INTERNAL_H
