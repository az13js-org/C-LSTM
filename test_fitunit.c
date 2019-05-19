#include "lstmlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    struct lstmlib *unit;
    int i, length = 100;
    printf("\"Test fit_unit\"\n");
    unit = lstmlib_create(length);
    for (i = 0; i < length; i++) {
        (*unit).x[i] = (double)rand() / RAND_MAX * 2 - 1;
        (*unit).h[i] = (double)rand() / RAND_MAX * 2 - 1;
        (*unit).hat_h[i] = (double)rand() / RAND_MAX * 2 - 1;
    }
    printf("before:\n");
    printf("%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", (*unit).W_fh, (*unit).W_fx, (*unit).b_f, (*unit).W_ih, (*unit).W_ix, (*unit).b_i, (*unit).W_Ch, (*unit).W_Cx, (*unit).b_C, (*unit).W_oh, (*unit).W_ox, (*unit).b_o);
    lstmlib_fit_unit(unit, 1.0);
    printf("after:\n");
    printf("%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", (*unit).W_fh, (*unit).W_fx, (*unit).b_f, (*unit).W_ih, (*unit).W_ix, (*unit).b_i, (*unit).W_Ch, (*unit).W_Cx, (*unit).b_C, (*unit).W_oh, (*unit).W_ox, (*unit).b_o);
    return 0;
}
