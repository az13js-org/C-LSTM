#include "lstmlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    struct lstmlib *unit;
    int i, length = 100;
    unit = lstmlib_create(length);
    for (i = 0; i < length; i++) {
        (*unit).x[i] = sin(2.0 * 3.14 / length * 5.0 * i);
        (*unit).hat_h[i] = cos(2.0 * 3.14 / length * 5.0 * i);
    }
    printf("id,MSE,W_fh,W_fx,b_f,W_ih,W_ix,b_i,W_oh,W_ox,b_o,W_Ch,W_Cx,b_C\n");
    for (i = 0; i < 2000; i++) {
        lstmlib_run_unit(unit);
        printf("%d,%lf,", i + 1, lstmlib_get_mse(unit));
        lstmlib_fit_unit(unit, 0.01);
        printf("%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
        (*unit).W_fh,(*unit).W_fx,(*unit).b_f,
        (*unit).W_ih,(*unit).W_ix,(*unit).b_i,
        (*unit).W_oh,(*unit).W_ox,(*unit).b_o,
        (*unit).W_Ch,(*unit).W_Cx,(*unit).b_C
        );
    }
    return 0;
}
