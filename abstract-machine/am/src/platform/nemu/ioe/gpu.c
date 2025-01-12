#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
  // int hw = inl(VGACTL_ADDR);
  // int w = (hw & 0xffff0000) >> 16;
  // int h = hw & 0x0000ffff;
  // uint32_t *fb = (uint32_t *)FB_ADDR;
  // for (int i = 0; i < w * h; ++i) fb[i] = i;
  // outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = 0, .height = 0,
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  if (ctl->pixels != NULL) {
    int hw = inl(VGACTL_ADDR);
    int w = (hw & 0xffff0000) >> 16;
    // int h = hw & 0x0000ffff;
    uint32_t *fb = (uint32_t *)FB_ADDR;
    for (int dy = 0; dy < ctl->h; ++dy) {
      for (int dx = 0; dx < ctl->w; ++dx) {
        fb[(ctl->x + dx) + (ctl->y + dy) * w] = ((uint32_t *)ctl->pixels)[dx + dy * ctl->w];
      }
    }
  }
  int hw = inl(VGACTL_ADDR);
  int w = (hw & 0xffff0000) >> 16;
  int h = hw & 0x0000ffff;
  uint32_t *fb = (uint32_t *)FB_ADDR;
  for (int i = 0; i < w * h; ++i) fb[i] = i;
  if (ctl->sync) {putstr("invoked __am_gpu_fbdraw and sync\n");
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
