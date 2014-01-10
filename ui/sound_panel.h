#ifndef SOUND_PANEL_H
#define SOUND_PANEL_H

#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _SoundPanel SoundPanel;

SoundPanel * sound_panel_build(GtkBuilder *builder);
void sound_panel_set(SoundPanel *, const ProgMsg *);

#endif // SOUND_PANEL_H
