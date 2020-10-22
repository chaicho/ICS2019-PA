#include "cc.h"


static inline def_EHelper(test) {
  //TODO();
  //rtl_and(s,ddest,ddest,dsrc1);
 cpu.eflag.CF=0;
  cpu.eflag.ZF=0;
  rtl_update_ZFSF(s,ddest,s->width); 
  print_asm_template2(test);
}

static inline def_EHelper(and) {
 //TODO();
 rtl_and(s,ddest,ddest,dsrc1);
  cpu.eflag.CF=0;
  cpu.eflag.OF=0;
  print_asm_template2(and);
}

static inline def_EHelper(xor) {
  rtl_xor(s,ddest,ddest,dsrc1);

  print_asm_template2(xor);
}

static inline def_EHelper(or) {
  TODO();

  print_asm_template2(or);
}

static inline def_EHelper(sar) {
  //TODO();
  // unnecessary to update CF and OF in NEMU
  rtl_sari(s,ddest,ddest,*dsrc1);
  rtl_update_ZFSF(s,ddest,s->width);
  print_asm_template2(sar);
}

static inline def_EHelper(shl) {
 //TODO();
  // unnecessary to update CF and OF in NEMU
  
rtl_shli(s,ddest,ddest,*dsrc1);
rtl_update_ZFSF(s,ddest,s->width);
  print_asm_template2(shl);
}

static inline def_EHelper(shr) {
  TODO();
  // unnecessary to update CF and OF in NEMU

  print_asm_template2(shr);
}


static inline def_EHelper(setcc) {
  uint32_t cc = s->opcode & 0xf;
  rtl_setcc(s, ddest, cc);
  operand_write(s, id_dest, ddest);

  print_asm("set%s %s", get_cc_name(cc), id_dest->str);
}

static inline def_EHelper(not) {
  TODO();

  print_asm_template1(not);
}

