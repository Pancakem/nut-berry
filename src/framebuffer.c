#include "framebuffer.h"
#include "mbox.h"
#include "pl011_uart.h"
#include "util.h"

int init_framebuffer(struct framebuffer *fb) {
  fb->width = 1024;
  fb->height = 768;
  fb->depth = 32;
  fb->x_offset = 0;
  fb->y_offset = 0;

  // these are set by the GPU.
  fb->size = 0;
  fb->pointer = 0;
  fb->pitch = 0;

  mbox[0] = 35 * 4;
  mbox[1] = MBOX_REQUEST;

  mbox[2] = 0x48003; // set phy wh
  mbox[3] = 8;
  mbox[4] = 8;
  mbox[5] = fb->width;
  mbox[6] = fb->height;

  mbox[7] = 0x48004; // set virt wh
  mbox[8] = 8;
  mbox[9] = 8;
  mbox[10] = fb->width;
  mbox[11] = fb->height;

  mbox[12] = 0x48009; // set offset
  mbox[13] = 8;
  mbox[14] = 8;
  mbox[15] = fb->x_offset;
  mbox[16] = fb->y_offset;

  mbox[17] = 0x48005; // set depth
  mbox[18] = 4;
  mbox[19] = 4;
  mbox[20] = fb->depth;

  mbox[21] = 0x48006; // set pixel order
  mbox[22] = 4;
  mbox[23] = 4;
  mbox[24] = 1; // RGB, not BGR preferably

  mbox[25] = 0x40001; // get framebuffer, gets alignment on request
  mbox[26] = 8;
  mbox[27] = 8;
  mbox[28] = 0; // fb->pointer;
  mbox[29] = fb->size;

  mbox[30] = 0x40008; // get pitch
  mbox[31] = 4;
  mbox[32] = 4;
  mbox[33] = fb->pitch;

  mbox[34] = MBOX_TAG_LAST;

  int result = mbox_call(MBOX_CH_FB);
  char res[33] = {0};
  my_sprintf(res, "\n%d", result);
  pl011_uart_puts(res);
  if (mbox[28] != 0) {
    fb->pointer =
        (unsigned int *)(mbox[28] &
                         0x3FFFFFFF); // convert pointer to ARM address
    fb->width = mbox[5];
    fb->height = mbox[33];
    fb->isrgb = mbox[24];
    return 0;
  }

  return 1;
}
