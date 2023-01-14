#include "./structures/array.h"

const int PLEASE_NO_ERRORS = 1;

int main()
{
    Array *arr = new_array(5, sizeof(int), false);

    set_values(arr, 0, (int[]){30, 60, 90, 120, 150}, arr->length);

    print_typed_arr(arr, "%d", int);

    set_comparator(arr, &int_compare);

    int num = 120;
    int idx = linear_search_value(arr, &num);
    printf("\narr[%d] = %d", idx, num);

    return 0;
}
