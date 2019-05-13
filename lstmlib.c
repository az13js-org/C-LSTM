#include "lstmlib.h"
#include <stdlib.h>

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
    return unit;
}
