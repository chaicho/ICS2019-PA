#include <isa.h>
#include <monitor/difftest.h>
#include "../local-include/reg.h"
#include "difftest.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  // if(ref_r->eflag!=cpu.eflag)printf("The supposed value: %x \n Wrong value : %x\n",ref_r->eflag,cpu.eflag);
  printf("CF:  %d    SF:   %d\n",cpu.eflag.CF,cpu.eflag.SF);
  if(ref_r->eflag.all!=cpu.eflag.all){
     return false;
  }
  if(ref_r->eax!=cpu.eax) {
    printf("The supposed EAX: %x \n Wrong EAX : %x\n",ref_r->eax,cpu.eax);
   printf("gg\n");
   // printf("CF:  %d  \n  SF:   %d\n",cpu.eflag.CF,cpu.eflag.SF);
    return false;
  }
   if(ref_r->ebp!=cpu.ebp) {
    printf("The supposed EBP: %x \n Wrong EBP : %x\n",ref_r->ebp,cpu.ebp);
    return false;
  }
   if(ref_r->ebx!=cpu.ebx) {
    printf("The supposed EBX: %x \n Wrong EBX : %x\n",ref_r->ebx,cpu.ebx);
    return false;
  }
   if(ref_r->ecx!=cpu.ecx) {
    printf("The supposed ECX: %x \n Wrong ECX : %x\n",ref_r->ecx,cpu.ecx);
    return false;
  }
   if(ref_r->edi!=cpu.edi) {
    printf("The supposed EDI: %x \n Wrong EDI : %x\n",ref_r->edi,cpu.edi);
    return false;
  }
   if(ref_r->edx!=cpu.edx) {
    printf("The supposed EDX: %x \n Wrong EDX : %x\n",ref_r->edx,cpu.edx);
    return false;
  }
  if(ref_r->esp!=cpu.esp) {
    printf("The supposed ESP: %x \n Wrong ESP : %x\n",ref_r->esp,cpu.esp);
    return false;
  }
  
  return true;
  // return ref_r->eax==cpu.eax&&ref_r->ebp==cpu.ebp&&ref_r->ebx==cpu.ebx&&ref_r->ecx==cpu.ecx&&ref_r->edi==cpu.edi&&ref_r->edx==cpu.edx&&ref_r->esp==cpu.esp;
}

void isa_difftest_attach() {
}
