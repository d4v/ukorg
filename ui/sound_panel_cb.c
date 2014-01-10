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

void on_layering_changed(GtkComboBox *combobox,gpointer user_data) {
  SoundPanel *panel = (SoundPanel*) user_data;
  VoiceMode mode = VOICE_MODE_SINGLE;

  if(gtk_combo_box_get_active(combobox) == GTK_LAYER_DOUBLE)
    mode = VOICE_MODE_LAYER;

  basics_panel_set(panel,mode);
}

