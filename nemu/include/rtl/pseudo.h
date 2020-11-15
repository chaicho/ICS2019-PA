#ifndef __RTL_PSEUDO_H__
#define __RTL_PSEUDO_H__

#ifndef __RTL_RTL_H__
#error "Should be only included by <rtl/rtl.h>"
#endif

/* RTL pseudo instructions */

static inline def_rtl(li, rtlreg_t* dest, const rtlreg_t imm) {
  *dest=imm;
}

static inline def_rtl(mv, rtlreg_t* dest, const rtlreg_t *src1) {
  *dest=*src1;
}

static inline def_rtl(not, rtlreg_t *dest, const rtlreg_t* src1) {
  // dest <- ~src1
  *dest=~(*src1);
  //TODO();
}

static inline def_rtl(neg, rtlreg_t *dest, const rtlreg_t* src1) {
  // dest <- -src1
  *dest=~(*src1)+1;
  //rtl_sub(s,dest,rz,src1);
  //TODO();
}

static inline def_rtl(sext, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- signext(src1[(width * 8 - 1) .. 0])
//  rtl_shli(s,t0,src1,8*(width-id_src1->width));
  rtl_shli(s,t0,src1,32-8*(width));
  //assert(0);q
//  printf("from :%x\n",*t0);
  rtl_sari(s,dest,t0,32-8*width);
 // operand_write(s,id_dest,t0);
 // printf("to: %x\n",*dest);
 // rtl_sari(s,t0,t0,8*(width-id_src1->width));
  //TODO();
  //operand_write(s,id_dest,src1);
}

static inline def_rtl(zext, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- zeroext(src1[(width * 8 - 1) .. 0])
 rtl_shli(s,t0,src1,8*(32-8*width));
 rtl_shri(s,dest,t0,8*(32-8*width));
  //TODO();
}

static inline def_rtl(msb, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- src1[width * 8 - 1]
  *t0=(*src1>>((8*width)-1))&0x1;
  *dest=*t0;
  //rtl_shri(s,dest,src1,(width)*8-1);
  //TODO();
}

#endif
