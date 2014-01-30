#ifndef OSC1_PANEL_H
#define OSC1_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _Osc1Panel Osc1Panel;

Osc1Panel * osc1_panel_build(GtkBuilder*,VoiceLayer);
void osc1_panel_cb_build(Osc1Panel *);
void osc1_panel_set(Osc1Panel *,const ProgMsg *);

#endif // OSC1_PANEL_H
