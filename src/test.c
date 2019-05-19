#include "lstmlib.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct lstmlib unit;
    printf("Test struct\n");
    printf("= %d\n", (unsigned int)(unit.length));
    printf("= %d\n", (unsigned int)(unit.x));
    printf("= %d\n", (unsigned int)(unit.h));
    printf("= %d\n", (unsigned int)(unit.f));
    printf("= %d\n", (unsigned int)(unit.i));
    printf("= %d\n", (unsigned int)(unit.tilde_C));
    printf("= %d\n", (unsigned int)(unit.C));
    printf("= %d\n", (unsigned int)(unit.o));
    printf("= %d\n", (unsigned int)(unit.hat_h));
    printf("= %lf\n", unit.W_fh);
    printf("= %lf\n", unit.W_fx);
    printf("= %lf\n", unit.b_f);
    printf("= %lf\n", unit.W_ih);
    printf("= %lf\n", unit.W_ix);
    printf("= %lf\n", unit.b_i);
    printf("= %lf\n", unit.W_Ch);
    printf("= %lf\n", unit.W_Cx);
    printf("= %lf\n", unit.b_C);
    printf("= %lf\n", unit.W_oh);
    printf("= %lf\n", unit.W_ox);
    printf("= %lf\n", unit.b_o);
    printf("= %d\n", unit.error_no);
    printf("= %s\n", unit.error_msg);
    return 0;
}
