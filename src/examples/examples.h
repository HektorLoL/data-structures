#ifndef EXAMPLES_H
#define EXAMPLES_H

#define PAGE_ERROR "Page %d not found.\n"

#include "../structures/array.h"

/// Array
// built-in:
void array_examples(int page);
// data-structure functions (int examples):
int access(Array *arr, uint32_t index);       // O(1)
int search(Array *arr, int num);              // O(n)
int add(Array *arr, int num, uint32_t index); // O(n)
int remove_(Array *arr, uint32_t index);      // O(n)
void array_structure_funcs_example();

#endif // EXAMPLES_H