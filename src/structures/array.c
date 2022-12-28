#include "array.h"

static inline char *get_usable_data(Array *arr, uint16_t index)
{
	// characters have only one byte, because of that, using the
	// item size we can jump the right amout of bytes to get the value
	return ((char *)arr->data) + (index * arr->item_size);
}

_Noreturn void array_error(int code, char *callback_name)
{
	printf(COLOR_YELLOW "{Code %d} ", code);

	if (callback_name == NULL)
		printf("Array.Error occured::\n\t");
	else 
		printf("Array.Errror occured in function %s(...)::\n\t", callback_name);

	printf(COLOR_RED);
	switch(code)
	{
		case 1:
			printf("The desired index is larger than the array length itself.\n");
		case 2:
			printf("The inserted content is larger than the array length itself.\n");
	}

	printf(COLOR_NONE);
	fflush(stdout);

	exit(EXIT_FAILURE);
}

Array *new_array(uint16_t length, size_t item_size, bool isTerminated)
{
	Array *arr = malloc(sizeof(Array));

	arr->length = length;
	arr->item_size = item_size;
	arr->data = malloc(length * item_size);

	// cast array list into a character array so we can accually use it
	char *usable = get_usable_data(arr, 0);

	// clears the array by defaylt
	foreach(i, arr->length)
		foreach(j, item_size)
			usable[(i * item_size)+j] = 0;

	// if terminates with a null character
	if (isTerminated)
	{
		arr->data = realloc(arr->data, (length + 1) * item_size);
		memcpy((void *)(usable + length), "\0", sizeof(char) * 1);
		arr->isTerminated = true;
	}

	return arr;
}

void insert_values(Array *arr, uint32_t index, const void *values, uint32_t length)
{
	if (index+1 > arr->length)
		array_error(1, "insert_values");
	else if (index + length > arr->length)
		array_error(2, "insert_values");

	char *usable_data = get_usable_data(arr, 0);
	const char *usable_values = values;

	for (int i = 0; i < length; i++)
		memcpy(
			(void *)(usable_data + arr->item_size * (i + index)),
			(void *)(usable_values + arr->item_size * i),
			arr->item_size
		);
}

Array *copy_array(Array *arr)
{
	uint32_t length = arr->length;
	size_t item_size = arr->item_size;
	char *data = get_usable_data(arr, 0);

	Array *copy = new_array(length, item_size, arr->isTerminated);

	foreach(i, length)
	{
		insert_values(copy, 0, data, length);
	}

	return copy;
}

void *free_array(Array *arr, bool only_structre)
{
	if (only_structre)
	{
		void *data = arr->data;
		free(arr);
		return data;
	}
}
