#ifndef BASICS_PANEL_H
#define BASICS_PANEL_H

typedef struct _SoundPanel SoundPanel;
typedef enum   _VoiceMode  VoiceMode;

void basics_panel_build(SoundPanel *);
void basics_panel_change_mode(SoundPanel *, VoiceMode newMode);

#endif // BASICS_PANEL_H
