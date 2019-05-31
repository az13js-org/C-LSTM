#include "lstmslib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    struct lstmslib *lstms;
    lstms = lstmslib_create(100, 10);
    if (NULL == lstms) {
        printf("Create fail!\n");
    } else {
        printf("Create success.\n");
        printf("Length:%d\n", (*lstms).length);
        printf("Lstm_num:%d\n", (*lstms).lstm_num);
        printf("First:%d\n", (int)((*lstms).first));
        printf("END:%d\n", (int)((*lstms).end));
    }
    return 0;
}

