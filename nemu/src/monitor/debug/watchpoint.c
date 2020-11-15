#include "watchpoint.h"
#include "expr.h"
//#include <isa.h>
#include <monitor/monitor.h>
//#include <monitor/difftest.h>
//#include <stdlib.h>
//#include <sys/time.h>

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
int size=0;
void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}
WP* new_wp(){
    if(free_==NULL){
      printf("No free watchpoints\n");
      assert(0);
    }  
    WP *tmp=free_;
    free_=free_->next;
    tmp->next=NULL;
    return tmp;
}
void free_wp(WP *wp){
     if(head==NULL||wp==NULL){
       printf("Nothing to free\n");
       assert(0);
     }
     else if(wp==head){
        head=head->next;
        printf("Free watchpoint %d : %s \n",wp->NO,wp->str);
        wp->pre_val=0;
        memset(wp->str,0,32);
        wp->next=free_;
        free_=wp;
     }
     else{
        WP *tmp=head;
        while(tmp!=NULL){
            if(tmp->next==wp){
              tmp->next=wp->next;
              wp->next=free_;
              wp->pre_val=0;
             memset(wp->str,0,32);
              free_=wp;
              break;
            }
            tmp=tmp->next;
        }
     }
}
void insert_wp(char * a){
    WP *now=new_wp();
    strcpy(now->str,a);
    bool success=true;
    now->pre_val=expr(a,&success);
    if(!success){
    printf("Invalid watchpoint");
    free_wp(now);
    }
    now->next=head;
    head=now; 
    return;
}
void check_wp(){
  bool change=false;
  WP *tmp=head;
  while (tmp!=NULL)
  {
    bool success;
    uint32_t new=expr(tmp->str,&success);
     //assert(success);
    if(tmp->pre_val!=new){
      printf("Watchpoint %d: %s change from %x to %x\n",tmp->NO,tmp->str,tmp->pre_val,new);
      change=true;
      tmp->pre_val=new;
    }
    tmp=tmp->next;
  } 
  if(change) {
    nemu_state.state=NEMU_STOP;
    }
  return;
}
void print_wp(){
  WP *tmp=head;
  while (tmp!=NULL)
  {
  printf("Watchpoint %d: %s with value %u \n",tmp->NO,tmp->str,tmp->pre_val);
  tmp=tmp->next;
  }
  return;
}
void delete_wp(int no){
    WP *tmp=head;
    while (tmp!=NULL)
    {
      if(tmp->NO==no) break;
      else tmp=tmp->next;
    }
    free_wp(tmp);
    return;
}

/* TODO: Implement the functionality of watchpoint */

