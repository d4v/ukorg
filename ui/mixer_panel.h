#ifndef MIXER_PANEL_H
#define MIXER_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _MixerPanel MixerPanel;

MixerPanel * mixer_panel_build(GtkBuilder*,VoiceLayer);
void mixer_panel_set(MixerPanel *,const ProgMsg *);

#endif // MIXER_PANEL_H
