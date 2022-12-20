#ifndef ARRAY_H
#define ARRAY_H

#include "structs.h"

#define foreach(var, length) for (int var = 0; var < length; var++)

// the formats are in order of ArrayT
#define STR_BOOL_TRUE  "true"
#define STR_BOOL_FALSE "false"

#define WITH_PERCENTAGE(format) "%" format ", "
#define FORMATS              \
    WITH_PERCENTAGE("c"),    \
    WITH_PERCENTAGE("d"),    \
    WITH_PERCENTAGE("c"),    \
    WITH_PERCENTAGE("u"),    \
    WITH_PERCENTAGE("f"),    \
    WITH_PERCENTAGE("s"),    \
    WITH_PERCENTAGE("p")
//  No OTHER type

typedef enum ArrayT
{
    SCHAR,  SINT,
    UCHAR,  UINT,

    FLOAT,

    BOOL,

    POINTER, OTHER,
} ArrayT;

typedef unsigned char unschar;
typedef unsigned int unsint;

typedef struct List
{
    signed   char      *schar;
    // signed   short     *sshort;
    signed   int       *sint;
    // signed   long      *slong;
    // signed   long long *slonglong;
    
    unsigned char      *uchar;
    // unsigned short     *ushort;
    unsigned int       *uint;
    // unsigned long      *ulong;
    // unsigned long long *ulonglong;
    
    float              *float_;
    // double             *double_; 
    // long double        *longdouble;
    
    bool               *bool_;
    
    void               **pointer;
    void               **other;
} List;

typedef struct Array
{
    size_t length;
    ArrayT type;
    List list;
    void (*printing_func)(struct Array *arr);
} Array;

typedef void (*Printer)(Array *arr);

void common_printing(Array *arr);
void set_printing(Array *arr, Printer printing_func);
void *get_list(Array *arr);
void print_list(Array *arr);
Array *new_array(const size_t length, const ArrayT type);

#endif // ARRAY_H