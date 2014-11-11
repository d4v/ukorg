#include <fcntl.h>
#include <stdio.h>
#include "sound_panel_internal.h"
#include "sound_panel_cb.h"
#include "basics_panel.h"
#include "voice_panel.h"
#include "osc1_panel.h"
#include "lfo_panel.h"

void cb_show_open_dialog(GtkWidget * p_wid, gpointer p_data) {
  GtkWidget  *dialog;
  SoundPanel *panel = (SoundPanel*) p_data;

  dialog = gtk_file_chooser_dialog_new (
      "Open File",
      NULL,
      GTK_FILE_CHOOSER_ACTION_OPEN,
      "_Cancel", GTK_RESPONSE_CANCEL,
      "_Open", GTK_RESPONSE_ACCEPT,
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

void on_program_emitted(gpointer arg1,gpointer arg2,gpointer arg3) {
  SoundPanel *panel = (SoundPanel*) arg2;
  ProgMsg    *msg   = (ProgMsg*) arg3;

  sound_panel_set(panel,msg);
}

void sound_panel_cb_build(SoundPanel *panel) {
  int layer = 0;

  basics_panel_cb_build(panel->basics);

  for(layer = 0; layer < 2; layer++) {
    voice_panel_cb_build(panel->voice[layer]);
    osc1_panel_cb_build(panel->osc1[layer]);
    lfo_panel_cb_build(panel->lfo[layer]);
  }

  g_signal_connect(G_OBJECT(panel->libSignalHook),
                   "program-emitted",
                   (GCallback) on_program_emitted,0);
}



