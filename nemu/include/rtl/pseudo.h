#ifndef __RTL_PSEUDO_H__
#define __RTL_PSEUDO_H__

#ifndef __RTL_RTL_H__
#error "Should be only included by <rtl/rtl.h>"
#endif

/* RTL pseudo instructions */

static inline def_rtl(li, rtlreg_t* dest, const rtlreg_t imm) {
 *dest+=imm;
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
  rtl_shli(s,dest,src1,(4-width)*8);
  rtl_sari(s,dest,src1,(4-width)*8);
  //TODO();
}

static inline def_rtl(zext, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- zeroext(src1[(width * 8 - 1) .. 0])
  rtl_shli(s,dest,src1,(4-width)*8);
  rtl_shri(s,dest,src1,(4-width)*8);
  //TODO();
}

static inline def_rtl(msb, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- src1[width * 8 - 1]
  rtl_li(s,dest, src1[width * 8 - 1]);
  //rtl_shri(s,dest,src1,(width)*8-1);
  //TODO();
}

#endif
