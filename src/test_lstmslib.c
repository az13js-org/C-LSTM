#include "lstmslib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int i;
    int length = 10, unit = 5;
    struct lstmslib *lstms;
    lstms = lstmslib_create(length, unit);
    if (NULL == lstms) {
        printf("Create fail!\n");
    } else {
        printf("Create success.\n");
        printf("Length:%d\n", (*lstms).length);
        printf("Lstm_num:%d\n", (*lstms).lstm_num);
        printf("First:%d\n", (int)((*lstms).first));
        printf("END:%d\n", (int)((*lstms).end));
        for (i = 0; i < length; i++) {
            (*((*((*lstms).first)).lstm)).x[i] = rand() / RAND_MAX;
        }
        for (i = 0; i < length; i++) {
            (*((*((*lstms).end)).lstm)).h[i] = -100.0;
        }
        lstmslib_run_unit(lstms);
        for (i = 0; i < length; i++) {
            printf("%d:%lf\n", i + 1, (*((*((*lstms).end)).lstm)).h[i]);
        }
    }
    return 0;
}

