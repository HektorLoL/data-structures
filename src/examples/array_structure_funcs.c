#include "examples.h"

// returns the number at the index.
int access(Array *arr, uint32_t index)
{
	int *list = arr->list;
	return list[index];
}

// if array has number: returns the index of the number in the array.
// else: retuns -1.
int search(Array *arr, int num)
{
	int *list = arr->list;

	foreach(i, arr->length)
	{
		if (list[i] == num) return i;
	}

	return -1;
}

// adds the number at the index, moving all other indexes to the right (this is not a set function).
// retuns the added number.
int add(Array *arr, int num, uint32_t index)
{
	int *list = arr->list;

	// example of array:
	//   [ 0, 2, 3, 4 ]   length: 4
	// you call this function:
	//   add(array: [that_array], num: [1], index: [1]);
	// so the loop will go backwards:
	//   i = (4-1) = 3    ->  array[3] = array[2]
	//   newarray         ->  [ 0, 2, 3, 3 ]
	//   i-1 = 2          ->  array[2] = array[1]
	//   newarray         ->  [ 0, 2, 2, 3 ]
	// the loop ends and we change the desired index to the num
	//   arr[1] = num
	//   newarray -> [ 0, 1, 2, 3 ]

	for (uint32_t i = arr->length - 1; i > index; i--)
		list[i] = list[i - 1];

	list[index] = num;
	return num;
}

// removes the number from a index of the array.
// retuns the removed number.
int remove_(Array *arr, uint32_t index)
{
	int *list = arr->list;
	int removed_number = list[index];

	// works kind of like the add() function
	// but the loop goes from left to right (like a normal loop)

	for (uint32_t i = index; (i + 1) < arr->length; i++)
		list[i] = list[i + 1];
	list[arr->length - 1] = 0; // last index needs to be cleaned if there is something

	return removed_number;
}

void array_structure_funcs_example()
{
	Array *arr = new_array(4, INT, sizeof(int));
    int *list = arr->list;

    foreach(i, 4)
        list[i] = i + 1;
    list[3] = 5;

    printf("before: ");
    print_list(arr);
    printf("\n");

    printf("> access(): number %d\n", access(arr, 1));
    printf("> search(): index %d\n", search(arr, 4));
    printf("> add():    number %d\n", add(arr, 4, 3));
    printf("> remove(): number %d\n", remove_(arr, 0));

    printf("after: ");
    print_list(arr);
    printf("\n");
}
