#include <stdio.h>
#include "ukorg.h"

void on_tick(void *user_data) {
  printf("Tick! user_data : %d", *((int*) user_data));
}

void on_prog_msg(const ProgMsg *msg,void *user_data) {
  fprintf(stderr,"ProgMsg! user_data : %d", *((int*) user_data));
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

