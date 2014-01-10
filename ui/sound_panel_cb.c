#include <fcntl.h>
#include <stdio.h>
#include "sound_panel_internal.h"
#include "sound_panel_cb.h"
#include "sound_panel.h"

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
    static const size_t bufSize = sizeof(ProgMsg);
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

void on_voice_mode_changed(GtkComboBox *combobox,gpointer user_data) {
  SoundPanel *panel = (SoundPanel*) user_data;
  VoiceMode mode = VOICE_MODE_SINGLE;

  g_signal_handler_block(
      panel->basics.combobox_voice,panel->cbHandlers.voice_changed);
  g_signal_handler_block(
      panel->basics.combobox_layer,panel->cbHandlers.layer_changed);

  if(gtk_combo_box_get_active(GTK_COMBO_BOX(panel->basics.combobox_voice)) == GTK_VOICE_VOCODER)
    mode = VOICE_MODE_VOCODER;
  else if(gtk_combo_box_get_active(GTK_COMBO_BOX(panel->basics.combobox_layer)) == GTK_LAYER_DOUBLE)
    mode = VOICE_MODE_LAYER;

  basics_panel_set(panel,mode);

  g_signal_handler_unblock(
      panel->basics.combobox_voice,panel->cbHandlers.voice_changed);
  g_signal_handler_unblock(
      panel->basics.combobox_layer,panel->cbHandlers.layer_changed);
}

void sound_panel_set_cb(SoundPanel *panel) {
  panel->cbHandlers.voice_changed = 
  g_signal_connect(panel->basics.combobox_voice,"changed",
                   (GCallback) on_voice_mode_changed,panel);

  panel->cbHandlers.layer_changed = 
  g_signal_connect(panel->basics.combobox_layer,"changed",
                   (GCallback) on_voice_mode_changed,panel);
}


