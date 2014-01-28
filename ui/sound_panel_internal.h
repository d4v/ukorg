#ifndef SOUND_PANEL_INTERNAL_H
#define SOUND_PANEL_INTERNAL_H

#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _BasicsPanel BasicsPanel;
typedef struct _VoicePanel  VoicePanel;
typedef struct _PitchPanel  PitchPanel;

typedef struct _SoundPanel {
  GtkWidget   *libSignalHook; //!< Not a real widget, will receive lib signal
  BasicsPanel *basics;
  VoicePanel  *voice[2];
  PitchPanel  *pitch[2];
} SoundPanel;

#endif // SOUND_PANEL_INTERNAL_H
