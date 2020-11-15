#include <isa.h>
#include "expr.h"
#include "watchpoint.h"
#include <memory/paddr.h>
#include <memory/vaddr.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "watchpoint.h"
#include <monitor/monitor.h>
void cpu_exec(uint64_t);
int is_batch_mode();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);

  return 0;
}


static int cmd_q(char *args) {
  nemu_state.state=NEMU_QUIT;
  return -1;
}


static int cmd_help(char *args);
static int cmd_si(char *args);
static int cmd_info(char *args);
static int cmd_x(char *args);
static int cmd_p (char *args);
static int cmd_w(char *args);
static int cmd_d(char *args);
static struct {
  char *name;
  char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "Let the program step through N instructions and then suspend execution. When N is not given, the default value is 1",cmd_si},
  {"info"," Print register status or Print monitoring point information",cmd_info},
  { "p"," Calculate the value of the expression EXPR. For the operations supported by EXPR, see the section on expression evaluation in debugging",cmd_p},
  {"x","Find the value of the expression EXPR, use the result as the starting memory address, and output consecutive N 4 bytes in hexadecimal form",cmd_x},
  {"w", "When the value of the expression EXPR changes, the program execution is suspended",cmd_w},
  {"d","Delete the monitoring point with sequence number N",cmd_d},
  /* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))


static int cmd_si(char *args){
  char *arg =  strtok(NULL, " "); //这个地方从刚才的下一个开始
  if(arg==NULL) cpu_exec(1);
  else{
    int i=0;
    sscanf(arg,"%d",&i);
    if(i<0) printf("Wrong Arguments\n");  
    else if(i==0) printf("Do nothing\n");
    else {
    cpu_exec(i);

    }
  }
  return 0;
}
static int cmd_info(char  *args){
  char *arg =strtok(NULL,"");
  if(*arg=='r'){
    isa_reg_display();

  }
  else if(*arg=='w')  //打印监视点
  {
     print_wp();
  }
  return 0;
}
static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}
static int cmd_w(char *args){
   insert_wp(args);
   return 0;
}
static int cmd_d(char *args){
  int number;
  sscanf(args,"%d",&number);
  delete_wp(number);
  return 0;
}
static int cmd_x(char *args){
   char *arg = strtok(NULL, " "); 
   if(arg==NULL) printf ("More arguments needed\n");
   int number, address=1;
   bool success=true;
   int i=0;
   sscanf(arg, "%d", &number);
   arg = strtok(NULL, " ");
   address=expr(arg,&success);
    if(!success) printf("Mission failed\n");
   for( i=0;i<number;i++){
      printf("%8x :  %8x\n",address+4*i,vaddr_read(address+4*i, 4));
   } 
  return 0;
}
static int cmd_p (char *args){
    bool success=true;
    if(args==NULL) printf("More arguments needed\n");
    else{
           unsigned t=expr(args,&success);
           if(!success) printf("Mission failed\n");
           else printf("%x\n",t);
         }
     
    return 0; 
}
void ui_mainloop() {
  if (is_batch_mode()) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    
    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef HAS_IOE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
  return;
}
