#ifndef LSTMSLIB

#define LSTMSLIB

#include "lstmlib.h"

// LSTM 单元组成的链表
struct lstmslib_sequence
{
    struct lstmslib_sequence *before; // 上一个单元
    struct lstmlib *lstm; // 当前单元保存的 LSTM
    struct lstmslib_sequence *after; // 下一个单元
};

// LSTM 多单元的对象
struct lstmslib
{
    int length; // 总长度
    int lstm_num; // LSTM 数量
    struct lstmslib_sequence *first; // 第一个 LSTM 链表单元
    struct lstmslib_sequence *end; // 最后一个 LSTM 链表单元
};

struct lstmslib* lstmslib_create(int length, int lstm_num); // 创建 LSTM 多单元对象

#endif
