#include <stdio.h>

#include "../include/selfctl.h"

int main(void)
{
    printf("%s\n\
%s\n", __FUNCTION__, __func__);
    printf("%ld\n", __STDC_VERSION__);
    TRACE("eiei");
    return 0;
}
