#include <fcntl.h>
#include <stdio.h>
#include "sound_panel_internal.h"
#include "sound_panel_cb.h"
#include "basics_panel.h"

void cb_show_open_dialog(GtkWidget * p_wid, gpointer p_data) {
  GtkWidget  *dialog;
  SoundPanel *panel = (SoundPanel*) p_data;

  dialog = gtk_file_chooser_dialog_new (
      "Open File",
      NULL,
      GTK_FILE_CHOOSER_ACTION_OPEN,
      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
      NULL);

  if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    const size_t bufSize = c_ProgMsgSize;
    char buf[bufSize];

    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
    int fd = open(filename,O_RDONLY);

    read(fd,buf,bufSize);

    sound_panel_set(panel,(ProgMsg*) &buf);

    puts(filename);
    g_free (filename);
  }
  gtk_widget_destroy (dialog);

}

void freeze_signals(SoundPanel *panel) {
  g_signal_handler_block(
      panel->basics.combobox_voice,panel->cbHandlers.voice_changed);
  g_signal_handler_block(
      panel->basics.combobox_layering,panel->cbHandlers.layer_changed);
}

void unfreeze_signals(SoundPanel *panel) {
  g_signal_handler_unblock(
      panel->basics.combobox_voice,panel->cbHandlers.voice_changed);
  g_signal_handler_unblock(
      panel->basics.combobox_layering,panel->cbHandlers.layer_changed);
}

void on_voice_mode_changed(GtkComboBox *combobox,gpointer user_data) {
  SoundPanel *panel = (SoundPanel*) user_data;
  VoiceMode mode = VOICE_MODE_SINGLE;

  freeze_signals(panel);

  if(gtk_combo_box_get_active(GTK_COMBO_BOX(panel->basics.combobox_voice)) == GTK_VOICE_VOCODER)
    mode = VOICE_MODE_VOCODER;
  else if(gtk_combo_box_get_active(GTK_COMBO_BOX(panel->basics.combobox_layering)) == GTK_LAYER_DOUBLE)
    mode = VOICE_MODE_LAYER;

  basics_panel_change_mode(&panel->basics,mode);

  unfreeze_signals(panel);
}

void on_assign_mode_changed(GtkComboBox *combobox,gpointer user_data) {
  VoicePanel *voice_panel = (VoicePanel*) user_data;
  AssignMode mode = gtk_combo_box_get_active(combobox);

  if(mode == ASSIGN_MODE_UNISON)
    gtk_widget_set_sensitive(voice_panel->scale_detune,1);
  else
    gtk_widget_set_sensitive(voice_panel->scale_detune,0);

  if(mode == ASSIGN_MODE_POLY)
    gtk_widget_set_sensitive(voice_panel->combobox_trigger,0);
  else
    gtk_widget_set_sensitive(voice_panel->combobox_trigger,1);
}

void on_program_emitted(gpointer arg1,gpointer arg2,gpointer arg3) {
  SoundPanel *panel = (SoundPanel*) arg2;
  ProgMsg    *msg   = (ProgMsg*) arg3;

  sound_panel_set(panel,msg);
}

void sound_panel_cb_build(SoundPanel *panel) {
  int layer = 0;
  panel->cbHandlers.voice_changed = 
  g_signal_connect(panel->basics.combobox_voice,"changed",
                   (GCallback) on_voice_mode_changed,panel);

  panel->cbHandlers.layer_changed = 
  g_signal_connect(panel->basics.combobox_layering,"changed",
                   (GCallback) on_voice_mode_changed,panel);

  for(layer = 0; layer < 2; layer++) {
    g_signal_connect(panel->voice[layer].combobox_assign,"changed",
                     (GCallback) on_assign_mode_changed,
                     &panel->voice[layer]);
  }

  g_signal_connect(G_OBJECT(panel->libSignalHook),
                   "program-emitted",
                   (GCallback) on_program_emitted,0);
}



