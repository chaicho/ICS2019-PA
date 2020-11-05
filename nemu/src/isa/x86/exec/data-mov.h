static inline def_EHelper(mov) {
  operand_write(s, id_dest, dsrc1);
  print_asm_template2(mov);
}

static inline def_EHelper(push) {
  if(id_dest->width==1) rtl_sext(s,ddest,ddest,1);
  rtl_push(s,ddest);
  print_asm_template1(push);
}

static inline def_EHelper(pop) {
  //TODO();
  rtl_pop(s,ddest);
  print_asm_template1(pop);
}

static inline def_EHelper(pusha) {
  TODO();

  print_asm("pusha");
}

static inline def_EHelper(popa) {
  TODO();

  print_asm("popa");
}

static inline def_EHelper(leave) {
  rtl_mv(s,&cpu.esp,&cpu.ebp);
  rtl_pop(s,s0);
  if(s->isa.is_operand_size_16) cpu.gpr[R_EBP]._16=*s0;
  else cpu.gpr[R_EBP]._32=*s0;
  //cpu.ebp=*s0;
  print_asm("leave");
}

static inline def_EHelper(cltd) {
  if (s->isa.is_operand_size_16) {
    rtl_lr(s,s0,R_AX,2);
    rtl_msb(s,s0,s0,2);  
    *s0=*s0<<15;
    rtl_sr(s,R_DX,s0,2);
  }
  else {
    rtl_lr(s,s0,R_AX,4);
    rtl_msb(s,s0,s0,4);  
    *s0=*s0<<31;
    rtl_sr(s,R_EDX,s0,4);
  }

  print_asm(s->isa.is_operand_size_16 ? "cwtl" : "cltd");
}

static inline def_EHelper(cwtl) {
  if (s->isa.is_operand_size_16) {
     rtl_lr(s,s0,R_AL,1);
     rtl_sext(s,s0,s0,1);
     rtl_sr(s,R_AX,s0,2);  
  }
  else {
    rtl_lr(s,s0,R_AX,2);
    // printf("AX: %x\n",*s0);
    rtl_sext(s,s0,s0,2);
    rtl_sr(s,R_EAX,s0,4);
  } 

  print_asm(s->isa.is_operand_size_16 ? "cbtw" : "cwtl");
}

static inline def_EHelper(movsx) {
  id_dest->width = s->isa.is_operand_size_16 ? 2 : 4;
  rtl_sext(s, ddest, dsrc1, id_src1->width);
  operand_write(s, id_dest, ddest);
  print_asm_template2(movsx);
}

static inline def_EHelper(movzx) {
  id_dest->width = s->isa.is_operand_size_16 ? 2 : 4;
  rtl_zext(s, ddest, dsrc1, id_dest->width);
  operand_write(s, id_dest, dsrc1);
  print_asm_template2(movzx);
}

static inline def_EHelper(movsb) {
  int tt=0;
  if(id_dest->width==1) {
      tt=1;
     rtl_sm(s,ddest,0,dsrc1,1);
  }
 else{
    id_dest->width = s->isa.is_operand_size_16 ? 2 : 4;
    tt= s->isa.is_operand_size_16 ? 2 : 4;
    //operand_write(s, id_dest, dsrc1); 
    rtl_sm(s,ddest,0,dsrc1,id_dest->width);
 } 
    // *s0=reg_l(R_EDI)+1;
    cpu.edi+=tt;
    cpu.esi+=tt;
    print_asm_template2(movsb);


  // print_asm_template2(movzx);
}
static inline def_EHelper(lea) {
  rtl_addi(s, ddest, s->isa.mbase, s->isa.moff);
  operand_write(s, id_dest, ddest);
  print_asm_template2(lea);
}

