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
