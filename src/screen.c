#include "screen.h"
#include "font.h"
#include "framebuffer.h"
#include "mbox.h"
#include "mm.h"
#include "util.h"

static const pixel_t WHITE = {0xFF, 0xFF, 0xFF};
static const pixel_t BLACK = {0x00, 0x00, 0x00};

void init_screen(void) {
  // try till we succeed
  while (init_framebuffer())
    ;

  // clear screen
  for (uint32_t i = 0; i < fbinfo.height; ++i) {
    for (uint32_t j = 0; j < fbinfo.width; ++j)
      write_pixel(j, i, &BLACK);
  }
}

void write_pixel(uint32_t x, uint32_t y, const pixel_t *pixel) {
  uint8_t *loc = fbinfo.buf + y * fbinfo.pitch + x * BYTES_PER_PIXEL;
  memcpy((char *)loc, (const char *)pixel, BYTES_PER_PIXEL);
}

void screen_putc(const char c) {
  uint8_t w, h, mask;
  const uint8_t *bmp = font(c);
  uint32_t i, num_rows = fbinfo.height / CHAR_HEIGHT;

  // shift everything up one row
  if (fbinfo.chars_y >= num_rows) {
    // copy a whole character row into the one above it
    for (i = 0; i < num_rows - 1; ++i)
      memcpy(fbinfo.buf + fbinfo.pitch * i * CHAR_HEIGHT,
             fbinfo.buf + fbinfo.pitch * (i + 1) * CHAR_HEIGHT,
             fbinfo.buf + fbinfo.pitch);

    // zero out the last row
    memzero(fbinfo.buf + fbinfo.pitch * i * CHAR_HEIGHT,
            fbinfo.pitch * CHAR_HEIGHT);

    fbinfo.chars_y--;
  }

  if (c == '\n') {
    fbinfo.chars_x = 0;
    fbinfo.chars_y++;
    return;
  }

  for (w = 0; w < CHAR_WIDTH; ++w) {
    for (h = 0; h < CHAR_HEIGHT; ++h) {
      mask = 1 << (w);
      if (bmp[h] & mask)
        write_pixel(fbinfo.chars_x * CHAR_WIDTH + w,
                    fbinfo.chars_x * CHAR_HEIGHT + h, &WHITE);
      else
        write_pixel(fbinfo.chars_x * CHAR_WIDTH + w,
                    fbinfo.chars_x * CHAR_HEIGHT + h, &BLACK);
    }
  }

  fbinfo.chars_x++;
  if (fbinfo.chars_x > fbinfo.chars_width) {
    fbinfo.chars_x = 0;
    fbinfo.chars_y++;
  }
}

void screen_print(const char *str) {
  while (str) {
    screen_putc(*str);
    str++;
  }
}
