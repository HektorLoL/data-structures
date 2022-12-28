#include "./structures/array.h"

int main()
{
    Array *arr = new_array(5, sizeof(int), false);
    int x = 500;
    int y = -9;

    insert_values(arr, 0, (int[]){30, 60, 90, 120, 150}, arr->length);
    
    Array *copy = copy_array(arr);
    
    insert_value(arr, 2, &x);
    insert_value(copy, 1, &y);


    print_typed_arr(arr, "%d", int);
    printf("\n");
    print_typed_arr(copy, "%d", int);

    return 0;
}
