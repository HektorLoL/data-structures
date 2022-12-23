#include "examples/examples.h"
#include "structures/commonarray.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#define MAX 5000000000

int main()
{
    //! Uncomment what you want to see.
    char *pointer = malloc(sizeof(char) * MAX);
    if (pointer == NULL)
    {
        perror("malloc returned NULL");
        return -1;
    }

    for (size_t i = 0; i < MAX; i++)
        pointer[i] = i % 200;
    
    printf("Press\x1B[31m ANY\x1B[0m key to continue.");
    getchar();

    free(pointer);
    
    return 0;
}
