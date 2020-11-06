#include <am.h>
#include <nemu.h>

 #define SYNC_ADDR (VGACTL_ADDR + 4)
void __am_gpu_init() {      
    int i;
    int w = 400;  // TODO: get the correct width
    int h = 300;  // TODO: get the correct height
    uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
    for (i = 0; i < w * h; i ++) fb[i] = i;
    outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  // uint32_t tmp=inl(VGACTL_ADDR);
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = 400, .height = 300,
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  // int xx=ctl->x;
  // int yy=ctl->y;
  // int ww=ctl->w;
  // int hh=ctl->h;
  // int i,j;
  // uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  // for(i=0;i<ww;i++){
  //   for(j=0;j<(hh);j++){
  //       *(fb+400*xx+yy+i*ww+j*hh)=*((uint32_t *) (ctl->pixels+i*ww+j*hh));
  //   }
  // }
  // if (ctl->sync) {
  //   // outl(SYNC_ADDR, 0);
  //   outl(SYNC_ADDR, 1);
  // }
    if (ctl->sync) {
    outl(SYNC_ADDR, 0);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
