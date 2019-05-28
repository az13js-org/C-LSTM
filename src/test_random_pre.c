/**
 * 用于测试随机数预测
 */
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
        (*unit).x[i] = 0.0;
        (*unit).hat_h[i] = (double)rand() / RAND_MAX - 0.5;
    }
    for (i = 0; i < 1000; i++) {
        lstmlib_run_unit(unit);
        lstmlib_fit_unit(unit, 0.01);
    }
    printf("id,h,hat_h\n");
    for (i = 0; i < length; i++) {
        printf("%d,%lf,%lf\n", i + 1, (*unit).h[i], (*unit).hat_h[i]);
    }
    return 0;
}
