#include <isa.h>
#include <monitor/difftest.h>
#include "../local-include/reg.h"
#include "difftest.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  return ref_r->eax==cpu.eax&&ref_r->ebp==cpu.ebp&&ref_r->ebx==cpu.ebx&&ref_r->ecx==cpu.ecx&&ref_r->edi==cpu.edi&&ref_r->edx==cpu.edx&&ref_r->esp==cpu.esp;
}

void isa_difftest_attach() {
}
