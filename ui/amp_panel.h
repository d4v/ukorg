#ifndef AMP_PANEL_H
#define AMP_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _AmpPanel AmpPanel;

AmpPanel * amp_panel_build(GtkBuilder*,VoiceLayer);
void amp_panel_set(AmpPanel *,const ProgMsg *);

#endif // AMP_PANEL_H
