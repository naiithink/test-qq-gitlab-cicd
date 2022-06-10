/*
 * assert: if an identifier holds a certain type or not.
 * not done
 */

#include <stdio.h>

#include "../include/selfctl.h"

int is_iterable(void *obj)
{
    self_type type = TYPE_OF(obj);

    switch (type)
    {
        case T_INT_PTR_ARR:
            printf("int[]\n");
        case T_INT_PTR:
            printf("int *\n");
        default:
            printf("-1\n");
    }
}

int main(void)
{
    int n = 0;

    if (n[0])
        return 1;
    else

    return 0;
}
