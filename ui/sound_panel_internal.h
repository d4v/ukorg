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

typedef struct _SoundPanel {
  BasicsPanel basics;
  VoicePanel  voice[2];
  GtkWidget  *notebook_layers;
  GtkWidget  *box_timbre[2];
  GtkWidget  *box_params_slot;
} SoundPanel;

void basics_panel_set(SoundPanel*,VoiceMode);

#endif // SOUND_PANEL_INTERNAL_H
