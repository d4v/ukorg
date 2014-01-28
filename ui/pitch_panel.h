#ifndef PITCH_PANEL_H
#define PITCH_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _PitchPanel PitchPanel;

PitchPanel * pitch_panel_build(GtkBuilder*,VoiceLayer);
void pitch_panel_cb_build(PitchPanel *);
void pitch_panel_set(PitchPanel *,const ProgMsg *);

#endif // PITCH_PANEL_H
