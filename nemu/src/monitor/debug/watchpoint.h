#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include <common.h>

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  uint32_t pre_val;
  char str[32];
} WP;
WP* new_wp();
void init_wp_pool() ;
void free_wp(WP *wp);
void insert_wp(char * a);
void check_wp();
void print_wp();
void delete_wp(int no);

#endif
