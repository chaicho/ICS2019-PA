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
  char str[32];//32
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
    //  if(e[position]=='\n') break;
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
              break;
          case 262:     //左括号
              tokens[nr_token++].type=262;
              break;
          case 263:     //右括号
              tokens[nr_token++].type=263;
              break;
          case 264:     //数字
              tokens[nr_token].type=264;
              strncpy(tokens[nr_token++].str,substr_start,substr_len);
              // assert(substr_len<=31);
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
        int credit=0;
        int j=0;
       
        for( j=p;j<=q;j++){
          if(tokens[j].type==TK_LEFTBRA) {
            credit++;
          }
          else if(tokens[j].type==TK_RIGHTBRA) {
            if(credit<=0) return false;
            else credit--;
        }}
        //printf("brackets: p=%d,q=%d,....%d\n",p,q,credit);
        return credit==0;
}
int eval(int p,int q){
    int a[33]={0};
    int gg=0;
    bool selected=false; //是否有优先级高的一个选的
   // printf("p=%d,q=%d\n",p,q);
    if(p>q){
      return 0;  
    }
    else if(p==q) {
      if(tokens[p].type==TK_NUM) return atoi(tokens[p].str);
      else return 0;        
    } 
    else if(tokens[p].type==TK_LEFTBRA&&tokens[q].type==TK_RIGHTBRA&&check_brackets(p+1,q-1))return eval(p+1,q-1);
    else if(check_brackets(p,q)){
          int i=0,lef=0; //用a按可行性记录符号,lef记录是否在括号中
      for(i=p;i<=q;i++){
       // printf("%d\n",tokens[i].type);
          if(tokens[i].type==TK_LEFTBRA){
            lef++;
          }
          else if(tokens[i].type==TK_RIGHTBRA)
          {
              lef--;
          }
          else if(lef==0&&tokens[i].type<TK_LEFTBRA&&tokens[i].type>TK_EQ){
           // printf("%d\n",gg);
              if(tokens[i].type<=TK_MINUS){  ///如果以后出了问题记得看这边
                selected=true;
                a[gg++]=i;
             //   printf("%d\n",a[gg]);
              }
              else if(!selected&&tokens[i].type<=TK_DIV){
                a[gg++]=i;
                }
          }
         // printf("%d\n",lef);
      }
      gg--;
      int positive=1;
      int record=a[gg];
     
      while(gg>0&&tokens[a[gg]].type==TK_MINUS){
          if(a[gg]==p) break;
          if(tokens[a[gg]-1].type!=TK_NUM&&tokens[a[gg]-1].type!=TK_RIGHTBRA){
           gg--;
           positive=-positive;
           printf("%d options remained\n",gg);
         }
         else break;
      }
        printf("the first valid op is %d\n",a[gg]);
      if(a[gg]==p) return (-positive)*eval(record+1,q);
      int val1=eval(p,a[gg]-1);
    
      int val2=positive*eval(record+1,q); 
      printf("val1=%d,val2=%d\n",val1,val2);
      switch (tokens[a[gg]].type)
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
  else{
    assert(0);
    return 0;
  }    
}
word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  
  /* TODO: Insert codes to evaluate the expression. */
 // printf("%d\n",nr_token);
  return eval(0,nr_token-1);
}
