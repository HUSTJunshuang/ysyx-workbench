#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#include <stdbool.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

#define PRINTF_NTOA_BUFFER_SIZE 32U

// internal flags definitions
#define FLAG_ZEROPAD    (1U <<  0U)
#define FLAG_LEFT       (1U <<  1U)
#define FLAG_SIGN       (1U <<  2U)
#define FLAG_SPACE      (1U <<  3U)
#define FLAG_PREFIX     (1U <<  4U)
#define FLAG_UPPERCASE  (1U <<  5U)
#define FLAG_CHAR       (1U <<  6U)
#define FLAG_SHORT      (1U <<  7U)
#define FLAG_LONG       (1U <<  8U)
#define FLAG_LONG_LONG  (1U <<  9U)
#define FLAG_PRECISION  (1U << 10U)

/* --------------- internal functions for output redirect --------------- */
// output function type, for output redirect
typedef void (*out_fct_type)(char character, void *buffer, size_t idx, size_t maxlen);

// internal buffer output, redirect to a buffer
static inline void _out_buffer(char character, void *buffer, size_t idx, size_t maxlen) {
  if (idx < maxlen) {
    ((char *)buffer)[idx] = character;
  }
}
// internal null output, redirect to null
static inline void _out_null(char character, void *buffer, size_t idx, size_t maxlen) {
  (void)character; (void)buffer; (void)idx; (void)maxlen;
}
// internal putch wrapper, redirect to serial output
static inline void _out_char(char character, void *buffer, size_t idx, size_t maxlen) {
  (void)buffer; (void)idx; (void)maxlen;
  if (character) {
    putch(character);
  }
}

/* --------------- internal functions for format process --------------- */
static inline bool _is_digit(char ch) {
  return (ch >= '0') && (ch <= '9');
}

// static size_t _out_reverse(out_fct_type out, char *buffer, size_t idx, size_t maxlen, const char *buf, size_t len, unsigned int width, unsigned int flags) {
static size_t _out_reverse(out_fct_type out, char *buffer, size_t idx, size_t maxlen, const char *buf, size_t len) {
  // const size_t start_idx = idx;
  
  // // determine padding character
  // char pad = (flags & FLAG_ZEROPAD) ? '0' : ' ';
  // // pre-padding
  // if (!(flags & FLAG_LEFT)) {
  //   for (size_t i = len; i < width; ++i) {
  //     out(pad, buffer, idx++, maxlen);
  //   }
  // }
  // reverse
  while (len) {
    out(buf[--len], buffer, idx++, maxlen);
  }
  // // post-padding
  // if (flags & FLAG_LEFT) {
  //   while (idx - start_idx < width) {
  //     out(pad, buffer, idx++, maxlen);
  //   }
  // }

  return idx;
}

static size_t _ntoa_format(out_fct_type out, char *buffer, size_t idx, size_t maxlen, char *buf, size_t len, bool neg, unsigned int base, unsigned int prec, unsigned int width, unsigned int flags) {
  const size_t start_idx = idx;
  // add sign or space, only for signed number
  if (width && (neg || (flags & (FLAG_SIGN | FLAG_SPACE)))) {
    --width;
  }
  if (neg) {
      out('-', buffer, idx++, maxlen);
    }
    else if (flags & FLAG_SIGN) {
      out('+', buffer, idx++, maxlen);
    }
    else if (flags & FLAG_SPACE) {
      out(' ', buffer, idx++, maxlen);
    }
  // add prefix, only for unsigned number
  if (flags & FLAG_PREFIX) {
    if (base == 16U) {
      out('0', buffer, idx++, maxlen);
      out((flags & FLAG_UPPERCASE) ? 'X' : 'x', buffer, idx++, maxlen);
      width -= 2;
    }
    else if (base == 8U) {
      if (buf[len - 1] != '0') {
        out('0', buffer, idx++, maxlen);
        --width;
      }
    }
  }
  // precision pre-padding
  if (flags & FLAG_PRECISION) {
    for (; len < prec; ++len) {
      out('0', buffer, idx++, maxlen);
    }
  }
  // width pre-padding
  char pad = (flags & FLAG_ZEROPAD) ? '0' : ' ';
  if (!(flags & FLAG_LEFT)) {
    for (size_t i = len; i < width; ++i) {
      out(pad, buffer, idx++, maxlen);
    }
  }
  // reverse
  idx = _out_reverse(out, buffer, idx, maxlen, buf, len);
  // post-padding
  if (flags & FLAG_LEFT) {
    while (idx - start_idx < width) {
      out(pad, buffer, idx++, maxlen);
    }
  }
  return idx;
}

