#include <isa.h>
#include <stdlib.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
enum {
  TK_NOTYPE, TK_EQ, TK_PLUS,TK_MINUS,TK_MULT,TK_DIV,TK_LEFTBRA,TK_RIGHTBRA,TK_NUM,TK_HEX,TK_DE,TK_AND,TK_OR,TK_NEQ,TK_REG,TK_NEG,

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
  {"0[xX][a-f0-9]+",TK_HEX},
  {"[0-9]+",TK_NUM},
  {"&&",TK_AND},
  {"\\|\\|",TK_OR},
  {"!=",TK_NEQ},
  {"\\$[Ee]?[A-Da-d][xX]}|\\$[A-Da-d][xXlL]|\\$[Ee]?[si|SI|di|DI|SP|sp|BP|bp]",TK_REG},
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
 bool address=false;
 int lowest=-1;// 用来记录当前优先级最低的符号
static int priority[32]={0,7,4,4,3,3,1,1,1000,1000,2,11,12,7,2};
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
          case TK_NOTYPE:     //空格
              break;
          
          case TK_EQ:     //等于
              tokens[nr_token].type=TK_EQ;
             // strcpy(tokens[nr_token++].str,"==");
              break;
           case TK_PLUS:     //加号
              tokens[nr_token++].type=TK_PLUS;
              break;
          case TK_MINUS:     //减
              tokens[nr_token++].type=TK_MINUS;
              break;
          case TK_MULT:     //乘
              tokens[nr_token++].type=TK_MULT;
              break;
          case TK_DIV:  //除法
              tokens[nr_token++].type=TK_DIV;
              break;
          case TK_LEFTBRA:     //左括号
              tokens[nr_token++].type=TK_LEFTBRA;
              break;
          case TK_RIGHTBRA:     //右括号
              tokens[nr_token++].type=TK_RIGHTBRA;
              break;
          case TK_REG:
              tokens[nr_token].type=TK_REG;
               strncpy(tokens[nr_token++].str,substr_start,substr_len);
               assert(substr_len<=31);
               break;
          case TK_HEX:
              tokens[nr_token].type=TK_HEX;
               strncpy(tokens[nr_token++].str,substr_start,substr_len);
               assert(substr_len<=31);
               break;
          case TK_NUM:     //数字
              tokens[nr_token].type=TK_NUM;
              strncpy(tokens[nr_token++].str,substr_start,substr_len);
               assert(substr_len<=31);
              break;
          case TK_AND:
              tokens[nr_token++].type=TK_AND;
              break;
          case TK_OR:
              tokens[nr_token++].type=TK_OR;
              break;
          case TK_NEQ:
              tokens[nr_token++].type=TK_NEQ;
              break;
          default:
              printf("Illegal\n");
              break;
        }
        break;
      }
    }
   // if(e[position]=='\n') return true;
    if (i == NR_REGEX) {
      //printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      //if(e[position]=='\n') return true;
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
unsigned eval(int p,int q){
    //int a[33]={0};
    int record=p;
    //int gg=0;
    //bool selected=false; //是否有优先级高的一个选的
   // printf("p=%d,q=%d\n",p,q);
    if(p>q){
      return 0;  
    }
    else if(p==q) {
      if(tokens[p].type==TK_NUM) return atoi(tokens[p].str);
      else if(tokens[p].type==TK_HEX){

      }
      else if(tokens[p].type==TK_REG)
      {
      }
      
      else return 0;        
    } 
    else if(tokens[p].type==TK_LEFTBRA&&tokens[q].type==TK_RIGHTBRA&&check_brackets(p+1,q-1))return eval(p+1,q-1);
    else if(check_brackets(p,q)){
          int i=0,lef=0; //lef记录是否在括号中
      for(i=p;i<=q;i++){
        lef=0;
       // printf("%d\n",tokens[i].type);
          if(tokens[i].type==TK_LEFTBRA){
            lef++;
          }
          else if(tokens[i].type==TK_RIGHTBRA)
          {
              lef--;
          }
          else if(lef==0){
           // printf("%d\n",gg);
               if(priority[tokens[i].type]>=lowest){
                 record=i;
                 lowest=priority[tokens[i].type];
               }
          }
         // printf("%d\n",lef);
      }
     /* gg--;
      int positive=1;
      int record=a[gg];
      while(gg>0&&tokens[a[gg]].type==TK_MINUS){
          if(a[gg]==p) break;
          if(tokens[a[gg]-1].type!=TK_NUM&&tokens[a[gg]-1].type!=TK_RIGHTBRA){
           gg--;
           positive=-positive;
        //   printf("%d options remained\n",gg);
         }
         else break;
      
       // printf("the first valid op is %d\n",a[gg]);
      if(a[gg]==p) return (-positive)*eval(record+1,q);*/
      int val1=eval(p,record-1);
      int val2=eval(record+1,q); 
   //   printf("val1=%d,val2=%d\n",val1,val2);
      switch (tokens[record].type)
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
      case TK_EQ:
        return val1==val2;
        break;
      case TK_NEQ:
        return val1!=val2;
        break;
      case TK_NEG:
        return -val2;
        break;
      case TK_OR:
        return val1||val2;
        break;
      case TK_AND:
        return val1&&val2;
        break;
      case TK_DE:
        address=true;
        return val2;
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
   return 0;
}
word_t expr(char *e, bool *success) {
  memset(tokens,0,32*sizeof(Token));
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  int w=0;
  for (w = 0; w < nr_token; w ++) {
     if (tokens[w].type == TK_MULT && (w == 0 || (tokens[w- 1].type!=TK_RIGHTBRA&&tokens[w-1].type!=TK_NUM&&tokens[w-1].type!=TK_HEX) ) ) {
      tokens[w].type = TK_DE;
    }}
  for (w = 0; w < nr_token; w ++) {
     if (tokens[w].type == TK_MINUS && (w == 0 || (tokens[w- 1].type!=TK_RIGHTBRA&&tokens[w-1].type!=TK_NUM&& tokens[w-1].type!=TK_HEX) ) ){
      tokens[w].type = TK_NEG;
    }
}
   lowest=-1;// 用来记录当前优先级最低的符号
  /* TODO: Insert codes to evaluate the expression. */
 // printf("%d\n",nr_token);
  return eval(0,nr_token-1);
}
