#include <isa.h>
#include <monitor/difftest.h>
#include "../local-include/reg.h"
#include "difftest.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  // if(ref_r->eflag!=cpu.eflag)printf("The supposed value: %x \n Wrong value : %x\n",ref_r->eflag,cpu.eflag);
  if(ref_r->eax!=cpu.eax) {
    printf("The supposed value: %x \n Wrong value : %x\n",ref_r->eax,cpu.eax);
    return false;
  }
   if(ref_r->ebp!=cpu.ebp) {
    printf("The supposed value: %x \n Wrong value : %x\n",ref_r->ebp,cpu.ebp);
    return false;
  }
   if(ref_r->ebx!=cpu.ebx) {
    printf("The supposed value: %x \n Wrong value : %x\n",ref_r->ebx,cpu.ebx);
    return false;
  }
   if(ref_r->ecx!=cpu.ecx) {
    printf("The supposed value: %x \n Wrong value : %x\n",ref_r->ecx,cpu.ecx);
    return false;
  }
   if(ref_r->edi!=cpu.edi) {
    printf("The supposed value: %x \n Wrong value : %x\n",ref_r->edi,cpu.edi);
    return false;
  }
   if(ref_r->edx!=cpu.edx) {
    printf("The supposed value: %x \n Wrong value : %x\n",ref_r->edx,cpu.edx);
    return false;
  }
  if(ref_r->esp!=cpu.esp) {
    printf("The supposed value: %x \n Wrong value : %x\n",ref_r->esp,cpu.esp);
    return false;
  }
  return true;
  // return ref_r->eax==cpu.eax&&ref_r->ebp==cpu.ebp&&ref_r->ebx==cpu.ebx&&ref_r->ecx==cpu.ecx&&ref_r->edi==cpu.edi&&ref_r->edx==cpu.edx&&ref_r->esp==cpu.esp;
}

void isa_difftest_attach() {
}
