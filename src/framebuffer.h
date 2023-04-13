#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include <stdint.h>

typedef struct {
  uint32_t height; // physical height
  uint32_t width;  // physical width
  uint32_t pitch;  // Set by GPU. Zero first
  uint32_t depth;
  uint32_t x_offset;
  uint32_t y_offset;
  uintptr_t pointer; // the pointer to the framebuffer into which our code
                     // should write. This is set by the GPU. We will zero
                     // it before passing this structure to the GPU
  uint32_t size;     // size of the framebuffer, also set by GPU, we will zero
                     // it also before passing to the GPU
  uint32_t isrgb;
} framebuffer_t;

int init_framebuffer(framebuffer_t *fb);

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} pixel_t;

void write_pixel(uint8_t x, uint8_t y, const pixel_t *pixel, framebuffer_t *fb);
#endif
