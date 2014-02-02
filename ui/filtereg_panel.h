#ifndef FILTEREG_PANEL_H
#define FILTEREG_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _FilterEgPanel FilterEgPanel;

FilterEgPanel * filtereg_panel_build(GtkBuilder*,VoiceLayer);
void filtereg_panel_set(FilterEgPanel *,const ProgMsg *);

#endif // FILTEREG_PANEL_H
