#include <stdio.h>

#include "../include/selfctl.h"

void invoke(void (*f[])(int), int n_func)
{
    for (int i = 0; i < n_func; ++i)
        (*f[i])(i);
}

void say_hello(int n)
{
    printf("%d hello, world\n", n);
}

void say_hi(int n)
{
    printf("%d hi, world\n", n);
}

int main(void)
{
    void (*f[])(int) = { &say_hello, &say_hi, &say_hello, &say_hi };
    invoke(f, 4);

    return 0;
}
