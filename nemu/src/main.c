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
  int result=0;
  char str[50];
  while( fscanf(fp, "%u %s", &result,str)){
     char *cmd = strtok(str, " ");
          printf("%s\n",str);

    if (cmd == NULL) { 
      continue; 
    }
   char *args=cmd+strlen(cmd)+1;
   bool success=true;
   unsigned x=expr(args,&success);
   // printf("%u\n",expr(args,&success));
   if(x==(unsigned) result) {
    // printf("%s\n",args);
     printf("You are right!\n");
   }
   else {
    //printf("%s\n",args);
     printf("Right:%u,Wrong:%u \n",result,x);
   }
    memset(str,0,49);
  }
  return is_exit_status_bad();
}
