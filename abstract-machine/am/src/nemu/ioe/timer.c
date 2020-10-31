#include <am.h>
#include <nemu.h>
// static uint32_t boot_time;
void __am_timer_init() {
  // asm volatile ("inl %1, %0" : "=a"(boot_time) : "d"(0x48)); 
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint32_t data;
  asm volatile ("inl %1, %0" : "=a"(data) : "d"(0x48));    
  uptime->us=(data)*1000000;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
