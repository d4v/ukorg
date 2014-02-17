#ifndef LFO2_PANEL_H
#define LFO2_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _Lfo2Panel Lfo2Panel;

Lfo2Panel * lfo2_panel_build(GtkBuilder*,VoiceLayer);
void lfo2_panel_set(Lfo2Panel *,const ProgMsg *);

void lfo2_panel_cb_build(Lfo2Panel *panel);

#endif // LFO2_PANEL_H
