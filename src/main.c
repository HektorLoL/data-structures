#include "./structures/array.h"

int main()
{
    Array *arr = new_array(5, sizeof(int), false);
    int x = 500;

    insert_values(arr, 0, (int[]){30, 60, 90, 120, 150}, arr->length);
    insert_value(arr, 2, &x);

    print_typed_arr(arr, "%d", int);

    return 0;
}
