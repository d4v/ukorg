#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include "sound_panel.h"

int main (int argc, char ** argv)
{
  GtkBuilder  *  mainBuilder   = NULL;
  GtkBuilder  *  voice1Builder = NULL;
  GtkBuilder  *  voice2Builder = NULL;

  GError      *  err   = NULL;
  SoundPanel  *  panel = NULL;

  gtk_init (& argc, & argv);

  mainBuilder   = gtk_builder_new ();
  voice1Builder = gtk_builder_new ();
  voice2Builder = gtk_builder_new ();

  gtk_builder_add_from_file (mainBuilder, "ui/ui.glade", & err);

  if(err != NULL) {
    g_error ("%s", err->message);
    g_error_free (err);
    return EXIT_FAILURE;
  }

  gtk_builder_add_from_file (voice1Builder, "ui/voice.glade", & err);

  if(err != NULL) {
    g_error ("%s", err->message);
    g_error_free (err);
    return EXIT_FAILURE;
  }

  gtk_builder_add_from_file (voice2Builder, "ui/voice.glade", & err);

  if(err != NULL) {
    g_error ("%s", err->message);
    g_error_free (err);
    return EXIT_FAILURE;
  }

  GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
      mainBuilder, "window1");

  panel = sound_panel_build(mainBuilder,voice1Builder,voice2Builder);

  gtk_builder_connect_signals(mainBuilder,panel);

  gtk_widget_show_all (p_win);
  gtk_main ();

  return EXIT_SUCCESS;
}

