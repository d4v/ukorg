#ifndef SOUNDS_TREE_VIEW_H
#define SOUNDS_TREE_VIEW_H

#include <gtk/gtk.h>

void sounds_tree_view_build(GtkBuilder *builder);

void sounds_tree_view_set_dir(const char *dirname);

#endif // SOUNDS_TREE_VIEW_H
