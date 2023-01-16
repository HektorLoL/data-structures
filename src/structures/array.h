/* HELP:

   ** Function naming notation:
   1. the function name should tell pretty clearly what it does
   2. functions that are not supposed to be used outside have 
   two underlines (__) surrounding their names. e.g: "int __dont_use__()".
   3. functions that can be used but are not really from the array
   specs algorithms functions, like an about function or an error
   utilities functioon
	
   ** TODO:
   // remove_values
   // sort_array
   
*/







#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "terminal_macros.h"







#ifndef foreach
#  define foreach(var, length) for (int var = 0; var < length; var++) 
#endif

#ifndef MY_MATH
#define math_min(a, b) (a > b ? b : a)
#define math_max(a, b) (a > b ? a : b)
#define math_ceil(x) ((x) - ((int)x) <= 0 ? ((int)x) : ((int)x) + 1)
#endif




// print an array with a c defined type (not struct, union or enum)
#define print_typed_arr(array, format, type) ({ \
	printf("["); \
	foreach(i, array->length) \
	{ \
		printf(format, ((type *)array->data)[i]); \
		if (i + 1 != array->length) \
			printf(", "); \
	} \
	printf("]"); \
})

#define print_any_array(array, format, format_parameters...) ({ \
	printf("["); \
	foreach(i, array->length) \
	{ \
		printf(format, format_parameters); \
		if (i + 1 != array->length) \
			printf(", "); \
	} \
	printf("]"); \
})




#define print_bool(boolean) printf("%s", boolean ? "TRUE" : "FALSE");

#define set_value(array, index, value) set_values(array, index, value, 1)

#define insert_value(array, index, value) insert_values(array, index, value, 1)

#define get_element(array, type, index) ((type *)array->data)[index]

// the item->size of the returned index is the element you are looking for
// e.g ->  __get_data_index(data, arr, i)
#define __get_data_index(data, arr, index) (data + arr->item_size * (index))







const extern int PLEASE_NO_ERRORS;



typedef struct _Array Array;
typedef void (*Clearer)(Array *arr);
typedef bool (*Comparator)(Array *arr, uint32_t index, const void *search_item);





struct _Array
{
	uint32_t length;
	void *data;
	
	size_t item_size;
	bool isTerminated;
	Clearer clear_func;
	Comparator compare_func;
};





// I HAVE NO IDEA WHY I HAVE TO PUT STATIC IN AN INLINE FUNCTION IN THE HEADER FILE
// BUT IT WORKS AND IS AVALIABLE TO OTHER FILES WHICH IS WHAT I WANTED.
// WIHOUT THE STATIC THE FUNCTION FOR SOME REASON CANNOT BE ACCESSED
// IN THE SOURCE FILE (array.c) IDK WHY. (AND ACCUALLY ANY OTHER FILE)
//
// this function is not recommended as it is just used inside
// this array specs functions. It is complicated an there is
// a much easier and simpler alternative: the "get_element" macro.
static inline char *get_usable_data(Array *arr, uint32_t index)
{
	// characters have only one byte, because of that, using the
	// item size we can jump the right amout of bytes to get the value
	return ((char *)arr->data) + (index * arr->item_size);
}

// JUST REALIZED I HAVE TO PUT STATIC IN EVERY INLINE FUNCTION
// FOR IT TO BE GLOBAL.
static inline void set_clearer(Array *arr, Clearer clear_func)
{
	arr->clear_func = clear_func;
}

static inline void set_comparator(Array *arr, Comparator compare_func)
{
	arr->compare_func = compare_func;
}

static inline int ceil_(float x)
{
    int y = (int)x;
    
    if ( (float)x - (float)y <= 0)
        return y;
    else
        return y + 1;    
}







_Noreturn void __array_error__(int code, char *callback_name);
void __array_error(int code, char *callback_name);

void __print_array_specs();

void set_values(Array *arr, uint32_t index, const void *values, uint32_t length);
void insert_values(Array *arr, uint32_t index, const void *values, uint32_t length);
Array *new_array(uint32_t length, size_t item_size, bool isTerminated);
Array *copy_array(Array *arr);
void *free_array(Array *arr, bool only_structre);
void reset_array(Array *arr);
int linear_search_value(Array *arr, const void *value); // O(n)

// this function is not really from the spec is just an example
// of a compare function. it was made by me to test the linear 
// search and ended up staying.
bool int_compare(Array *arr, uint32_t index, const void *search_item);

#endif // ARRAY_H