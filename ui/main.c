#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include "sound_panel.h"

int main (int argc, char ** argv)
{
  GtkBuilder  *  builder   = NULL;
  GError      *  err       = NULL;
  SoundPanel  *  panel     = NULL;

  gdk_threads_init();

  gtk_init (& argc, & argv);

  builder = gtk_builder_new ();

  gtk_builder_add_from_file (builder, "ui.glade", & err);

  if(err != NULL) {
    g_error ("%s", err->message);
    g_error_free (err);
    return EXIT_FAILURE;
  }

  GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
      builder, "window1");

  panel = sound_panel_build(builder);

  gtk_builder_connect_signals(builder,panel);

  gtk_widget_show_all (p_win);
  gtk_main ();

  return EXIT_SUCCESS;
}

