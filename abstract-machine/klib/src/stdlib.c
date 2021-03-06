#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static char *addr=NULL;
static unsigned long int next = 1;
// static unsigned long int before=NULL;
int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

void *malloc(size_t size) {
   if(addr==0){
     addr=heap.start;
    }
  char *old = addr;
      size  = (size_t)ROUNDUP(size, 8);
     
      addr += size;
     
      for (uint64_t *p = (uint64_t *)old; p != (uint64_t *)addr; p ++) {
        *p = 0;
      }
    return old;
}

void free(void *ptr) {
}

#endif
