#ifndef PITCH_PANEL_H
#define PITCH_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _PitchPanel PitchPanel;

void pitch_panel_build(GtkBuilder*,VoiceLayer,PitchPanel*);

#endif // PITCH_PANEL_H
