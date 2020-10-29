#include <klib.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t t=0;
  while(s[t]!='\0') t++;
  return t;
}

char *strcpy(char* dst,const char* src) {
  //assert(strlen(dst)>=strlen(src));
  size_t i;
  for(i=0;src[i]!='\0';i++) dst[i]=src[i];
  dst[i]='\0';
  // assert(0);
  return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
  size_t i;
  for(i=0;i<n&&src[i]!='\0';i++) dst[i]=src[i];
  for(;i<n;i++) dst[i]='\0';
  return dst;
}

char* strcat(char* dst, const char* src) {
  size_t i=0;
  while (dst[i]!='\0') i++;
  //assert(dst[i]=='\0');
  strcpy(dst+i,src);
  return dst;
}

int strcmp(const char* s1, const char* s2) {
  while (*s1==*s2) {
    if(*(s1)=='\0'||*(s2)=='\0') break;
    s1++;
    s2++;
  }
  return *(s1)-*(s2);
}

int strncmp(const char* s1, const char* s2, size_t n) {
while ((n--)>0&&*s1==*s2) {
    if(*(s1)=='\0') break;
    s1++;
    s2++;
  }  return 0;
}

void* memset(void* v,int c,size_t n) {
  //assert(0);
  size_t i=0;
  unsigned char *s=(unsigned char *)v;
  for(i=0;i<n;i++){
    *(s++)= c;
  }
  return v;
}

void* memmove(void* dst,const void* src,size_t n) {
 // assert(0);
  return NULL;
}

void* memcpy(void* out, const void* in, size_t n) {
   unsigned char *c1=(unsigned char *)out;
   unsigned char *c2=(unsigned char *)in;
  while ((n--)>0)
  {
    *(c1++)=*(c2++);
  }
  return out;
}

int memcmp(const void* s1, const void* s2, size_t n) {
  unsigned char *c1=(unsigned char *)s1;
  unsigned char *c2=(unsigned char *)s2;
  while ((--n)>0&&*c1==*c2) {
    if(*(c1)=='\0'||*(c2)=='\0') break;
    c1++;
    c2++;
  }
  return *c1-*c2;
}

#endif
