#include <stdlib.h>
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

typedef struct {
    SoundPanel *panel;
    ProgMsg    *progMsg;
} ProgMsgIdleArgs;

gboolean on_prog_msg_idle(gpointer user_data) {
  ProgMsgIdleArgs *args = (ProgMsgIdleArgs*) user_data;
  int ret = 0;

  g_signal_emit(args->panel->libSignalHook,
                ukorg_signals[SIG_ONE_PROG],
                0,
                (gpointer) args->panel,
                (gpointer) args->progMsg,
                &ret);

  free(args);

  //! This is a one shot idle function
  return FALSE;
}

void on_prog_msg(const ProgMsg *progMsg,void *user_data) {
  SoundPanel *panel = (SoundPanel*) user_data;
  ProgMsgIdleArgs *args = (ProgMsgIdleArgs*) malloc(sizeof(ProgMsgIdleArgs));
  args->panel   = panel;
  args->progMsg = (ProgMsg *) progMsg;

  g_idle_add(on_prog_msg_idle,args);
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

