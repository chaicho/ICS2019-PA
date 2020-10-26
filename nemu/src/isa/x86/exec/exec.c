#include <cpu/exec.h>
#include "../local-include/decode.h"
#include "all-instr.h"

static inline void set_width(DecodeExecState *s, int width) {
  if (width == -1) return;
  if (width == 0) {
    width = s->isa.is_operand_size_16 ? 2 : 4;
  }
  s->src1.width = s->dest.width = s->src2.width = width;
}

/* 0x80, 0x81, 0x83 */
static inline def_EHelper(gp1) {
  switch (s->isa.ext_opcode) {/// I2E
    EX(0,add) EMPTY(1) EMPTY(2) EMPTY(3)
    EX(4,and) EX(5,sub) EXW(6,xor,1) EX(7,cmp)
  }
}

/* 0xc0, 0xc1, 0xd0, 0xd1, 0xd2, 0xd3 */
static inline def_EHelper(gp2) {
  switch (s->isa.ext_opcode) {
    EMPTY(0) EMPTY(1) EMPTY(2) EMPTY(3)
    EX(4,shl) EMPTY(5) EMPTY(6) EX(7,sar)
  }
}


/* 0xf6, 0xf7 */
static inline def_EHelper(gp3) {
  switch (s->isa.ext_opcode) {
    IDEXW(0,test_I,test,1) EMPTY(1) EX(2,not) EMPTY(3)
    EMPTY(4) EMPTY(5) EMPTY(6)  EX(7,idiv)
  }
}

/* 0xfe */
static inline def_EHelper(gp4) {
  switch (s->isa.ext_opcode) {
    EMPTY(0) EMPTY(1) EMPTY(2) EMPTY(3)
    EMPTY(4) EMPTY(5) EMPTY(6) EMPTY(7)
  }
}

/* 0xff */
static inline def_EHelper(gp5) {
  switch (s->isa.ext_opcode) {
    EX(0,inc) EMPTY(1) EMPTY(2) EMPTY(3)
    EMPTY(4) EMPTY(5) EX(6,push) EMPTY(7)
  }
}

/* 0x0f 0x01*/
static inline def_EHelper(gp7) {
  switch (s->isa.ext_opcode) {
    EMPTY(0) EMPTY(1) EMPTY(2) EMPTY(3)
    EMPTY(4) EMPTY(5) EMPTY(6) EMPTY(7)
  }
}
static inline def_EHelper(endbr){
  instr_fetch(&s->seq_pc,1);
  instr_fetch(&s->seq_pc,2);
}
static inline def_EHelper(){

}
static inline def_EHelper(2byte_esc) {
  uint8_t opcode = instr_fetch(&s->seq_pc, 1);
  s->opcode = opcode;
  switch (opcode) {
  /* TODO: Add more instructions!!! */
    IDEX (0x01, gp7_E, gp7)
    IDEXW (0X94,setcc_E, setcc,1)
    IDEXW (0X95,setcc_E, setcc,1)
    IDEXW (0xb6,mov_E2G,movzx,1)
    IDEX (0xaf,E2G,imul2);
    default: exec_inv(s);
  }
}

