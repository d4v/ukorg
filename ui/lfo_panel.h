#ifndef LFO_PANEL_H
#define LFO_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _LfoPanel LfoPanel;

LfoPanel * lfo_panel_build(GtkBuilder*,VoiceLayer);
void lfo_panel_set(LfoPanel *panel,const ProgMsg *progMsg);

void lfo_panel_cb_build(LfoPanel *panel);

#endif // LFO_PANEL_H
