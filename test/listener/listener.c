#include <stdio.h>
#include "ukorg.h"
#include "ProgMsg_internal.h"

void on_tick(void *user_data) {
  printf("Tick! user_data : %d", *((int*) user_data));
}

void on_prog_msg(const ProgMsg *msg,void *user_data) {
  printf("ProgMsg! user_data : %d\n", *((int*) user_data));
  printf("assign 1: %x, ", (unsigned char) msg->params.synths.timbre1.assignMode);
  printf("assign 2: %x\n", (unsigned int) msg->params.synths.timbre2.assignMode);
}

int main(int argc, char *argv[]) {

  int my_private_data = 12;

  struct ukorg_callbacks my_callbacks = {
    on_tick,
    on_prog_msg
  };

  ukorg_register_listener(&my_callbacks,&my_private_data);

  ukorg_start();

  getchar();

  return 0;
}

