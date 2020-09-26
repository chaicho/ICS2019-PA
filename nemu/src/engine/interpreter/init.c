void ui_mainloop();
void init_device();
#include<stdio.h>
void engine_start() {
  /* Initialize devices. */
  init_device();
  FILE *fp = fopen("/home/chaicho/ics2020/nemu/tools/gen-expr/input", "r");
  char str[50];
  while(fgets(str,40,fp)!=NULL){ 
    puts(str);
  }
  /* Receive commands from user. */
  ui_mainloop();

}
