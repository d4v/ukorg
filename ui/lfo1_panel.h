#ifndef LFO1_PANEL_H
#define LFO1_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _Lfo1Panel Lfo1Panel;

Lfo1Panel * lfo1_panel_build(GtkBuilder*,VoiceLayer);
void lfo1_panel_set(Lfo1Panel *,const ProgMsg *);

void lfo1_panel_cb_build(Lfo1Panel *panel);

#endif // LFO1_PANEL_H
