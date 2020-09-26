void init_monitor(int, char *[]);
void engine_start();
int is_exit_status_bad();
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"monitor/debug/expr.h"
int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
  init_monitor(argc, argv);

  /* Start engine. */
  engine_start();
  FILE *fp = fopen("/home/chaicho/ics2020/nemu/tools/gen-expr/input", "r");
  char str[50];
  while(fgets(str,40,fp)!=NULL){ 
     char *cmd = strtok(str, " ");
    if (cmd == NULL) { 
      continue; 
    }
   char *args = cmd + strlen(cmd) + 1;
   bool success=true;
   unsigned x=expr(args,&success);
   if(x==(unsigned)atoi(cmd)) printf("You are right!\n");
   else printf("Right:%u,Wrong:%u\n",atoi(cmd),x);
  }
  return is_exit_status_bad();
}
