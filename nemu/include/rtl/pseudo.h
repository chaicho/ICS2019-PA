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
  rtl_xori(s,dest,src1,0xffffffff);
  //TODO();
}

static inline def_rtl(neg, rtlreg_t *dest, const rtlreg_t* src1) {
  // dest <- -src1
  rtl_sub(s,dest,rz,src1);
  //TODO();
}

static inline def_rtl(sext, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- signext(src1[(width * 8 - 1) .. 0])
//  rtl_shli(s,t0,src1,8*(width-id_src1->width));
  rtl_shli(s,t0,src1,8*(width-1));
  printf("from :%d",*t0);
  rtl_sari(s,t0,t0,8*(width-1));
  printf("to: %d\n",*t0);
 // rtl_sari(s,t0,t0,8*(width-id_src1->width));
  //TODO();
  //operand_write(s,id_dest,src1);
}

static inline def_rtl(zext, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- zeroext(src1[(width * 8 - 1) .. 0])
  rtl_shli(s,dsrc1,src1,(4-width)*8);
  rtl_shri(s,ddest,src1,(4-width)*8);
  //TODO();
}

static inline def_rtl(msb, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- src1[width * 8 - 1]
  *t0=(*src1>>((8*width)-1))&0x1;
  rtl_li(s,dest,*t0);
  
  //rtl_shri(s,dest,src1,(width)*8-1);
  //TODO();
}

#endif
