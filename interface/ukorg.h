#ifndef UKORG_H
#define UKORG_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ProgMsg ProgMsg;

struct ukorg_callbacks {
  void (*on_tick)(void*);
  void (*on_prog_msg)(const ProgMsg*,void*);
};

typedef struct _ukorg_listener ukorg_listener;

ukorg_listener *ukorg_register_listener(struct ukorg_callbacks*,void *user_data);

void ukorg_start();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UKORG_H
