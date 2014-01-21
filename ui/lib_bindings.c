#include <gtk/gtk.h>
#include "ukorg.h"
#include "sound_panel_internal.h"

enum {
  SIG_ONE_PROG,
  LAST_SIGNAL
};

static gint ukorg_signals[LAST_SIGNAL] = { 0 };



void build_signals() {
  ukorg_signals[SIG_ONE_PROG] =
    g_signal_new ("program-emitted", /* Signal name    */
                    G_TYPE_OBJECT,     /* Object type    */
                    G_SIGNAL_RUN_FIRST,     /* Signal flags   */
                    0,                 /* Class offset   */
                    0,                 /* Accumulator    */
                    0,                 /* Accu user data */
                    0,                 /* C Marshaller   */
                    G_TYPE_NONE,       /* Return value   */
                    0 );               /* Param number   */

}

void on_tick(void *user_data) {
}

void on_prog_msg(const ProgMsg *progMsg,void *user_data) {
  GtkWidget* hook = (GtkWidget*) user_data;
  g_signal_emit(hook,ukorg_signals[SIG_ONE_PROG],0);
}

static struct ukorg_callbacks cbs = {
  on_tick,
  on_prog_msg
};

void lib_bindings_build(SoundPanel *panel) {

  build_signals();

  ukorg_register_listener(&cbs,panel->libSignalHook);

  ukorg_start();
}

