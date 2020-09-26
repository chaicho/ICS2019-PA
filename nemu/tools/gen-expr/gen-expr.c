#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"#include <stdint.h>\n"
"#include <assert.h>\n"
"int main() { "
"  unsigned tmp= %s;"
//  unsigned tmp=(unsigned) result;"
//" if(result==tmp){"
"  printf(\"%%u\", tmp); "
//"  else assert(0);"
"  return 0; "
"}";
int ii,j,tmp,flag=0;
static inline void gen_num(){
     tmp=rand()%6+1;
     j=0;
     buf[ii++]=rand()%8+1+'0';
    for(j=1;j<=tmp;j++) {
      buf[ii++]=rand()%9+'0';
      }
}
static inline void gen_rand_expr() {
  if(ii>=500) {
    gen_num();
    return;
    }
  switch (rand()%3)
  {
  case 0:
    gen_num();
    break;
  case 1:
    buf[ii++]='(';
    gen_rand_expr();
    buf[ii++]=')';
    break;
  case 2:
    gen_rand_expr();
    tmp=rand()%4;
    switch (tmp)
    {
    case 0:
      buf[ii++]='-';
      break;
    case 1:
      buf[ii++]='+';
      break;
    case 2:
      buf[ii++]='/';
      break;
    case 3:
      buf[ii++]='*';
      break;
    }
    gen_rand_expr();

    break;
    
  }
  return;
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    ii=0; 
    memset(buf,0,65535);
     gen_rand_expr();
    flag=1;
    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);
    int ret = system("gcc /tmp/.code.c -Wall -Werror -o  /tmp/.expr");
    if (ret != 0)  {
      i--;
      continue;
    }
    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);
    int result;
    fscanf(fp, "%u", &result);
    pclose(fp);
    printf("%u %s\n", result, buf);
  }
  return 0;
}
 