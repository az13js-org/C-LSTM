/*
 * 给定一段正弦波作为输入和一段余弦波作为对应的输出给LSTM作为训练数据，训练后打印预测结果和
 * 原训练数据。
 *
 * 编译：gcc -O3 lstmlib.c test_sin_cos_pre.c -lm -o test_sin_cos_pre.out
 *
 */
#include "lstmlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    struct lstmlib *unit;
    /* length是输入和输出序列点的个数，cyc是函数在序列上重复在多少个周期 */
    int i, length = 100, cyc = 5;
    unit = lstmlib_create(length);
    for (i = 0; i < length; i++) {
        //(*unit).x[i] = sin(2.0 * 3.14 / length * cyc * i) * 0.5 + 0.2 * rand() / RAND_MAX - 0.1;
        (*unit).x[i] = sin(2.0 * 3.14 / length * cyc * i) * 0.5;
        //(*unit).hat_h[i] = cos(2.0 * 3.14 / length * cyc * i) * 0.5 + 0.2 * rand() / RAND_MAX - 0.1;
        (*unit).hat_h[i] = cos(2.0 * 3.14 / length * cyc * i) * 0.5;
    }
    printf("ID,hat_h,h\n");
    for (i = 0; i < 100000; i++) {
        lstmlib_run_unit(unit);
        lstmlib_fit_unit(unit, 0.01);
    }
    for (i = 0; i < length; i++) {
        printf("%d,%lf,%lf\n", i + 1, (*unit).hat_h[i], (*unit).h[i]);
    }
    return 0;
}
