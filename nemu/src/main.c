void init_monitor(int, char *[]);
void engine_start();
int is_exit_status_bad();
#include<stdio.h>
int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
  init_monitor(argc, argv);
  FILE *fp = fopen("/home/chaicho/ics2020/nemu/tools/gen-expr/input", "r");
  char str[50];
  while(fgets(str,40,fp)!=NULL){ 
  puts(str);
  }
  /* Start engine. */
  engine_start();
 
  return is_exit_status_bad();
}
