/**
 * This header file is old and was made for training
 * After ome time working on it I reliazed that the
 * array structure wasn't made for anything but to print
 * items, so I stopped the development of this and started
 * a new array.h.
 * */


// IMPORTANT: you can't include both commonarray.h and array.h because they 
// have similar function names
#ifndef ARRAY_H
#define ARRAY_H

#include "structs.h"

// a useful header for making a loop, so you don't waste time
#ifndef foreach
#  define foreach(var, length) for (int var = 0; var < length; var++)
#endif

// possible types (made for making the printing easier)
typedef enum ArrayT
{
    CHAR, INT,   // signed numbers
    FLOAT,          // floating point numbers
    BOOL,           // booleans (true/else)
    STRING, OTHER, // pointer types
} ArrayT;

// Array type could also be defined like this: (which would be better)
typedef struct _Array Array;
typedef void (*Printer)(Array *arr);

struct _Array
{
    uint32_t length;
    void *list;
    
    ArrayT type;
    char *str_type;

    Printer printing_func;
};

// you shouldn't use this function directly
void common_printing(Array *arr);

void set_printing(Array *arr, Printer printing_func);
void set_typeID(Array *arr, const char *type_name);
void print_list(Array *arr);

Array *new_array(uint32_t length, ArrayT type, size_t type_size);

#endif // ARRAY_H