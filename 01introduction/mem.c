#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> // explicit for assert() prototype; avoids implicit declaration
#include "common.h"

int main(int argc, char *argv[])
{
    int *p = malloc(sizeof(int));                               // stdlib.h
    assert(p != NULL);                                          // assert.h
    printf("(%d) address pointed to by p: %p \n", getpid(), p); // stdio.h + unistd.h
    *p = 0;
    while (1)
    {
        Spin(1); // common.h
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p); // stdio.h + unistd.h
    }

    return 0;
}