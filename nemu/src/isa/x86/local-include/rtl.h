#ifndef __X86_RTL_H__
#define __X86_RTL_H__

#include <rtl/rtl.h>
#include "reg.h"

/* RTL pseudo instructions */

static inline def_rtl(lr, rtlreg_t* dest, int r, int width) {
  switch (width) {
    case 4: rtl_mv(s, dest, &reg_l(r)); return;
    case 1: rtl_host_lm(s, dest, &reg_b(r), 1); return;
    case 2: rtl_host_lm(s, dest, &reg_w(r), 2); return;
    default: assert(0);
  }
}

static inline def_rtl(sr, int r, const rtlreg_t* src1, int width) {
  switch (width) {
    case 4: rtl_mv(s, &reg_l(r), src1); return;
    case 1: rtl_host_sm(s, &reg_b(r), src1, 1); return;
    case 2: rtl_host_sm(s, &reg_w(r), src1, 2); return;
    default: assert(0);
  }
}

static inline def_rtl(push, const rtlreg_t* src1) {
  // esp <- esp - 4
  // M[esp] <- src1
    cpu.esp-=4;
    //rtl_zext(s,t0,*src1,s->width);
    rtl_sm (s,&cpu.esp, 0,src1,4);
}

static inline def_rtl(pop, rtlreg_t* dest) {
  // dest <- M[esp]
  // esp <- esp + 4
  rtl_lm(s,dest,&cpu.esp,0,4);
  cpu.esp+=4;
 // TODO();
}

static inline def_rtl(is_sub_overflow, rtlreg_t* dest,
    const rtlreg_t* res, const rtlreg_t* src1, const rtlreg_t* src2, int width) {
  // dest <- is_overflow(src1 - src2)
   rtl_msb(s,t1,src2,width);
   rtl_msb(s,t2,res,width);  
   rtl_msb(s,t0,src1,width);
    // printf("src1 :  %x  %x  src2: %x %x ans: %x  ans_bit : %d\n ",*t0,*src1,*t1,*src2,*dest,*t2);
   if(*t1==*t0) *dest=0;
   else {
      if(*t2!=*t0) *dest=1;
      else  *dest=0;
   }
 //TODO();
}

static inline def_rtl(is_sub_carry, rtlreg_t* dest,
    const rtlreg_t* src1, const rtlreg_t* src2) {
    //*t0=rtl_msb(s,dest,src1,)
    // printf("src1:  %x  src2: %x\n",*src1,*src2);
    if((*src1-*src2)>*src1) *dest=1;
    else *dest=0;
 // TODO();
}
//TODO();
static inline def_rtl(is_add_overflow, rtlreg_t* dest,
    const rtlreg_t* res, const rtlreg_t* src1, const rtlreg_t* src2, int width) {
  // dest <- is_overflow(src1 + src2)
   rtl_msb(s,t1,src2,width);
   rtl_msb(s,t2,res,width);
   rtl_msb(s,t0,src1,width);
   if(*t1!=*t0) *dest=0;
   else {
      if(*t2==*t0) *dest=0;
      else  *dest=1;
   }
  //TODO();
}

static inline def_rtl(is_add_carry, rtlreg_t* dest,
    const rtlreg_t* res, const rtlreg_t* src1) {
  // dest <- is_carry(src1 + src2) 
  if( *res>*src1+*res)  *dest=1;   
  else *dest=0;
 // TODO();
}

#define def_rtl_setget_eflags(f) \
  static inline def_rtl(concat(set_, f), const rtlreg_t* src) { \
   cpu.eflag.f=*src; \
  } \
  static inline def_rtl(concat(get_, f), rtlreg_t* dest) { \
    *dest=cpu.eflag.f; \
  }

def_rtl_setget_eflags(CF)
def_rtl_setget_eflags(OF)
def_rtl_setget_eflags(ZF)
def_rtl_setget_eflags(SF)

static inline def_rtl(update_ZF, const rtlreg_t* result, int width) {
  // eflags.ZF <- is_zero(result[width * 8 - 1 .. 0])
  if(*result == 0) cpu.eflag.ZF=1;
  else cpu.eflag.ZF=0;
 // TODO();
}

static inline def_rtl(update_SF, const rtlreg_t* result, int width) {
  // eflags.SF <- is_sign(result[width * 8 - 1 .. 0])
  rtl_msb(s,t1,result,width);
  // printf("msb:  %d\n",*t1);
  cpu.eflag.SF=*t1;
}

static inline def_rtl(update_ZFSF, const rtlreg_t* result, int width) {
  rtl_update_ZF(s, result, width);
  rtl_update_SF(s, result, width);
  //assert(0);
}

#endif
