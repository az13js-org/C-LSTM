#include "lstmlib.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct lstmlib *unit;
    printf("Test lstmlib_create()\n");
    unit = lstmlib_create(0);
    if (NULL == unit) {
        printf("create(0) success\n");
    } else {
        printf("create(0) fail.\n");
        return 0;
    }
    unit = lstmlib_create(10);
    printf("= %d\n", (*unit).length);
    printf("= %d\n", (*unit).x);
    printf("= %d\n", (*unit).h);
    printf("= %d\n", (*unit).f);
    printf("= %d\n", (*unit).i);
    printf("= %d\n", (*unit).tilde_C);
    printf("= %d\n", (*unit).C);
    printf("= %d\n", (*unit).o);
    printf("= %d\n", (*unit).hat_h);
    printf("= %d\n", (*unit).W_fh);
    printf("= %d\n", (*unit).W_fx);
    printf("= %d\n", (*unit).b_f);
    printf("= %d\n", (*unit).W_ih);
    printf("= %d\n", (*unit).W_ix);
    printf("= %d\n", (*unit).b_i);
    printf("= %d\n", (*unit).W_Ch);
    printf("= %d\n", (*unit).W_Cx);
    printf("= %d\n", (*unit).b_C);
    printf("= %d\n", (*unit).W_oh);
    printf("= %d\n", (*unit).W_ox);
    printf("= %d\n", (*unit).b_o);
    printf("= %d\n", (*unit).error_no);
    printf("= %d\n", (*unit).error_msg);
    return 0;
}
