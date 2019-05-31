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
    for (i = 0; i < 1000; i++) {
        lstmlib_run_unit(unit);
        lstmlib_fit_unit(unit, 0.01);
    }
    printf("Write:%d\n", lstmlib_save(unit, "test_save.csv"));
    return 0;
}
