#include "lstmlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int i;
    struct lstmlib *unit;
    double *input;
    double *output;
    int l = 100;
    unit = lstmlib_create(l);
    input = (double*)calloc(l, sizeof (double));
    output = (double*)calloc(l, sizeof (double));
    i = l;
    do {
        input[i] = (double)rand() / RAND_MAX * 2 - 1;
        output[i] = 0;
    } while (i--);
    lstmlib_run(unit, input, output);
    printf("id,h,x,f,i,tilde_C,C,o,hat_h\n");
    for (i = 0; i < l; i++) {
        printf("%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", i, output[i], input[i], (*unit).f[i], (*unit).i[i], (*unit).tilde_C[i], (*unit).C[i], (*unit).o[i], (*unit).hat_h[i]);
    }
    return 0;
}
