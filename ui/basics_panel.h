#ifndef BASICS_PANEL_H
#define BASICS_PANEL_H

typedef struct _BasicsPanel BasicsPanel;
typedef enum   _VoiceMode  VoiceMode;

void basics_panel_build(GtkBuilder *,BasicsPanel *);
void basics_panel_change_mode(BasicsPanel *, VoiceMode newMode);

enum {
  GTK_VOICE_SYNTH,
  GTK_VOICE_VOCODER,
};

enum {
  GTK_LAYER_SINGLE,
  GTK_LAYER_DOUBLE,
};

#endif // BASICS_PANEL_H
