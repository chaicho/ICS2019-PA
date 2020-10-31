#ifndef __CC_H__
#define __CC_H__

#include "../local-include/rtl.h"

enum {
  CC_O, CC_NO, CC_B,  CC_NB,
  CC_E, CC_NE, CC_BE, CC_NBE,
  CC_S, CC_NS, CC_P,  CC_NP,
  CC_L, CC_NL, CC_LE, CC_NLE
};


/* Condition Code */

static inline const char* get_cc_name(int subcode) {
  static const char *cc_name[] = {
    "o", "no", "b", "nb",
    "e", "ne", "be", "nbe",
    "s", "ns", "p", "np",
    "l", "nl", "le", "nle"
  };
  return cc_name[subcode];
}

static inline void rtl_setcc(DecodeExecState *s, rtlreg_t* dest, uint32_t subcode) {
  uint32_t invert = subcode & 0x1;

  // TODO: Query EFLAGS to determine whether the condition code is satisfied.
  // dest <- ( cc is satisfied ? 1 : 0)
  switch (subcode & 0xe) {
    case CC_O:
     *ddest= (cpu.eflag.OF==1)? 1:0; 
    break;
    case CC_B:
     *ddest=(cpu.eflag.CF==1)? 1:0;
     break;
    case CC_E: 
      //rtl_update_ZF(s,dest,id_dest->width);
     *dest= cpu.eflag.ZF==1 ? 1: 0;
      assert(*dest==cpu.eflag.ZF);
            //printf("%d\n",*dest);
      break;
    case CC_BE:
      if(cpu.eflag.ZF==1||cpu.eflag.CF==1) *dest=1;
      else *dest=0;
      break;
    case CC_S:
      *dest=(cpu.eflag.SF==1)? 1:0;
      break;
    case CC_L:
      if(cpu.eflag.SF!=cpu.eflag.OF)  *dest=1;
      else *dest =0;
      break;
    case CC_LE:
      //TODO();
      if(cpu.eflag.ZF==1||cpu.eflag.OF!=cpu.eflag.SF) *dest=1;
      else *dest=0;
      break;
       
    default: panic("should not reach here");
    case CC_P: panic("PF is not supported");
  }
  //if((*dest)==1) printf("JUMPPPP\n");
  if (invert) {
    rtl_xori(s, dest, dest, 0x1);
  }
  assert(*dest == 0 || *dest == 1);
}

#endif
