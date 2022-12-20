#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
// #include <unistd.h>

#define COLOR_NONE    0
#define COLOR_BLACK   30
#define COLOR_RED     31
#define COLOR_GREEN   32
#define COLOR_YELLOW  33
#define COLOR_BLUE    34
#define COLOR_MAGENTA 35
#define COLOR_CYAN    36
#define COLOR_WHITE   37

#define UP    "A"
#define DOWN  "B"
#define RIGHT "C"
#define LEFT  "D"

// expands macros as well
#define str(a) #a
#define xstr(a) str(a)

#define COLOR(n)   "\x1B[" xstr(n) "m"
#define GO(n, dir) "\x1B[" xstr(n) dir
#define DELETE              "\x1B[2K"
#define DELETE_FROM_TO_START   "\x1B[1K"
#define DELETE_FROM_TO_END     "\x1B[0K"

#endif // STRUCTS_H