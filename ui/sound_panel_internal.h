#ifndef SOUND_PANEL_INTERNAL_H
#define SOUND_PANEL_INTERNAL_H

#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _BasicsPanel BasicsPanel;

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

typedef struct _SoundPanel {
  GtkWidget  *libSignalHook; //!< Not a real widget, will receive lib signal
  BasicsPanel *basics;
  VoicePanel  voice[2];
  PitchPanel  pitch[2];
} SoundPanel;

#endif // SOUND_PANEL_INTERNAL_H
