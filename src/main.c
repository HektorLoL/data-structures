#include "./structures/array.h"

int main()
{
    Array *arr = new_array(5, sizeof(int), false);

    set_values(arr, 0, (int[]){30, 60, 90, 120, 150}, arr->length);

    printf("Default Array: ");
    print_typed_arr(arr, "%d", int);
    printf("\n");
    
    insert_values(arr, 1, (int[]){2, 3, 4, 5, 6}, 5);

    printf("Inserted     : ");
    print_typed_arr(arr, "%d", int);
    printf("\n\n");
    
    __print_array_specs__();

    return 0;
}
