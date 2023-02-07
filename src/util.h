#ifndef _UTIL_H_
#define _UTIL_H_

void bin_to_hex(char *val, unsigned int d);
unsigned int strlen(const char *str);
void strcat(char *dest, const char *src);
int strcmp(const char *src1, const char *src2);

void memcpy(char *dest, const char *src, unsigned int len);

#endif