static inline void fetch_decode_exec(DecodeExecState *s) {
  uint8_t opcode;
  //assert(0);
again:
  opcode = instr_fetch(&s->seq_pc, 1);
  s->opcode = opcode;
  //printf("op: %x\n",s->opcode);
  switch (opcode) {
    EX   (0x0f, 2byte_esc)
    IDEXW(0x80, I2E, gp1, 1)
    IDEX (0x81, I2E, gp1)
    IDEX (0x83, SI2E, gp1)
    IDEXW(0x88, mov_G2E, mov, 1) 
    IDEX (0x89, mov_G2E, mov)
    IDEXW(0x8a, mov_E2G, mov, 1)
    IDEX (0x8b, mov_E2G, mov)
    IDEXW(0xa0, O2a, mov, 1)
    IDEX (0xa1, O2a, mov)
    IDEXW(0xa2, a2O, mov, 1)
    IDEX (0xa3, a2O, mov)
    IDEXW(0xb0, mov_I2r, mov, 1)
    IDEXW(0xb1, mov_I2r, mov, 1)
    IDEXW(0xb2, mov_I2r, mov, 1)
    IDEXW(0xb3, mov_I2r, mov, 1)
    IDEXW(0xb4, mov_I2r, mov, 1)
    IDEXW(0xb5, mov_I2r, mov, 1)
    IDEXW(0xb6, mov_I2r, mov, 1)
    IDEXW(0xb7, mov_I2r, mov, 1)
    IDEX (0xb8, mov_I2r, mov)
    IDEX (0xb9, mov_I2r, mov)
    IDEX (0xba, mov_I2r, mov)
    IDEX (0xbb, mov_I2r, mov)
    IDEX (0xbc, mov_I2r, mov)
    IDEX (0xbd, mov_I2r, mov)
    IDEX (0xbe, mov_I2r, mov)
    IDEX (0xbf, mov_I2r, mov)
    IDEXW(0xc0, gp2_Ib2E, gp2, 1)
    IDEX (0xc1, gp2_Ib2E, gp2)
    IDEXW(0xc6, mov_I2E, mov, 1)
    IDEX (0xc7, mov_I2E, mov)
    EX   (0xc9, leave);
    IDEXW(0xd0, gp2_1_E, gp2, 1)
    IDEX (0xd1, gp2_1_E, gp2)
    IDEXW(0xd2, gp2_cl2E, gp2, 1)
    IDEX (0xd3, gp2_cl2E, gp2)
    EX   (0xd6, nemu_trap)
    EX (0xf3,endbr)
    IDEXW(0xf6, E, gp3, 1)
    IDEX (0xf7, E, gp3)
    IDEXW(0xfe, E, gp4, 1)
    IDEX (0xff, E, gp5)
    IDEX (0xe8, J, call)
    IDEX (0x50,r,push) IDEX (0x51, r, push) IDEX(0x52,r,push) IDEX (0x53, r, push)  IDEX (0x55, r, push)  IDEX (0x56, r, push)  IDEX (0x57, r, push) 
    IDEXW(0x6a, push_SI,push,1)
    IDEX (0x01, G2E, add)
    IDEX (0x68, push_SI, push)
    IDEXW (0X74, J, jcc,1)  IDEXW(0x75,J,jcc,1) IDEXW(0x7e,J,jcc,1) IDEXW(0x7f,J,jcc,1)
    IDEX (0X31, G2E,xor)
    // IDEX (0x58, r,pop)
    IDEX (0x8d, lea_M2G ,lea)
    IDEXW (0x84,G2E, test,1) IDEX(0X85,G2E,test) 
    IDEXW (0xeb,J,jmp,1)
    IDEX (0x3b, E2G , cmp) IDEX(0x3d,I2a,cmp)
    IDEX (0x41,r,inc) IDEX(0x43,r,inc) IDEX( 0x47,r, inc) IDEX(0x40,r,inc) IDEX(0x46,r,inc) IDEX(0x42,r,inc) IDEX(0x44,r,inc) IDEX(0x45,r,inc)
    IDEX(0x4b,r,dec)  IDEX(0x48,r,dec) IDEX(0x49,r,dec) IDEX(0x4a,r,dec)
    IDEX (0x5a,r,pop)  IDEX (0x5d,r,pop)  IDEX (0x59,r,pop) IDEX (0x5e,r,pop)  IDEX (0x5f,r,pop) IDEX(0x5b,r,pop) IDEX (0x58,r,pop) 
   // IDEXW(0xff,O,push,1)
    EX   (0xc3, ret )
    IDEX(0x03,E2G,add)
    IDEX(0x09,G2E,or) IDEXW (0x0a,E2G,or,1)
    IDEXW (0x22,E2G,and,1)
    IDEX( 0x13,E2G,adc)
    IDEX(0x39,G2E,cmp)
    IDEX(0x2b,E2G,sub) 
    IDEX(0x1b,E2G,sbb)
    EX(0x99,cltd)
    case(0x90):  break;
  case 0x66: s->isa.is_operand_size_16 = true; goto again;
  default: exec_inv(s);
  }
}

vaddr_t isa_exec_once() {
  DecodeExecState s;
  s.is_jmp = 0;
  s.isa = (ISADecodeInfo) { 0 };
  s.seq_pc = cpu.pc;
  //printf("%x: \n",s.seq_pc);
  fetch_decode_exec(&s);
 // assert(0);
 // printf("JUMP = %d  to  %x with code %x\n",s.is_jmp,s.jmp_pc, s.opcode);
  update_pc(&s);
  
  return s.seq_pc;
}
