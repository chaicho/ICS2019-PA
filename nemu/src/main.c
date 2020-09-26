void init_monitor(int, char *[]);
void engine_start();
int is_exit_status_bad();
#include<stdio.h>
int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
  init_monitor(argc, argv);

  /* Start engine. */
  engine_start();
  FILE *fp = fopen("/home/chaicho/ics2020/nemu/tools/gen-expr/input", "r");
  char str[50];
  if(fgets(str,40,fp)!=NULL){ 
  puts(str);
  }
  return is_exit_status_bad();
}
