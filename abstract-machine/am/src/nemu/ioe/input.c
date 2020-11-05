#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  //  kbd->keydown = 0;
  //  kbd->keycode = AM_KEY_NONE;
   uint32_t tmp=inl(0xa1000060);
   kbd->keydown=(tmp==AM_KEY_NONE);
   kbd->keycode=tmp;
}
