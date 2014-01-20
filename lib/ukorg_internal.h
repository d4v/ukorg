#ifndef UKORG_INTERNAL_H
#define UKORG_INTERNAL_H

#include <vector>
#include "ukorg.h"

typedef struct _ukorg_listener {
  struct ukorg_callbacks *callbacks;
  void *user_data;
} ukorg_listener;

const std::vector<ukorg_listener*> &ukorg_get_listeners();

#endif // UKORG_INTERNAL_H
