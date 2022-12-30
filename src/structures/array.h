#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "terminal_macros.h"

// #define PLEASE_NO_ERRORS // when defined no errors will be printed

#ifndef foreach
#  define foreach(var, length) for (int var = 0; var < length; var++) 
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

#define set_value(array, index, value) set_values(array, index, value, 1)

#define insert_value(array, index, value) insert_values(array, index, value, 1)

#define get_element(array, type, index) ((type *)array->data)[index]

#define __get_data_index__(data, arr, index) (data + arr->item_size * index)

typedef struct _Array Array;
typedef void (*Clearer)(Array *arr);

struct _Array
{
	uint16_t length;
	void *data;
	
	size_t item_size;
	bool isTerminated;
	Clearer clear_func;
};

#ifdef PLEASE_NO_ERRORS
_Noreturn void __array_error(int code, char *callback_name);
#else
void __array_error(int code, char *callback_name);
#endif

void __print_array_specs__();

inline void set_clearer(Array *arr, Clearer clear_func);
void set_values(Array *arr, uint32_t index, const void *values, uint32_t length);
void insert_values(Array *arr, uint32_t index, const void *values, uint32_t length);
Array *new_array(uint16_t length, size_t item_size, bool isTerminated);
Array *copy_array(Array *arr);
void *free_array(Array *arr, bool only_structre);
void reset_array(Array *arr);

// binary_search_array  O(log n) [faster but needs to be sorted]
// linear_search_array  O(n)
// remove_values
// sort_array

#endif // ARRAY_H