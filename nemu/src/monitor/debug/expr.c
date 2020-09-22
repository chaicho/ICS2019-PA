#include <isa.h>
#include <stdlib.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ, TK_PLUS,TK_MINUS,TK_MULT,TK_DIV,TK_LEFTBRA,TK_RIGHTBRA,TK_NUM,

  /* TODO: Add more token types */

};

static struct rule {
  char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention  to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", TK_PLUS},         // plus
  {"==", TK_EQ},        // equal
  {"\\-",TK_MINUS},
  {"\\*",TK_MULT},
  {"\\/",TK_DIV}, 
  {"\\(",TK_LEFTBRA},
  {"\\)",TK_RIGHTBRA},
  {"[0-9]+",TK_NUM},

};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX;  i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);//re[i]存放编译后的正则表达式
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {}; //存放正则表达式
static int nr_token __attribute__((used))  = 0; //正则表达式的的数量

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;
  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {

      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;
     //   printf("%s\n",rules[i].regex);
       /* Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
           i, rules[i].regex, position, substr_len, substr_len, substr_start);
        */
        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        
        switch (rules[i].token_type) {
          case 256:     //空格
              break;
          
          case 257:     //等于
              tokens[nr_token].type=257;
              strcpy(tokens[nr_token++].str,"==");
              break;
           case 258:     //加号
              tokens[nr_token++].type=258;
              break;
          case 259:     //减
              tokens[nr_token++].type=259;
              break;
          case 260:     //乘
              tokens[nr_token++].type=260;
              break;
          case 261:  //除法
              tokens[nr_token++].type=261;
          case 262:     //左括号
              tokens[nr_token++].type=262;
              break;
          case 263:     //右括号
              tokens[nr_token++].type=263;
              break;
          case 264:     //数字
              tokens[nr_token].type=264;
              strncpy(tokens[nr_token++].str,substr_start,substr_len);
              assert(substr_len<=31);
              break;
          
          default:
              printf("Illegal\n");
              break;
        }
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}
bool check_brackets(int p,int q){
        if(tokens[p].type!=TK_LEFTBRA&&tokens[q].type!=TK_RIGHTBRA) return false;
        int credit=0;
        int j=0;
        for( j=p;j<=q;j++){
          if(tokens[j].type==TK_LEFTBRA) credit++;
          else if(tokens[j].type==TK_RIGHTBRA) {
            if(credit<=0) return false;
            else credit--;
        }}
        return credit==0;
}
int eval(int p,int q){
    int loc=0;
    if(p>q){
      return -1;  
    }
    else if(p==q) {
      if(tokens[p].type==TK_NUM)
      return atoi(tokens[p].str);
      
      else return 0;        
    } 
    else if(check_brackets(p,q)){
        return eval(p+1,q-1);
    }
    else{
      int i=0,lef=0; //用loc来记录,lef记录是否在括号中
      for(i=p;i<=q;i++){
          if(tokens[i].type==TK_LEFTBRA){
            lef++;
          }
          else if(tokens[i].type==TK_RIGHTBRA)
          {
              lef--;
          }
          else if(lef==0&&tokens[i].type<TK_LEFTBRA&&tokens[i].type>TK_EQ){
              if(tokens[i].type<=TK_MINUS||tokens[i].type<tokens[loc].type){
                loc=i;
                printf("Loc=%d\n",loc);
              }
          }
      }
      int val1=eval(p,loc-1);
      int val2=eval(loc+1,q);
      switch (tokens[loc].type)
      {
      case TK_PLUS:
        return val1+val2;
        break;
      case  TK_MINUS:
        return val1-val2;
        break;
      case TK_MULT:
        return val1*val2;
        break;
      case TK_DIV:
        return val1/val2;
        break;
      default:
        return 0;
        break;
      }
    }    
}
word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  
  /* TODO: Insert codes to evaluate the expression. */
  printf("%d\n",nr_token);
  return eval(0,nr_token-1);
}
