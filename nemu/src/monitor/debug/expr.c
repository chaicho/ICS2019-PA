#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_PLUS,TK_EQ, TK_MINUS,TK_MULT,TK_LEFTBRA,TK_RIGHTBRA,TK_NUM

  /* TODO: Add more token types */

};

static struct rule {
  char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", TK_PLUS},         // plus
  {"==", TK_EQ},        // equal
  {"\\-",TK_MINUS},
  {"\\*",TK_MULT},
  {"\\(",TK_LEFTBRA},
  {"\\)",TK_RIGHTBRA},
  {"[0~9]+",TK_NUM},

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

  for (i = 0; i < NR_REGEX; i ++) {
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

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        
        switch (rules[i].token_type) {
          case 256:     //空格
              break;
          case 257:     //加号
              tokens[nr_token].type=257;
              break;
          case 258:     //等于
              tokens[nr_token].type=258;
              strcpy(tokens[nr_token++].str,"==");
              break;
          case 259:     //减
              tokens[nr_token++].type=259;
              break;
          case 260:     //乘
              tokens[nr_token++].type=260;
              break;
          case 261:     //左括号
              tokens[nr_token++].type=261;
              break;
          case 262:     //右括号
              tokens[nr_token++].type=262;
              break;
          case 263:     //数字
              tokens[nr_token].type=263;
              strncpy(tokens[nr_token++].str,substr_start,substr_len);
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


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  TODO();

  return 0;
}
