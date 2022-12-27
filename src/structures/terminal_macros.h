#ifndef TERMINAL_MACROS_H
#define TERMINAL_MACROS_H

#define COLOR_NONE    COLOR(0)
#define COLOR_BLACK   COLOR(30)
#define COLOR_RED     COLOR(31)
#define COLOR_GREEN   COLOR(32)
#define COLOR_YELLOW  COLOR(33)
#define COLOR_BLUE    COLOR(34)
#define COLOR_MAGENTA COLOR(35)
#define COLOR_CYAN    COLOR(36)
#define COLOR_WHITE   COLOR(37)

#define UP    "A"
#define DOWN  "B"
#define RIGHT "C"
#define LEFT  "D"

// expands macros as well
#define str(a) #a
#define xstr(a) str(a)

#define COLOR(n)             "\x1B[" xstr(n) "m"
#define GO(n, dir)           "\x1B[" xstr(n) dir
#define DELETE               "\x1B[2K"
#define DELETE_FROM_TO_START "\x1B[1K"
#define DELETE_FROM_TO_END   "\x1B[0K"

#endif // TERMINAL_MACROS_H