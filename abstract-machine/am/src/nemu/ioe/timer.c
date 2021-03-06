#include <am.h>
#include <nemu.h>
 static uint32_t boot_time=0;
void __am_timer_init() {
   boot_time=inl(RTC_ADDR+4);
  // asm volatile ("inl %1, %0" : "=a"(boot_time) : "d"(0x48)); 
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint32_t data;
  data=inl(RTC_ADDR+4);    
  uptime->us=(data-boot_time)*1000000+inl(RTC_ADDR);
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
