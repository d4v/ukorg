#ifndef UI_UTIL_H
#define UI_UTIL_H

#include <gtk/gtk.h>

static inline
void set_combo_box_value(GtkWidget *combobox,int value) {
  if(gtk_combo_box_get_active(GTK_COMBO_BOX(combobox)) != value)
    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox),value);
}

#define GET_GTK_OBJECT(object,type,builder,name) \
  object = (type *)  gtk_builder_get_object(builder,name)

#endif // UI_UTIL_H
