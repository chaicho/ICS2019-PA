#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
 va_list tmp;
 va_start(tmp,fmt);
//   int i=0;
//   int gg;
//   int store[32],j=-1;
//   while (fmt[i]!='\0')
//   {
//     if(fmt[i]!='%') {
//      putch(fmt[i++]);
//       continue;
//     }
//     if(fmt[i]=='%'){
//         i++;
//         switch (fmt[i++])
//         {
//         case 'c':
//         {
//             while (1)
//             {
//               char c='\n';
//               putch(c);
//             }
            
//         }
//         case 's':
//         {
//             char *s = va_arg(tmp, char *);
//             int gg = 0;
//             while (s[gg] != '\0')
//             {
//                 putch(s[gg++]);
//             }
//             i++;
//              break;
             
//          }
//         case 'd':;
//          {
//             gg=(int)va_arg(tmp,int);
//             // int store[20],j=-1;
//             j=-1;
//             while (gg)
//             {
//               store[++j]=gg%10;
//             gg/=10;
//          }
//             for(;j>=0;--j){
//             putch ((char)'0'+store[j]);
//              }      
//            i++;  
//         break;
//         }
//     }
//     }
//   }

//   va_end(tmp);
  char buf[1000];
  char *out=buf;
  int len=vsprintf(buf,fmt,tmp);
  //putch(buf[0]);
  //assert(0);
  for(;len>0;len--){
    putch(*out);
      out++;
   }
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list tmp) {
  // va_start(tmp,fmt);
  int i=0,num_before=0;
  int gg;
  int store[32],j=-1;
  char *ggg=out;
  while (fmt[i]!='\0')
  {
    if(fmt[i]!='%') {
      *(ggg++)=fmt[i++];
      continue;
    }
    else{
        i++;
        while(fmt[i]>='0'&&fmt[i]<='9'){
          num_before=10*num_before+fmt[i]-'0';
          i++;
        }
        switch (fmt[i++])
        {
        case 'c':{
           char c=(char)va_arg(tmp,int );
          *(ggg++)=c;
           break;
        }
        case 's':
        {
            char *s = va_arg(tmp, char *);
            int gg = 0;
            while (s[gg] != '\0')
            {
                *(ggg++) = s[gg++];
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
            while(j<num_before){
              *(ggg++)='0';
              num_before--;
            }
           for(;j>=0;--j){
             *(ggg++)=(char) ('0'+store[j]);
               }      
        break;
        }
    }
    }
  }
  *ggg = '\0';

  va_end(tmp);
  return (int)(ggg-out);
}

int sprintf(char *out, const char *fmt, ...) {
  va_list tmp;

   va_start(tmp,fmt);
  // int i=0;
  // int gg;
  // int store[32],j=-1;
  // char *ggg=out;
  // while (fmt[i]!='\0')
  // {
  //   if(fmt[i]!='%') {
  //     *(ggg++)=fmt[i++];
  //     continue;
  //   }
  //   else{
  //       i++;
  //       switch (fmt[i++])
  //       {
  //       case 'c':{
  //          char c=(char)va_arg(tmp,int );
  //         *(ggg++)=c;
  //          break;
  //       }
  //       case 's':
  //       {
  //           char *s = va_arg(tmp, char *);
  //           int gg = 0;
  //           while (s[gg] != '\0')
  //           {
  //               *(ggg++) = s[gg++];
  //           }
  //            break;
  //        }
  //       case 'd':;
  //        {
  //           gg=(int)va_arg(tmp,int);
  //           // int store[20],j=-1;
  //           j=-1;
  //           while (gg)
  //           {
  //             store[++j]=gg%10;
  //             gg/=10;
  //           }
  //          for(;j>=0;--j){
  //            *(ggg++)=(char) ('0'+store[j]);
  //              }      
  //       break;
  //       }
  //   }
  //   }
  // }
  // *ggg = '\0';
  int len=vsprintf(out,fmt,tmp);
  // va_end(tmp);
  return len;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  return 0;
}

#endif
