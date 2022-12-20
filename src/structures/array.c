#include "array.h"

static void clear_list(Array *arr)
{
    if (arr->type != SCHAR)   arr->list.schar = NULL;
    if (arr->type != SINT)    arr->list.sint = NULL;
    if (arr->type != UCHAR)   arr->list.uchar = NULL;
    if (arr->type != UINT)    arr->list.uint = NULL;
    if (arr->type != FLOAT)   arr->list.float_ = NULL;
    if (arr->type != BOOL)    arr->list.bool_ = NULL;
    if (arr->type != POINTER) arr->list.pointer = NULL;
}

static void init_list(Array *arr)
{
    size_t size = arr->length;

    switch (arr->type) {
        case SCHAR:
            arr->list.schar = malloc(size * sizeof(char *));
            break;
        case SINT:
            arr->list.sint = malloc(size * sizeof(int *));
            break;
        case UCHAR:
            arr->list.uchar = malloc(size * sizeof(unschar *));
            break;
        case UINT:
            arr->list.uint = malloc(size * sizeof(unsint *));
            break;
        case FLOAT:
            arr->list.float_ = malloc(size * sizeof(float *));
            break;
        case BOOL:
            arr->list.bool_ = malloc(size * sizeof(bool *));
            break;
        case POINTER:
            arr->list.pointer = malloc(size * sizeof(void *));
            break;
        case OTHER:
        default:
            arr->list.other = malloc(size * sizeof(void *));
            break;
    }

    clear_list(arr);
}

Array *new_array(const size_t length, const ArrayT type)
{
    Array *array = malloc(sizeof(Array));

    array->length = length;
    array->type = type;

    init_list(array);

    if (type == OTHER)
        array->printing_func = NULL;
    else
        array->printing_func = &common_printing;

    return array;
}

void set_printing(Array *arr, Printer printing_func)
{
    arr->printing_func = printing_func;
}

void common_printing(Array *arr)
{
    char *formats[] = { FORMATS };

    fputs("[", stdout);
    switch (arr->type) {
        case SCHAR:
            for (int i = 0; i < arr->length; i++)
                fprintf(stdout, formats[arr->type], arr->list.schar[i]);
            break;
        case SINT:
            for (int i = 0; i < arr->length; i++)
                fprintf(stdout, formats[arr->type], arr->list.sint[i]);
            break;
        case UCHAR:
            for (int i = 0; i < arr->length; i++)
                fprintf(stdout, formats[arr->type], arr->list.uchar[i]);
            break;
        case UINT:
            for (int i = 0; i < arr->length; i++)
                fprintf(stdout, formats[arr->type], arr->list.uint[i]);
            break;
        case FLOAT:
            for (int i = 0; i < arr->length; i++)
                fprintf(stdout, formats[arr->type], arr->list.float_[i]);
            break;
        case BOOL:
            for (int i = 0; i < arr->length; i++)
                fprintf(stdout, formats[arr->type], arr->list.bool_[i]);
            break;
        case POINTER:
            for (int i = 0; i < arr->length; i++)
                fprintf(stdout, formats[arr->type], arr->list.pointer[i]);
            break;
        case OTHER:
        default:
            arr->printing_func(arr);
            break;
    }
    printf(GO(2, LEFT) DELETE_FROM_TO_END); // delete last colon ", "
    fflush(stdout); // dont know if it's necessary
    fputs("]", stdout);
}

void *get_list(Array *arr)
{
    switch (arr->type) {
        case SCHAR:
            return arr->list.schar;
        case SINT:
            return arr->list.sint;
        case UCHAR:
            return arr->list.uchar;
        case UINT:
            return arr->list.uint;
        case FLOAT:
            return arr->list.float_;
        case BOOL:
            return arr->list.bool_;
        case POINTER:
            return arr->list.pointer;
        case OTHER:
        default:
            return arr->list.other;
    }
}

void print_list(Array *arr)
{
    if (arr->printing_func != NULL)
        arr->printing_func(arr);
}
