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
        (*unit).x[i] = (double)rand() / RAND_MAX - 0.5;
        (*unit).hat_h[i] = (double)rand() / RAND_MAX - 0.5;
    }
    printf("ID,MSE\n");
    for (i = 0; i < 100000; i++) {
        lstmlib_run_unit(unit);
        printf("%d,%lf\n", i + 1, lstmlib_get_mse(unit));
        lstmlib_fit_unit(unit, 0.01);
    }
    return 0;
}
