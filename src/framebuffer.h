#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include <stdint.h>

#define COLORDEPTH 24
#define BYTES_PER_PIXEL COLORDEPTH / 8

typedef struct {
  uint32_t width;
  uint32_t height;
  uint32_t pitch;
  void *buf;
  uint32_t buf_size;
  uint32_t chars_width;
  uint32_t chars_height;
  uint32_t chars_x;
  uint32_t chars_y;
} framebuffer_info_t;

extern framebuffer_info_t fbinfo;

int init_framebuffer(void);
#endif
