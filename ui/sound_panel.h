#ifndef SOUND_PANEL_H
#define SOUND_PANEL_H

#include <gtk/gtk.h>
#include "ProgMsg.h"

void sound_panel_build(GtkBuilder *builder);
void sound_panel_set(const ProgMsg *progMsg);

#endif // SOUND_PANEL_H
