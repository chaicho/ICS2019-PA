#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  //  kbd->keydown = 0;
  //  kbd->keycode = AM_KEY_NONE;
   uint16_t tmp=inw(0xa1000060);
   kbd->keydown=(tmp==AM_KEY_NONE)? 0:1;
   kbd->keycode=(tmp==AM_KEY_NONE)? 0:tmp ;
}
