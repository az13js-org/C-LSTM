#include "lstmlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct lstmlib* lstmlib_create(int length)
{
    struct lstmlib* unit;
    if (length < 1) {
        return NULL;
    }
    unit = (struct lstmlib*)malloc(sizeof (struct lstmlib));
    if (!unit) {
        return NULL;
    }
    (*unit).error_no = 0;
    (*unit).error_msg = "\0";
    (*unit).length = length;
    (*unit).x = (double*)calloc(length, sizeof (double));
    if (NULL == (*unit).x) {
        free(unit);
        return NULL;
    }
    (*unit).h = (double*)calloc(length, sizeof (double));
    if (NULL == (*unit).h) {
        free((*unit).x);
        free(unit);
        return NULL;
    }
    (*unit).f = (double*)calloc(length, sizeof (double));
    if (NULL == (*unit).f) {
        free((*unit).h);
        free((*unit).x);
        free(unit);
        return NULL;
    }
    (*unit).i = (double*)calloc(length, sizeof (double));
    if (NULL == (*unit).i) {
        free((*unit).f);
        free((*unit).h);
        free((*unit).x);
        free(unit);
        return NULL;
    }
    (*unit).tilde_C = (double*)calloc(length, sizeof (double));
    if (NULL == (*unit).tilde_C) {
        free((*unit).i);
        free((*unit).f);
        free((*unit).h);
        free((*unit).x);
        free(unit);
        return NULL;
    }
    (*unit).C = (double*)calloc(length, sizeof (double));
    if (NULL == (*unit).C) {
        free((*unit).tilde_C);
        free((*unit).i);
        free((*unit).f);
        free((*unit).h);
        free((*unit).x);
        free(unit);
        return NULL;
    }
    (*unit).o = (double*)calloc(length, sizeof (double));
    if (NULL == (*unit).o) {
        free((*unit).C);
        free((*unit).tilde_C);
        free((*unit).i);
        free((*unit).f);
        free((*unit).h);
        free((*unit).x);
        free(unit);
        return NULL;
    }
    (*unit).hat_h = (double*)calloc(length, sizeof (double));
    if (NULL == (*unit).hat_h) {
        free((*unit).o);
        free((*unit).C);
        free((*unit).tilde_C);
        free((*unit).i);
        free((*unit).f);
        free((*unit).h);
        free((*unit).x);
        free(unit);
        return NULL;
    }
    lstmlib_random_params(unit, -1, 1);
    return unit;
}

char lstmlib_random_params(struct lstmlib *unit, double min, double max)
{
    int i;
    double diff;
    if (NULL == unit) {
        return 0;
    }
    if (max < min) {
        return 0;
    }
    diff = max - min;
    i = (*unit).length - 1;
    do {
        (*unit).x[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).h[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).f[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).i[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).tilde_C[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).C[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).o[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).hat_h[i] = (double)rand() / RAND_MAX * diff + min;
        printf("%d\n", i);
    } while (i--);
    (*unit).W_fh = (double)rand() / RAND_MAX * diff + min;
    (*unit).W_fx = (double)rand() / RAND_MAX * diff + min;
    (*unit).b_f = (double)rand() / RAND_MAX * diff + min;
    (*unit).W_ih = (double)rand() / RAND_MAX * diff + min;
    (*unit).W_ix = (double)rand() / RAND_MAX * diff + min;
    (*unit).b_i = (double)rand() / RAND_MAX * diff + min;
    (*unit).W_Ch = (double)rand() / RAND_MAX * diff + min;
    (*unit).W_Cx = (double)rand() / RAND_MAX * diff + min;
    (*unit).b_C = (double)rand() / RAND_MAX * diff + min;
    (*unit).W_oh = (double)rand() / RAND_MAX * diff + min;
    (*unit).W_ox = (double)rand() / RAND_MAX * diff + min;
    (*unit).b_o = (double)rand() / RAND_MAX * diff + min;
    return 1;
}
