#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  int size = 0;
  char *str = NULL;
  va_list ap;
  /* Determine required size */
  va_start(ap, fmt);
  size = vsnprintf(str, size, fmt, ap);
  va_end(ap);
  ++size; // for '\0'
  /* Print output to str */
  // str = malloc(size); // not implemented
  // va_start(ap, fmt);
  // size = vsnprintf(str, size, fmt, ap);
  // va_end(ap);
  // putstr(str);
  char buf[1024];
  va_start(ap, fmt);
  size = vsnprintf(buf, size, fmt, ap);
  va_end(ap);
  putstr(buf);
  return size;
}

// itoa function, for temporary use
void reverse(char *s, int len) {
  for (int i = 0; i < len / 2; i++) {
    char tmp = s[len - i - 1];
    s[len - i - 1] = s[i];
    s[i] = tmp;
  }
}
int itoa(const int num, char *s) {
  if (num == 0) {
    s[0] = '0';
    s[1] = '\0';
    return 1;
  }
  int len = 0;
  int neg = (num < 0) ? 1 : 0;
  long tmp = (num < 0) ? -(long)num : num;
  while (tmp) {
    s[len++] = '0' + (tmp % 10);
    tmp /= 10;
  }
  if (neg)  s[len++] = '-';
  s[len] = '\0';
  reverse(s, len);
  return len;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return vsnprintf(out, -1, fmt, ap);
  // size_t fmt_ptr = 0;
  // int d;
  // char *s;
  // int size = 0;

  // // clear out
  // *out = '\0';
  // while (fmt[fmt_ptr]) {
  //   if (fmt[fmt_ptr] == '%') {
  //     fmt_ptr++;
  //     switch (fmt[fmt_ptr++]) {
  //     case '%':
  //       out[size++] = '%';
  //       break;
  //     case 's':
  //       s = va_arg(ap, char *);
  //       size += strlen(s);
  //       strcat(out, s);
  //       break;
  //     case 'd':
  //       d = va_arg(ap, int);
  //       // convert int to string
  //       char dstr[16];
  //       size += itoa(d, dstr);
  //       strcat(out, dstr);
  //       break;
  //     }
  //   }
  //   else {
  //     out[size++] = fmt[fmt_ptr++];
  //   }
  //   out[size] = '\0';
  // }
  // return size;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int size = vsprintf(out, fmt, ap);
  va_end(ap);
  return size;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int size = vsnprintf(out, n, fmt, ap);
  va_end(ap);
  return size;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  // panic("Not implemented");
  size_t fmt_ptr = 0;
  int d;
  char *s;
  int size = 0;

  // clear out
  *out = '\0';
  while (fmt[fmt_ptr]) {
    if (fmt[fmt_ptr] == '%') {
      fmt_ptr++;
      switch (fmt[fmt_ptr++]) {
      case '%':
        if (size < n) out[size] = '%';
        ++size;
        break;
      case 's':
        s = va_arg(ap, char *);
        // size += strlen(s);
        // strcat(out, s);
        for (int i = 0; i < strlen(s); ++i) {
          if (size < n) {
            out[size] = s[i];
          }
          ++size;
        }
        break;
      case 'd':
        d = va_arg(ap, int);
        // convert int to string
        char dstr[16];
        // size += itoa(d, dstr);
        // strcat(out, dstr);
        for (int i = 0; i < itoa(d, dstr); ++i) {
          if (size < n) {
            out[size] = dstr[i];
          }
          ++size;
        }
        break;
      }
    }
    else {
      if (size < n) {
        out[size] = fmt[fmt_ptr++];
      }
      ++size;
    }
    if (size >= n) {
      out[n - 1] = '\0';
    }
    else {
      out[size] = '\0';
    }
  }
  return size;
}

#endif
