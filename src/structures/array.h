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

#define insert_value(array, index, value) insert_values(array, index, value, 1)

typedef struct _Array Array;

struct _Array
{
	uint16_t length;
	void *data;
	
	size_t item_size;
	bool isTerminated;
};

_Noreturn void array_error(int code, char *callback_name);
void insert_values(Array *arr, uint32_t index, const void *values, uint32_t length);
Array *new_array(uint16_t length, size_t item_size, bool isTerminated);
Array *copy_array(Array *arr);
void *free_array(Array *arr, bool only_structre);

#endif // ARRAY_H