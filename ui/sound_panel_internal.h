#ifndef SOUND_PANEL_INTERNAL_H
#define SOUND_PANEL_INTERNAL_H

#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _BasicsPanel BasicsPanel;
typedef struct _VoicePanel  VoicePanel;
typedef struct _PitchPanel  PitchPanel;
typedef struct _Osc1Panel   Osc1Panel;
typedef struct _Osc2Panel   Osc2Panel;
typedef struct _MixerPanel  MixerPanel;
typedef struct _FilterPanel FilterPanel;

typedef struct _SoundPanel {
  GtkWidget   *libSignalHook; //!< Not a real widget, will receive lib signal
  BasicsPanel *basics;
  VoicePanel  *voice[2];
  PitchPanel  *pitch[2];
  Osc1Panel   *osc1[2];
  Osc2Panel   *osc2[2];
  MixerPanel  *mixer[2];
  FilterPanel *filter[2];
} SoundPanel;

#endif // SOUND_PANEL_INTERNAL_H
