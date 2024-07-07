#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8

typedef struct {
  uint8_t red, green, blue;
} pixel_t;

void init_screen(void);
void write_pixel(uint32_t x, uint32_t y, const pixel_t *pixel);
void screen_putc(char c);
void screen_print(const char *str);
#endif
