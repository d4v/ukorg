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
                  G_SIGNAL_RUN_FIRST,/* Signal flags   */
                  0,                 /* Class offset   */
                  0,                 /* Accumulator    */
                  0,                 /* Accu user data */
                  0,                 /* C Marshaller   */
                  G_TYPE_NONE,       /* Return value   */
                  3,                 /* Param number   */
                  G_TYPE_POINTER,    /* arg1 : signal hook */
                  G_TYPE_POINTER,    /* arg2 : SoundPanel  */
                  G_TYPE_POINTER);   /* arg3 : progMsg     */
}

void on_tick(void *user_data) {
}

void on_prog_msg(const ProgMsg *progMsg,void *user_data) {
  SoundPanel *panel = (SoundPanel*) user_data;
  int ret = 0;

  gdk_threads_enter();

  g_signal_emit(panel->libSignalHook,
                ukorg_signals[SIG_ONE_PROG],
                0,
                (gpointer) panel,
                (gpointer) progMsg,
                &ret);
 
  gdk_threads_leave();
}

static struct ukorg_callbacks cbs = {
  on_tick,
  on_prog_msg
};

void lib_bindings_build(SoundPanel *panel) {

  build_signals();

  ukorg_register_listener(&cbs,panel);

  ukorg_start();
}

