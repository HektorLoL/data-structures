#include <stdio.h>
#include "structures/array.h"

void array_example()
{
    // int type example
    Array *array = new_array(10, SINT);
    int *list = (int *)get_list(array);
    
    foreach(i, 10)
        list[i] = i * 2;

    print_list(array);
    printf("\n             --- OR --- \n");
    array->printing_func(array);
    printf("\n");

    // other type example
    // need to fix the array other
    // Array *array2 = new_array(2, OTHER);
    // // array2->printing_func = &printer;
    // int *list2 = get_list(array2);
    // int a = 2, b = 4;

    // list2[0] = &a;
    // list2[1] = &b;

}

int main()
{
    return 0;
}