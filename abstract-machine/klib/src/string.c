#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  // if (s == NULL)  return 0;
  size_t len = 0;
  while (s[len] != '\0') {
    len++;
  }
  return len;
}

char *strcpy(char *dst, const char *src) {
  // CHECK need assert or not
  // if (src == NULL)  return dst;
  size_t len = 0;
  while (src[len] != '\0') {
    dst[len] = src[len];
    len++;
  }
  // dst[len] = '\0';
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dst[i] = src[i];
  }
  for (; i < n; i++) {
    dst[i] = '\0';
  }
  return dst;
}

char *strcat(char *dst, const char *src) {
  size_t dst_len = strlen(dst);
  size_t src_ptr = 0;
  while (src[src_ptr] != '\0') {
    dst[dst_len + src_ptr] = src[src_ptr];
    src_ptr++;
  }
  dst[dst_len + src_ptr] = '\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  size_t cmp_len = 0;
  int ascii_diff = s1[cmp_len] - s2[cmp_len];
  while (ascii_diff == 0 && s1[cmp_len] != '\0') {
    cmp_len++;
    ascii_diff = s1[cmp_len] - s2[cmp_len];
  }
  return ascii_diff;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  int ascii_diff = 0;
  for (size_t i = 0; i < n; i++) {
    ascii_diff = s1[i] - s2[i];
    if (s1[i] == '\0' || ascii_diff != 0) {
      break;
    }
  }
  return ascii_diff;
}

// TODO use max length type instead of char to exploit the data width of CPU's reg(word length)
void *memset(void *s, int c, size_t n) {
  for (size_t i = 0; i < n; i++) {
    ((char *)s)[i] = c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  if (dst < src) {
    // dst is in front of src, use forward copy
    for (size_t i = 0; i < n; i++) {
      ((char *)dst)[i] = ((char *)src)[i];
    }
  }
  else {
    // dst is at back of src, use backward copy
    for (size_t i = n; i != 0; i--) {
      ((char *)dst)[i - 1] = ((char *)src)[i - 1];
    }
  }
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  for (size_t i = 0; i < n; i++) {
    ((char *)out)[i] = ((char *)in)[i];
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  int ascii_diff = 0;
  for (size_t i = 0; i < n; i++) {
    ascii_diff = ((char *)s1)[i] - ((char *)s2)[i];
    if (ascii_diff != 0) {
      break;
    }
  }
  return ascii_diff;
}

#endif
