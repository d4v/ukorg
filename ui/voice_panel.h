#ifndef VOICE_PANEL_H
#define VOICE_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _VoicePanel VoicePanel;

void voice_panel_build(GtkBuilder *,VoiceLayer,VoicePanel *);

#endif // VOICE_PANEL_H
