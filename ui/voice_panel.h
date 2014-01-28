#ifndef VOICE_PANEL_H
#define VOICE_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _VoicePanel VoicePanel;

VoicePanel * voice_panel_build(GtkBuilder *,VoiceLayer);
void voice_panel_cb_build(VoicePanel *);
void voice_panel_set(VoicePanel *,const ProgMsg *);

#endif // VOICE_PANEL_H
