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
    (*unit).length = length;
    (*unit).x = (double*)calloc(length, sizeof (double));
    if (NULL == (*unit).x) {
        return NULL;
    }
    return unit;
}
