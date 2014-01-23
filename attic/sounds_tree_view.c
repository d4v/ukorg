#include <dirent.h>
#include <string.h>
#include <errno.h>

#include "sounds_tree_view.h"

GtkWidget * sounds_tree_view  = 0;
GtkWidget * sounds_list_store = 0;

enum {
  COL_SND_NAME,
  COL_SND_FILE,
  NB_COL,
};

void sounds_tree_view_build(GtkBuilder *builder) {
  GtkCellRenderer *renderer;
  
  sounds_tree_view = GTK_WIDGET(
      gtk_builder_get_object (builder, "sounds_tree_view"));

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (
      GTK_TREE_VIEW(sounds_tree_view),
      -1,
      "Sound name",
      renderer,
      "text", COL_SND_NAME,
      NULL);

  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (
      GTK_TREE_VIEW(sounds_tree_view),
      -1,
      "File",
      renderer,
      "text", COL_SND_FILE,
      NULL);

  sounds_list_store = GTK_WIDGET(
    gtk_list_store_new(NB_COL,G_TYPE_STRING,G_TYPE_STRING));

  gtk_tree_view_set_model(
    GTK_TREE_VIEW(sounds_tree_view),
    GTK_TREE_MODEL(sounds_list_store));

}

void sounds_tree_view_set_dir(const char *dirname) {

  DIR * d;

  /* Open the current directory. */

  d = opendir (dirname);

  if (! d) {
      fprintf (stderr, "Cannot open directory '%s': %s\n",
               dirname, strerror (errno));
      return;
  }
  while (1) {
      struct dirent * entry;
      
      entry = readdir (d);
      if (! entry) {
          break;
      }
      printf ("%s\n", entry->d_name);
  }
  /* Close the directory. */
  if (closedir (d)) {
      fprintf (stderr, "Could not close '%s': %s\n",
               dirname, strerror (errno));
      return;
  }

  return 0;
}

  
  
