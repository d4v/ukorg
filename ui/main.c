#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "ProgMsg.h"
#include "sound_panel.h"

void cb_show_open_dialog(GtkWidget * p_wid, gpointer p_data) {
  GtkWidget *dialog;

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
    static const bufSize = sizeof(ProgMsg);
    char buf[bufSize];

    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
    int fd = open(filename,O_RDONLY);

    read(fd,buf,bufSize);

    sound_panel_set((ProgMsg*) &buf);

    puts(filename);
    g_free (filename);
  }
  gtk_widget_destroy (dialog);

}

int main (int argc, char ** argv)
{
  GtkBuilder  *  p_builder   = NULL;
  GError      *  p_err       = NULL;
  GtkTreeIter  iter;
  GtkCellRenderer * renderer;

  gtk_init (& argc, & argv);

  p_builder = gtk_builder_new ();

  gtk_builder_add_from_file (p_builder, "ui.glade", & p_err);

  if(p_err != NULL) {
    g_error ("%s", p_err->message);
    g_error_free (p_err);
    return EXIT_FAILURE;
  }

  GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
      p_builder, "window1");

  sound_panel_build(p_builder);

  gtk_builder_connect_signals(p_builder,NULL);

  gtk_widget_show_all (p_win);
  gtk_main ();

  return EXIT_SUCCESS;
}

