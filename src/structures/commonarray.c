#include "commonarray.h"

Array *new_array(uint32_t length, ArrayT type, size_t type_size)
{

    Array *array = malloc(sizeof(Array));

    array->length = length;
    array->type = type;

    array->list = malloc(type_size * length);

    if (type == OTHER)
        array->printing_func = NULL;
    else
        array->printing_func = &common_printing;

    return array;
}

void set_typeID(Array *arr, const char *type_name)
{
    arr->str_type = malloc(strlen(type_name) + 1); // count the \0
    strcpy(arr->str_type, type_name);
}

// as this function is so short, it could be declared as inline
void set_printing(Array *arr, Printer printing_func)
{
    arr->printing_func = printing_func;
}

void common_printing(Array *arr)
{
    fputs("[", stdout);
    for (int i = 0; i < arr->length; i++)
    {
        switch (arr->type)
        {
        case CHAR:
            if (((char *)arr->list)[i] == '\0') break;
            printf("'%c'", ((char *)arr->list)[i]);
            break;
        case INT:
            printf("%d", ((int *)arr->list)[i]);
            break;
        case FLOAT:
            printf("%f", ((float *)arr->list)[i]);
            break;
        case BOOL:
        {
            bool *list = ((bool *)arr->list);
            if (list[i]) printf("true");
            else         printf("false");
            break;
        }
        case STRING:
            printf("\"%s\"", ((char **)arr->list)[i]);
            break;
        case OTHER:
        default:
            if (arr->str_type) printf("<Array[%d]:: %s>", arr->length, arr->str_type);
            else printf("<Array[%d]>", arr->length);
            break;
        }

        // characters have different cases because of the \0
        if (arr->type == CHAR && ((char *)arr->list)[i + 1] == '\0')
            break;
        // if it is the last index put a colon
        else if (i + 1 < arr->length) printf(", ");
    }
    fputs("]", stdout);
}

void print_list(Array *arr)
{
    if (arr->printing_func != NULL)
        arr->printing_func(arr);
    else
    {
        if (arr->str_type) printf("<Array[%d]:: %s>", arr->length, arr->str_type);
        else printf("<Array[%d]>", arr->length);    
    }
}
