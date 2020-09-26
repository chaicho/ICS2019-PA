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
   char *args=strtok(str," ");
   bool success=true;
   int x=expr(args,&success);
   printf("%d\n",expr(args,&success));
   printf("%s\n",args);
   if(x==atoi(args)) {
     printf("%s\n",args);
     printf("You are right!\n");
   }
   else {
     printf("%s\n",args);
     printf("Right:%u,Wrong:%u \n",atoi(cmd),x);
   }
    memset(str,'\n',50);
  }
  return is_exit_status_bad();
}
