
#ifndef _H_MACROS
#define _H_MACROS

#include <avr/io.h>

// I/O Access
#define BIT_T(p,b)                (P ## p ## b)
#define PORT_T(p,b)               (PORT ## p)
#define PIN_T(p,b)                (PORT ## p ## b)
#define DDR_T(p,b)                (DDR ## p)
#define BITD_T(p,b)               (DD ## p ## b)

#define BIT(...) BIT_T(__VA_ARGS__)
#define PORT(...) PORT_T(__VA_ARGS__)
#define PIN(...) PIN_T(__VA_ARGS__)
#define DDR(...) DDR_T(__VA_ARGS__)
#define BITD(...) BITD_T(__VA_ARGS__)

#define io_set_high(a, b) (a |= _BV(b))
#define io_set_low(a, b) (a &= ~_BV(b))
#define io_toggle(a, b)   (a ^= _BV(b))

#endif
