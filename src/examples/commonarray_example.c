#include "../structures/commonarray.h"
#include "examples.h"

typedef struct somestruct // this is a static structure
{
    int x;
    int y;
} mystruct;
static void print_mystruct_pointer(Array *arr);
static void print_mystruct_structure(Array *arr);

void array_examples(int page)
{
    // char type example
    if (page == 1)
    {
        Array *array = new_array(6, CHAR, sizeof(char));
        char *list = (char *)array->list;
        char *copies = "Hello"; // "Hel\0lo" would also work
        
        foreach(i, 6)
            list[i] = copies[i];

        printf("print_list(...) ->           ");
        print_list(array);
        printf(COLOR(COLOR_GREEN) "\n                           --- OR --- \n" COLOR(COLOR_NONE));
        printf("array->printing_func(...) -> ");
        array->printing_func(array);
        printf(COLOR(COLOR_GREEN) "\n                           ---EVEN--- \n" COLOR(COLOR_NONE));
        printf("common_printing(...) ->      ");
        common_printing(array);
        printf(COLOR(COLOR_RED) " // not recommended!!" COLOR(COLOR_NONE));
        printf("\n");
    }
    // int type example
    else if (page == 2)
    {
        Array *array = new_array(10, INT, sizeof(int));
        int *list = (int *)array->list;
        
        foreach(i, 10)
            list[i] = i * 2;

        print_list(array);
        printf(COLOR(COLOR_YELLOW) "\nOther methods of printing have been discussed in page (1)\n" COLOR(COLOR_NONE));
    }
    // float type example
    else if (page == 3)
    {
        Array *array = new_array(10, FLOAT, sizeof(float));
        float *list = (float *)array->list;
        
        foreach(i, 10)
            list[i] = i * 1.5;

        print_list(array);
        printf(COLOR(COLOR_YELLOW) "\nOther methods of printing have been discussed in page (1)\n" COLOR(COLOR_NONE));
    }
    // bool type example
    else if (page == 4)
    {
        Array *array = new_array(10, BOOL, sizeof(bool));
        bool *list = (bool *)array->list;
        
        foreach(i, 10)
            list[i] = i >= 5 ? true : false;

        print_list(array);
        printf(COLOR(COLOR_YELLOW) "\nOther methods of printing have been discussed in page (1)\n" COLOR(COLOR_NONE));
    }
    // string type example
    else if (page == 5)
    {
        Array *array =new_array(4, STRING, sizeof(char *));
        char **list = array->list;
        char *strings[] = {
            "Heitor",
            "Isis",
            "Mirna",
            "Elves",
        };

        foreach(i, 4)
        {
            char *str = strings[i];
            list[i] = str;
        }

        print_list(array);
        printf(COLOR(COLOR_GREEN) "\n// string types may be weird and not default but they are." COLOR(COLOR_NONE));
        printf(COLOR(COLOR_YELLOW) "\nOther methods of printing have been discussed in page (1)\n" COLOR(COLOR_NONE));
    }
    // other type example (pointer to pointer)
    else if (page == 6)
    {
        Array *array = new_array(5, OTHER, sizeof(mystruct *));
        mystruct **list = array->list;

        foreach(i, 5)
        {
            mystruct *new_struct = malloc(sizeof(mystruct));
            new_struct->x = 2 * i;
            new_struct->y = 3 * i;

            list[i] = new_struct;
        }

        printf("Without defined printer function: \n\t");
        print_list(array);
        printf("\nWith defined printer function: \n\t");
        set_printing(array, &print_mystruct_pointer);
        print_list(array);
        printf(COLOR(COLOR_YELLOW) "\nOther methods of printing have been discussed in page (1)\n" COLOR(COLOR_NONE));
    }
    // other type example (pointer to struct) [NOT RECOMMENDED]
    else if (page == 7)
    {
        Array *array = new_array(5, OTHER, sizeof(mystruct));
        mystruct *list = array->list;

        foreach(i, 5)
        {
            mystruct new_struct = { i + 10, i + 100 };
            list[i] = new_struct;
        }

        printf("Without defined printer function: \n\t");
        print_list(array);
        printf("\nWith defined printer function: \n\t");
        set_printing(array, &print_mystruct_structure);
        print_list(array);
        printf(COLOR(COLOR_YELLOW) "\nOther methods of printing have been discussed in page (1)\n" COLOR(COLOR_NONE));
    }
    // example of set_typeID() with other type
    else if (page == 8)
    {
        Array *array = new_array(5, OTHER, sizeof(mystruct *));
        mystruct **list = array->list;

        foreach(i, 5)
        {
            mystruct *new_struct = malloc(sizeof(mystruct));
            new_struct->x = 2 * i;
            new_struct->y = 3 * i;

            list[i] = new_struct;
        }

        set_typeID(array, "somestruct");
        print_list(array);
        printf(COLOR(COLOR_YELLOW) "\nOther methods of printing have been discussed in page (1)\n" COLOR(COLOR_NONE));
    }
    else printf(PAGE_ERROR, page);
}

static void print_mystruct_pointer(Array *arr)
{
    mystruct **list = arr->list;
    foreach(i, arr->length)
        printf("{x: %d, y: %d}", list[i]->x, list[i]->y);
}

static void print_mystruct_structure(Array *arr)
{
    mystruct *list = arr->list;
    foreach(i, arr->length)
        printf("{x: %d, y: %d}", list[i].x, list[i].y);
}
