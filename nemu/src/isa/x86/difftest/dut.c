#include <isa.h>
#include <monitor/difftest.h>
#include "../local-include/reg.h"
#include "difftest.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  // if(ref_r->eflag!=cpu.eflag)printf("The supposed value: %x \n Wrong value : %x\n",ref_r->eflag,cpu.eflag);
  
   bool fla=true;
   if(ref_r->pc!=cpu.pc){
      printf("The supposed pc: %x \n Wrong pc : %x\n",ref_r->pc,cpu.pc);
  fla=false;
   }
  // if(ref_r->eflag.CF!=cpu.eflag.CF){
  //    printf("The supposed CF: %x \n Wrong CF : %x\n",ref_r->eflag .CF,cpu.eflag.CF);
  //    fla=false;
  // }
  // if(ref_r->eflag.OF!=cpu.eflag.OF){
  //    printf("The supposed OF: %x \n Wrong OF : %x\n",ref_r->eflag .OF,cpu.eflag.OF);
  //    fla=false;
  // }
  // if(ref_r->eflag.ZF!=cpu.eflag.ZF){
  //     printf("The supposed ZF: %x \n Wrong ZF : %x\n",ref_r->eflag .ZF,cpu.eflag.ZF);
  //    fla=false;
  //  }
  // if(ref_r->eflag.SF!=cpu.eflag.SF){
  //    printf("The supposed SF: %x \n Wrong SF : %x\n",ref_r->eflag .SF,cpu.eflag.SF);
  //    fla=false;
  // }
  // if(ref_r->eflag.all!=cpu.eflag.all){
  //    return false;
  // }
  if(ref_r->eax!=cpu.eax) {
    printf("The supposed EAX: %x \n Wrong EAX : %x\n",ref_r->eax,cpu.eax);
  fla=false;
  }
   if(ref_r->ebp!=cpu.ebp) {
    printf("The supposed EBP: %x \n Wrong EBP : %x\n",ref_r->ebp,cpu.ebp);
  fla=false;
  }
   if(ref_r->ebx!=cpu.ebx) {
    printf("The supposed EBX: %x \n Wrong EBX : %x\n",ref_r->ebx,cpu.ebx);
    fla=false;
  }
   if(ref_r->ecx!=cpu.ecx) {
    printf("The supposed ECX: %x \n Wrong ECX : %x\n",ref_r->ecx,cpu.ecx);
    fla=false;
  }
   if(ref_r->edi!=cpu.edi) {
    printf("The supposed EDI: %x \n Wrong EDI : %x\n",ref_r->edi,cpu.edi);
   fla=false;
  }
   if(ref_r->edx!=cpu.edx) {
    printf("The supposed EDX: %x \n Wrong EDX : %x\n",ref_r->edx,cpu.edx);
    fla=false;
  }
  if(ref_r->esp!=cpu.esp) {
    printf("The supposed ESP: %x \n Wrong ESP : %x\n",ref_r->esp,cpu.esp);
    fla=false;
  }
  if(!fla) printf("PC %x: ZF : %d  OF : %d  CF:  %d    SF:   %d\n",cpu.pc,cpu.eflag.ZF,cpu.eflag.OF,cpu.eflag.CF,cpu.eflag.SF);
  return fla;
  // return ref_r->eax==cpu.eax&&ref_r->ebp==cpu.ebp&&ref_r->ebx==cpu.ebx&&ref_r->ecx==cpu.ecx&&ref_r->edi==cpu.edi&&ref_r->edx==cpu.edx&&ref_r->esp==cpu.esp;
}

void isa_difftest_attach() {
}
