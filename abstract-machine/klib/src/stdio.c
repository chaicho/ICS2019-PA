#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  va_list tmp;
  va_start(tmp,fmt);
  int i=0;
  int gg;
  int store[33],j=-1;
  while (fmt[i]!='\0')
  {
    if(fmt[i]!='%') {
      putch(fmt[i]);
      i++;
      continue;
    }
    if(fmt[i]=='%'){
        i++;
        switch (fmt[i++])
        {
        case 's':
        {
            char *s = va_arg(tmp, char *);
            int gg = 0;
            while (s[gg] != '\0')
            {
                putch(s[gg++]);
            }
             break;
         }
        case 'd':;
         {
            gg=(int)va_arg(tmp,int);
            // int store[20],j=-1;
            j=-1;
            while (gg)
            {
              store[++j]=gg%10;
            gg/=10;
         }
            for(;j>=0;--j){
            putch( '0'+store[j]);
             }      
        break;
        }
    }
    }
  }
  // *out = '\0';

  va_end(tmp);
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return 0;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list tmp;
  va_start(tmp,fmt);
  int i=0;
  int gg;
  int store[32],j=-1;
  while (fmt[i]!='\0')
  {
    if(fmt[i]!='%') {
      *(out++)=fmt[i++];
      continue;
    }
    if(fmt[i]=='%'){
        i++;
        switch (fmt[i++])
        {
        case 's':
        {
            char *s = va_arg(tmp, char *);
            int gg = 0;
            while (s[gg] != '\0')
            {
                *(out++) = s[gg++];
            }
             break;
         }
        case 'd':;
         {
            gg=(int)va_arg(tmp,int);
            // int store[20],j=-1;
            j=-1;
            while (gg)
            {
              store[++j]=gg%10;
            gg/=10;
         }
            for(;j>=0;--j){
            *out=(char) ('0'+store[j]);
            out++;
             }      
        break;
        }
    }
    }
  }
  *out = '\0';

  va_end(tmp);
  return 0;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  return 0;
}

#endif
