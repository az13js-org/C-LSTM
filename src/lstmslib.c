#include "lstmslib.h"

struct lstmslib* lstmslib_create(int length, int lstm_num) // TODO az13js 创建 LSTM 多单元对象
{
    int i;
    struct lstmslib *lstms;
    struct lstmslib_sequence *sequence;
    struct lstmslib_sequence *sequence_last = NULL;
    if (length < 1 || lstm_num < 1) {
        return NULL;
    }
    lstms = (struct lstmslib*)malloc(sizeof (struct lstmslib));
    if (NULL == lstms) {
        return lstms;
    }
    (*lstms).length = length;
    (*lstms).lstm_num = lstm_num;
    for (i = 0; i < lstm_num; i++) {
        sequence = (struct lstmslib_sequence *)malloc(sizeof (struct lstmslib_sequence));
        if (NULL == sequence) {
            return NULL;
        }
        (*sequence).before = sequence_last;
        (*sequence).lstm = lstmlib_create(length);
        (*sequence).after = NULL;
        if (NULL != sequence_last) {
            free((*((*sequence).lstm)).x); // 存在上一个单元，则当前单元的输入来自上一个单元的输出
            (*((*sequence).lstm)).x = (*((*sequence_last).lstm)).h;
            free((*((*sequence_last).lstm)).hat_h); // 上一个单元不需要设置期望输出
            (*sequence_last).after = sequence;
        }
        sequence_last = sequence;
        if (0 == i) {
            (*lstms).first = sequence;
        }
        if (lstm_num - 1 == i) {
            (*lstms).end = sequence;
        }
    }
    return lstms;
}

char lstmslib_run_unit(struct lstmslib *lstms)
{
    struct lstmslib_sequence *sequence;
    if (NULL == lstms) {
        return 0;
    }
    sequence = (*lstms).first;
    while (sequence) {
        lstmlib_run_unit((*sequence).lstm);
        sequence = (*sequence).after;
    }
    return 1;
}

char lstmslib_fit_unit(struct lstmlib *lstms, double lr)
{
    return 1;
}
