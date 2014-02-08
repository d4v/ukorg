#ifndef AMPEG_PANEL_H
#define AMPEG_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _AmpEgPanel AmpEgPanel;

AmpEgPanel * ampeg_panel_build(GtkBuilder*,VoiceLayer);
void ampeg_panel_set(AmpEgPanel *,const ProgMsg *);

#endif // AMPEG_PANEL_H
