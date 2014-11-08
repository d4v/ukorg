#ifndef PATCH_PANEL_H
#define PATCH_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _PatchPanel PatchPanel;

PatchPanel * patch_panel_build(GtkBuilder*,VoiceLayer);
void patch_panel_set(PatchPanel *,const ProgMsg *);

void patch_panel_cb_build(PatchPanel *panel);

#endif // PATCH_PANEL_H