static size_t _ntoa_long(out_fct_type out, char *buffer, size_t idx, size_t maxlen, unsigned long value, bool neg, unsigned int base, unsigned int prec, unsigned int width, unsigned int flags) {
  char buf[PRINTF_NTOA_BUFFER_SIZE];
  size_t len = 0U;
  // no prefix for zero
  if (!value) {
    flags &= ~FLAG_PREFIX;
  }
  // write if precision != 0 && value != 0
  if (true) {
    do {
      const char digit = (char)(value % base);
      buf[len++] = (digit < 10) ? '0' + digit : (flags & FLAG_UPPERCASE ? 'A' : 'a') + digit - 10;
      value /= base;
    } while (value && (len < PRINTF_NTOA_BUFFER_SIZE));
  }
  return _ntoa_format(out, buffer, idx, maxlen, buf, len, neg, base, prec, width, flags);
}

// internal vsnprintf
static int _vsnprintf(out_fct_type out, char *buffer, size_t maxlen, const char *fmt, va_list ap) {
  unsigned int flags, width, precision, n;
  size_t idx = 0U;

  if (!buffer) {
    out = _out_null;
  }

  while (*fmt) {
    /* normal string */
    if (*fmt != '%') {
      out(*fmt, buffer, idx++, maxlen);
      ++fmt;
      continue;
    }
    /* format characters */
    ++fmt;
    // flag characters
    flags = 0U;
    do {
      switch(*fmt) {
        case '0': flags |= FLAG_ZEROPAD ; ++fmt;  n = 1U; break;
        case '-': flags |= FLAG_LEFT    ; ++fmt;  n = 1U; break;
        case '+': flags |= FLAG_SIGN    ; ++fmt;  n = 1U; break;
        case ' ': flags |= FLAG_SPACE   ; ++fmt;  n = 1U; break;
        case '#': flags |= FLAG_PREFIX  ; ++fmt;  n = 1U; break;
        default :                                 n = 0U; break;
      }
    } while(n);
    // filed width
    width = 0U;
    if (_is_digit(*fmt)) {
      putstr("entered width\n");
      width = atoi(fmt);
    }
    else if (*fmt == '*') {
      int w = va_arg(ap, int);
      if (w < 0) {
        flags |= FLAG_LEFT;
        width = (unsigned int)-w;
      }
      else {
        width = (unsigned int)w;
      }
      ++fmt;
    }
    // precision
    precision = 0U;
    if (*fmt == '.') {
      flags |= FLAG_PRECISION;
      ++fmt;
      if (_is_digit(*fmt)) {
        precision = atoi(fmt);
      }
      else if (*fmt == '*') {
        int prec = va_arg(ap, int);
        precision = prec > 0 ? (unsigned int)prec : 0U;
        ++fmt;
      }
    }
    // length modifier
    switch (*fmt) {
      case 'h':
        flags |= FLAG_SHORT;
        ++fmt;
        if (*fmt == 'h') {
          flags |= FLAG_CHAR;
          ++fmt;
        }
        break;
      case 'l':
        flags |= FLAG_LONG;
        ++fmt;
        if (*fmt == 'l') {
          flags |= FLAG_LONG_LONG;
          ++fmt;
        }
        break;
      case 'q':
        flags |= FLAG_LONG_LONG;
        ++fmt;
        break;
      // TODO add more
      default:
        break;
    }
    // conversion specifiers
    switch (*fmt) {
      case 'd': case 'i':
      case 'o': case 'u': case 'x': case 'X': {
        unsigned int base;
        if (*fmt == 'x' || *fmt == 'X') {
          base = 16U;
        }
        else if (*fmt == 'o') {
          base = 8U;
        }
        else {
          base = 10U;
          flags &= ~FLAG_PREFIX;
        }
        // uppercase
        if (*fmt == 'X') {
          flags |= FLAG_UPPERCASE;
        }
        // sign and space only available for signed decimal
        if ((*fmt != 'i') && (*fmt != 'd')) {
          flags &= ~(FLAG_SIGN | FLAG_SPACE);
        }
        // ignore zero pad when given precision
        if (flags & FLAG_PRECISION) {
          flags &= ~FLAG_ZEROPAD;
        }
        // string to integer
        if ((*fmt == 'i') || (*fmt == 'd')) {
          // signed
          if (flags & FLAG_LONG_LONG) {
            // long long val = va_arg(ap, long long);
            // TODO string to long long
          }
          else if (flags & FLAG_LONG) {
            long val = va_arg(ap, long);
            idx = _ntoa_long(out, buffer, idx, maxlen, (unsigned long)(val > 0 ? val : 0 - val), val < 0, base, precision, width, flags);
          }
          else {
            int val = (flags & FLAG_CHAR) ? (char)va_arg(ap, int) :
                      (flags & FLAG_SHORT) ? (short int)va_arg(ap, int) : va_arg(ap, int);
            idx = _ntoa_long(out, buffer, idx, maxlen, (unsigned long)(val > 0 ? val : 0UL - val), val < 0, base, precision, width, flags);
          }
        }
        else {
          // unsigned
          if (flags & FLAG_LONG_LONG) {
            // TODO string to uint
          }
          else if (flags & FLAG_LONG) {
            idx = _ntoa_long(out, buffer, idx, maxlen, va_arg(ap, unsigned long), false, base, precision, width, flags);
          }
          else {
            unsigned int val = (flags & FLAG_CHAR) ? (unsigned char)va_arg(ap, unsigned int) :
                                (flags & FLAG_SHORT) ? (unsigned short int)va_arg(ap, unsigned int) : va_arg(ap, unsigned int);
            idx = _ntoa_long(out, buffer, idx, maxlen, val, false, base, precision, width, flags);
          }
        }
        ++fmt;
        break;
      }
      // TODO float not implemented
      case 'c': {
        unsigned int pad = 1U;
        // pre-padding
        if (!(flags & FLAG_LEFT)) {
          while (pad++ < width) {
            out(' ', buffer, idx++, maxlen);
          }
        }
        // print char
        out((char)va_arg(ap, int), buffer, idx, maxlen);
        // post-padding
        if (flags & FLAG_LEFT) {
          while (pad++ < width) {
            out(' ', buffer, idx++, maxlen);
          }
        }
        ++fmt;
        break;
      }
      case 's': {
        char *s = va_arg(ap, char *);
        unsigned int len = strlen(s);
        // pre-padding
        if (flags & FLAG_PRECISION) {
          len = (len < precision) ? len : precision;
        }
        if (!(flags & FLAG_LEFT)) {
          while (len++ < width) {
            out(' ', buffer, idx++, maxlen);
          }
        }
        // print string
        while ((*s != '\0') && (!(flags & FLAG_PRECISION) || precision--)) {
          out(*(s++), buffer, idx++, maxlen);
        }
        // post-padding
        if (flags & FLAG_LEFT) {
          while (len++ < width) {
            out(' ', buffer, idx++, maxlen);
          }
        }
        ++fmt;
        break;
      }
      // TODO add more
      case '%': {
        out('%', buffer, idx++, maxlen);
        ++fmt;
        break;
      }
      default: {
        out(*fmt, buffer, idx++, maxlen);
        ++fmt;
      }
    }
  }
  // overflow string truncation
  out('\0', buffer, idx < maxlen ? idx : maxlen - 1U, maxlen);
  return (int)idx;
}

/* --------------- external function interfaces of stdio --------------- */
int printf(const char *fmt, ...) {
  // int size = 0;
  // char *str = NULL;
  // va_list ap;
  // /* Determine required size */
  // va_start(ap, fmt);
  // size = vsnprintf(str, size, fmt, ap);
  // va_end(ap);
  // ++size; // for '\0'
  // /* Print output to str */
  // // str = malloc(size); // not implemented
  // // va_start(ap, fmt);
  // // size = vsnprintf(str, size, fmt, ap);
  // // va_end(ap);
  // // putstr(str);
  // char buf[1024];
  // va_start(ap, fmt);
  // size = vsnprintf(buf, size, fmt, ap);
  // va_end(ap);
  // putstr(buf);
  va_list ap;
  va_start(ap, fmt);
  char buffer[1];
  int size = _vsnprintf(_out_char, buffer, -1, fmt, ap);
  return size;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return vsnprintf(out, -1, fmt, ap);
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
  return _vsnprintf(_out_buffer, out, n, fmt, ap);
}

#endif
