#ifndef BASICS_PANEL_H
#define BASICS_PANEL_H

typedef struct _BasicsPanel BasicsPanel;
typedef struct _ProgMsg ProgMsg;

BasicsPanel * basics_panel_build(GtkBuilder *);
void basics_panel_cb_build(BasicsPanel *);
void basics_panel_set(BasicsPanel *panel,const ProgMsg *);

#endif // BASICS_PANEL_H
