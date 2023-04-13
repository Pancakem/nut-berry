#ifndef _UTIL_H_
#define _UTIL_H_

extern int getcurrentEL(void);
void bin_to_hex(char *val, unsigned int d);
unsigned int strlen(const char *str);
void strcat(char *dest, const char *src);
int strcmp(const char *src1, const char *src2);
int my_sprintf(char *buf, const char *fmt, ...);
void memcpy(char *dest, const char *src, unsigned int len);
void putc(void *p, char c);

#define NULL (void *)0

#endif
