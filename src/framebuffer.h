#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

struct framebuffer {
  unsigned int height; // physical height
  unsigned int width;  // physical width
  unsigned int pitch;  // Set by GPU. Zero first
  unsigned int depth;
  unsigned int x_offset;
  unsigned int y_offset;
  unsigned int *pointer; // the pointer to the framebuffer into which our code
                         // should write. This is set by the GPU. We will zero
                         // it before passing this structure to the GPU
  unsigned int size; // size of the framebuffer, also set by GPU, we will zero
                     // it also before passing to the GPU
  unsigned int isrgb;
};

int init_framebuffer(struct framebuffer *fb);

#endif
