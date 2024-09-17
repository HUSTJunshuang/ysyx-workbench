#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

// itoa function, for temporary use
void reverse(char *s, int len) {
  for (int i = 0; i < len / 2 - 1; i++) {
    char tmp = s[len - i - 1];
    s[len - i - 1] = s[i];
    s[i] = tmp;
  }
}
int itoa(int num, char *s) {
  int len = 0;
  while (num) {
    s[len++] = '0' + (num % 10);
    num /= 10;
  }
  s[len] = '\0';
  reverse(s, len);
  return len;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  size_t fmt_ptr = 0;
  int d;
  char *s;
  int size = 0;

  // clear out
  *out = '\0';
  while (fmt[fmt_ptr]) {
    if (fmt[fmt_ptr++] == '%') {
      switch (fmt[fmt_ptr++]) {
      case '%':
        out[size++] = '%';
        break;
      case 's':
        s = va_arg(ap, char *);
        size += strlen(s);
        strcat(out, s);
        break;
      case 'd':
        d = va_arg(ap, int);
        // convert int to string
        char dstr[16];
        size += itoa(d, dstr);
        strcat(out, dstr);
        break;
      }
    }
    else {
      out[size++] = fmt[fmt_ptr++];
    }
    out[size] = '\0';
  }
  return size;
  // panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int size = vsprintf(out, fmt, ap);
  va_end(ap);
  return size;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
