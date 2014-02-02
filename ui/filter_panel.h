#ifndef FILTER_PANEL_H
#define FILTER_PANEL_H
#include <gtk/gtk.h>
#include "ProgMsg.h"

typedef struct _FilterPanel FilterPanel;

FilterPanel * filter_panel_build(GtkBuilder*,VoiceLayer);
void filter_panel_set(FilterPanel *,const ProgMsg *);

#endif // FILTER_PANEL_H
