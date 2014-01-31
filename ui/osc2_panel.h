#ifndef OSC2_PANEL_H
#define OSC2_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _Osc2Panel Osc2Panel;

Osc2Panel * osc2_panel_build(GtkBuilder*,VoiceLayer);
void osc2_panel_set(Osc2Panel *,const ProgMsg *);

#endif // OSC2_PANEL_H
