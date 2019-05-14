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
    printf("Test lstmlib_create()\n");
    unit = lstmlib_create(0);
    if (NULL == unit) {
        printf("create(0) success\n");
    } else {
        printf("create(0) fail.\n");
        return 0;
    }
    unit = lstmlib_create(5);
    input = (double*)calloc(5, sizeof (double));
    output = (double*)calloc(5, sizeof (double));
    i = 4;
    do {
        input[i] = (double)rand() / RAND_MAX * 2 - 1;
        output[i] = 0;
    } while (i--);
    lstmlib_run(unit, input, output);
    i = 4;
    do {
        printf("%d, %lf\n", i, output[i]);
    } while (i--);
    return 0;
}
