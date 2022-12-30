#include "array.h"
#include <string.h>

static inline char *get_usable_data(Array *arr, uint16_t index)
{
	// characters have only one byte, because of that, using the
	// item size we can jump the right amout of bytes to get the value
	return ((char *)arr->data) + (index * arr->item_size);
}

_Noreturn void __array_error(int code, char *callback_name)
{
	#ifdef PLEASE_NO_ERROS
	return;
	#endif

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

void __print_array_specs__()
{
	printf("\n"
		"Array speed: {\n"
		"\tAccess: " COLOR_CYAN "O(1)" COLOR_NONE ",\n"
		"\tSet   : " COLOR_CYAN "O(1)" COLOR_NONE ",\n"
		"\tSearch: " COLOR_CYAN "O(log n)" COLOR_GREEN " > " COLOR_CYAN "O(n)" COLOR_NONE ",\n"
		"\tInsert: " COLOR_CYAN "O(n)" COLOR_NONE ",\n"
		"\tDelete: " COLOR_CYAN "O(n)" COLOR_NONE ",\n"
		"};\n"
	);
}

inline void set_clearer(Array *arr, Clearer clear_func)
{
	arr->clear_func = clear_func;
}

void reset_array(Array *arr)
{
	char *usable = get_usable_data(arr, 0);

	if (arr->clear_func == NULL)
		foreach(i, arr->length)
			foreach(j, arr->item_size)
				usable[(i * arr->item_size)+j] = 0;
	else arr->clear_func(arr);
}

Array *new_array(uint16_t length, size_t item_size, bool isTerminated)
{
	Array *arr = malloc(sizeof(Array));

	arr->length = length;
	arr->item_size = item_size;
	arr->clear_func = NULL;
	arr->data = malloc(length * item_size);

	// cast array list into a character array so we can accually use it
	char *usable = get_usable_data(arr, 0);

	// clears the array by default
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

void set_values(Array *arr, uint32_t index, const void *values, uint32_t length)
{
	if (index+1 > arr->length)
	{
		__array_error(1, "set_values");
		return;
	}
	else if (index + length > arr->length)
	{
		__array_error(2, "set_values");
	}

	char *usable_data = get_usable_data(arr, 0);
	const char *usable_values = values;

	for (int i = 0; i < length; i++)
	{
		#ifdef PLEASE_NO_ERROS
		if (i + index >= arr->length) break;
		#endif

		memcpy(
			(void *)(usable_data + arr->item_size * (i + index)),
			(void *)(usable_values + arr->item_size * i),
			arr->item_size
		);
	}
}

// TODO (has bugs)
void insert_values(Array *arr, uint32_t index, const void *values, uint32_t length)
{
	if (index+1 > arr->length)
	{
		__array_error(1, "insert_values");
		return;
	}
	else if (index + length > arr->length)
	{
		__array_error(2, "insert_values");
	}

	char *usable_data = get_usable_data(arr, 0);
	char *usable_values = (char *)values;

	int starting_point = arr->length - length;

	if (starting_point <= index) // [best situation] O(1) -> no need to move the other items
	{
		memcpy(
			(void *)(usable_data + arr->item_size * index),
			(void *)(usable_values + arr->item_size * 0),
			arr->length - index
		);
	}
	else // [worst situation] O(n) -> needs to move the other items
	{
		for (int i = starting_point; i > index; i--)
		{
			void *destination_el = __get_data_index__(usable_data, arr, i + length);
			void *current_el = __get_data_index__(usable_data, arr, i);

			// copies the position to other location
			memcpy(destination_el, current_el, arr->item_size);

			// inserts one element
			if (i < index + length)
			{
				void *inserted_value = __get_data_index__(usable_values, arr, i - index);
				memcpy(current_el, inserted_value, arr->item_size);
			}
		}
	}

}

Array *copy_array(Array *arr)
{
	uint32_t length = arr->length;
	size_t item_size = arr->item_size;
	char *data = get_usable_data(arr, 0);

	Array *copy = new_array(length, item_size, arr->isTerminated);

	foreach(i, length)
	{
		set_values(copy, 0, data, length);
	}

	return copy;
}

void *free_array(Array *arr, bool only_structre)
{
	void *data = arr->data;
	free(arr);

	if (only_structre)
		return data;

	free(data);
	return NULL;
}
