#include "cc.h"


static inline def_EHelper(test) {
  //TODO();
  rtl_and(s,s0,ddest,dsrc1);
 // operand_write(s,id_dest,s0);
  cpu.eflag.CF=0;
  cpu.eflag.OF=0;
  rtl_update_ZFSF(s,s0,id_dest->width); 
  print_asm_template2(test);
}

static inline def_EHelper(and) {
 
  //rtl_sext(s, dsrc1, dsrc1, id_src1->width);
  //if(s->src1.width==1) *dsrc1|=0xfffffff00;
  rtl_and(s,ddest,ddest,dsrc1);
  operand_write(s,id_dest,ddest);
  cpu.eflag.CF=0;
  cpu.eflag.OF=0;
  rtl_update_ZFSF(s,ddest,id_dest->width);
  print_asm_template2(and);
}

static inline def_EHelper(xor) {
  rtl_xor(s,s0,ddest,dsrc1);
  rtl_update_ZFSF(s,s0,id_dest->width);
  operand_write(s,id_dest,s0);
  cpu.eflag.CF=0;
  cpu.eflag.OF=0;
  print_asm_template2(xor);
}

static inline def_EHelper(or) {
  //TODO();
  rtl_or(s,ddest,ddest,dsrc1);
  operand_write(s,id_dest,ddest);
  cpu.eflag.CF=0;
  cpu.eflag.OF=0;
  rtl_update_ZFSF(s,ddest,id_dest->width);
  print_asm_template2(or);
}

static inline def_EHelper(sar) {
  //TODO();
  // unnecessary to update CF and OF in NEMU
  printf("length %d\n",id_dest->width);
  if(s->isa.is_operand_size_16) rtl_sext(s,s0,ddest,2);
  else *s0=*ddest;
  rtl_sar(s,s0,s0,dsrc1);
  //TODO();
  //cpu.edx>>=3;
  //operand_write(s,id_dest,s0);
    operand_write(s,id_dest,s0);

  rtl_update_ZFSF(s,s0,id_dest->width);
  //TODO();
  operand_write(s,id_dest,s0);
  print_asm_template2(sar);
}

static inline def_EHelper(shl) {
 //TODO();
  // unnecessary to update CF and OF in NEMU
 rtl_shl(s,s0,ddest,dsrc1); 
 operand_write(s,id_dest,s0); 
 rtl_update_ZFSF(s,s0,id_dest->width);
  print_asm_template2(shl);
}

static inline def_EHelper(shr) {
  // printf("length %d\n",id_dest->width);
    // printf("NOW:length %d\n",id_dest->width);

 rtl_shr(s,s0,ddest,dsrc1);
//  printf("%x\n",*s0);
//  printf("length %d\n",id_dest->width);
 //id_dest->width=id_src1->width;
 operand_write(s,id_dest,s0); 
 rtl_update_ZFSF(s,s0,id_dest->width);

  print_asm_template2(shr);
}


static inline def_EHelper(setcc) {
  uint32_t cc = s->opcode & 0xf;
  rtl_setcc(s, ddest, cc);
  operand_write(s, id_dest, ddest);

  print_asm("set%s %s", get_cc_name(cc), id_dest->str);
}

static inline def_EHelper(not) {
  rtl_not(s,ddest,ddest);
  operand_write(s,id_dest,ddest);
  print_asm_template1(not);
}

