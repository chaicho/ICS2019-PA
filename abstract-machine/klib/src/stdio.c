#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return 0;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list tmp;
  va_start(tmp,fmt);
  int i=0;
  int loc=0;
  while (fmt[i]!='\0')
  {
    if(fmt[i]!='%') {
      out[loc++]=fmt[i++];
      continue;
    }
    if(fmt[i]=='%'){
      i++;
    }
    switch (fmt[i])
    {
    case 's':;
      char* s=va_arg(tmp,char *);
      int gg=0;
      while (s[gg]!='\0')
      {
         out[loc++]=s[gg++];
      }
      break;
    case 'd':;
      int gg1=(int)va_arg(tmp,int);
      // int store[20],j=-1;
      // while (gg1)
      // {
      //     store[++j]=gg1%10;
      //     gg1/=10;
      // }
      // for(;j>=0;--j){
      //    out[loc++]=(char) '0'+store[j];
      // }
      out[loc++]=gg1+'0';
      break;
    default:
      break;
    }
    out[loc++]='\0';

    va_end(tmp);
  }
  
  return 0;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  return 0;
}

#endif
