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
  //cpu.eflag=0x2;
/* FILE *fp = fopen("/home/chaicho/ics2020/nemu/tools/gen-expr/input", "r");
  int result=0;
  char str[50];
  while( fscanf(fp, "%u %s", &result,str)!=-1){
       //   printf("%s\n",str);

   bool success=true;
   unsigned x=expr(str,&success);
   // printf("%u\n",expr(args,&success));
   if(x==result) {
     printf("%s\n",str);
     printf("You are right! The answer is %u\n",x);
   }
   else {
     printf("%s\n",str);
     printf("Right:%u,Wrong:%u \n",result,x);
  
   }
    memset(str,0,49);
  }*/
  return is_exit_status_bad();
}
