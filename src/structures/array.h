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

// the array type
typedef struct Array
{
    uint32_t length;
    void *list;
    
    ArrayT type;
    char *str_type;

    void (*printing_func)(struct Array *arr);
} Array;

// the definition of a function to print arrays, so you
// dont miss anything when passing your own
typedef void (*Printer)(Array *arr);

// you shouldn't use this function directly
void common_printing(Array *arr);

void set_printing(Array *arr, Printer printing_func);
void set_typeID(Array *arr, const char *type_name);
void print_list(Array *arr);

Array *new_array(uint32_t length, ArrayT type, size_t type_size);

#endif // ARRAY_H