#include <am.h>
#include <nemu.h>
#include <klib.h>
#define W 400
#define H 300
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
  //  int xx=ctl->x;
  //  int yy=ctl->y;
  // int ww=ctl->w;
  // int hh=ctl->h;
  // int i,j;
   uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  //  for(i=0;i<(hh*4);i++){
  //    for(j=0;j<(ww*4);j++){
  //        *(fb+xx+yy*400+i+j)=*((uint32_t *) (ctl->pixels+i+j));
  //    }
  //  }
  // *fb=1;
  int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
  uint32_t *pixels = ctl->pixels;
  int cp_bytes = (W-x>x) ?   sizeof(uint32_t) * w :sizeof(uint32_t) *(W - x);
  for (int j = 0; j < h && y + j < H; j ++) {
    memcpy(&fb[(y + j) * W + x], pixels, cp_bytes);
    pixels += w;
  }
  if (ctl->sync) {
    // outl(SYNC_ADDR, 0);
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
