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
        (*unit).x[i] = 0.0;
        (*unit).h[i] = 0.0;
        (*unit).f[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).i[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).tilde_C[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).C[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).o[i] = (double)rand() / RAND_MAX * diff + min;
        (*unit).hat_h[i] = (double)rand() / RAND_MAX * diff + min;
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

char lstmlib_run(struct lstmlib *unit, double *input, double *output)
{
    int i, length;
    double s;
    double *input_back;
    double *output_back;
    if (NULL == unit) {
        return 0;
    }
    if (NULL == input) {
        return 0;
    }
    if (NULL == output) {
        return 0;
    }
    input_back = (*unit).x;
    output_back = (*unit).h;
    (*unit).x = input;
    (*unit).h = output;
    length = (*unit).length;
    for (i = 0; i < length; i++) {
        if (i == 0) {
            s = (*unit).b_f;
            (*unit).f[i] = 1.0 / (1.0 + exp(-1.0 * s));
            s = (*unit).b_i;
            (*unit).i[i] = 1.0 / (1.0 + exp(-1.0 * s));
            s = (*unit).b_C;
            (*unit).tilde_C[i] = tanh(s);
            (*unit).C[i] = (*unit).i[i] * (*unit).tilde_C[i];
            s = (*unit).b_o;
            (*unit).o[i] = 1.0 / (1.0 + exp(-1.0 * s));
            (*unit).h[i] = (*unit).o[i] * tanh((*unit).C[i]);
        } else {
            s = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i - 1] + (*unit).b_f;
            (*unit).f[i] = 1.0 / (1.0 + exp(-1.0 * s));
            s = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i - 1] + (*unit).b_i;
            (*unit).i[i] = 1.0 / (1.0 + exp(-1.0 * s));
            s = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i - 1] + (*unit).b_C;
            (*unit).tilde_C[i] = tanh(s);
            (*unit).C[i] = (*unit).f[i] * (*unit).C[i - 1] + (*unit).i[i] * (*unit).tilde_C[i];
            s = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i - 1] + (*unit).b_o;
            (*unit).o[i] = 1.0 / (1.0 + exp(-1.0 * s));
            (*unit).h[i] = (*unit).o[i] * tanh((*unit).C[i]);
        }
    }
    (*unit).x = input_back;
    (*unit).h = output_back;
    return 1;
}

double lstmlib_get_mse(struct lstmlib *unit)
{
    int i;
    double s, sum;
    if (NULL == unit) {
        return 0.0;
    }
    sum = 0.0;
    i = (*unit).length - 1;
    do {
        s = (*unit).h[i] - (*unit).hat_h[i];
        sum += (s * s);
    } while (i--);
    return sum / (*unit).length;
}

/**
 * BPTT 过程
 */
char lstmlib_fit_unit(struct lstmlib *unit, double lr)
{
    int i, length;
    double temp1, temp2;
    double d_h_W_fh = 0.0, d_h_W_fx = 0.0, d_h_b_f = 0.0;
    double d_h_W_ih = 0.0, d_h_W_ix = 0.0, d_h_b_i = 0.0;
    double d_h_W_Ch = 0.0, d_h_W_Cx = 0.0, d_h_b_C = 0.0;
    double d_h_W_oh = 0.0, d_h_W_ox = 0.0, d_h_b_o = 0.0;
    double d_E_W_fh = 0.0, d_E_W_fx = 0.0, d_E_b_f = 0.0;
    double d_E_W_ih = 0.0, d_E_W_ix = 0.0, d_E_b_i = 0.0;
    double d_E_W_Ch = 0.0, d_E_W_Cx = 0.0, d_E_b_C = 0.0;
    double d_E_W_oh = 0.0, d_E_W_ox = 0.0, d_E_b_o = 0.0;
    if (NULL == unit) {
        return 0;
    }
    length = (*unit).length;
    for (i = 0; i < length; i++) {
        if (0 == i) {
            d_h_b_f = 0.0;
            d_h_W_fh = 0.0;
            d_h_W_fx = 0.0;
            temp1 = tanh((*unit).C[i]);
            temp2 = 1.0 / (1.0 - exp(-((*unit).W_ix * (*unit).x[i] + (*unit).b_i)));
            d_h_b_i = (*unit).o[i] * (1.0 - temp1 * temp1) * (*unit).tilde_C[i] * (1.0 - temp2) * temp2;
            d_h_W_ih = 0.0;
            d_h_W_ix = d_h_b_i * (*unit).x[i];
            temp2 = tanh((*unit).W_Cx * (*unit).x[i] + (*unit).b_C);
            d_h_b_C = (*unit).o[i] * (1.0 - temp1 * temp1) * (*unit).i[i] * (1.0 - temp2 * temp2);
            d_h_W_Ch = 0.0;
            d_h_W_Cx = d_h_b_C * (*unit).x[i];
            temp2 = 1.0 / (1.0 - exp(-((*unit).W_ox * (*unit).x[i] + (*unit).b_o)));
            d_h_b_o = temp1 * (1.0 - temp2) * temp2;
            d_h_W_oh = 0.0;
            d_h_W_ox = d_h_b_o * (*unit).x[i];
        } else {
        }
        d_E_W_fh = d_E_W_fh + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_W_fh;
        d_E_W_fx = d_E_W_fx + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_W_fx;
        d_E_b_f = d_E_b_f + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_b_f;
        d_E_W_ih = d_E_W_ih + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_W_ih;
        d_E_W_ix = d_E_W_ix + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_W_ix;
        d_E_b_i = d_E_b_i + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_b_i;
        d_E_W_Ch = d_E_W_Ch + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_W_Ch;
        d_E_W_Cx = d_E_W_Cx + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_W_Cx;
        d_E_b_C = d_E_b_C + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_b_C;
        d_E_W_oh = d_E_W_oh + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_W_oh;
        d_E_W_ox = d_E_W_ox + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_W_ox;
        d_E_b_o = d_E_b_o + 2.0 / length * ((*unit).h[i] - (*unit).hat_h[i]) * d_h_b_o;
    }
    (*unit).W_fh = (*unit).W_fh - lr * d_E_W_fh;
    (*unit).W_fx = (*unit).W_fx - lr * d_E_W_fx;
    (*unit).b_f = (*unit).b_f - lr * d_E_b_f;
    (*unit).W_ih = (*unit).W_ih - lr * d_E_W_ih;
    (*unit).W_ix = (*unit).W_ix - lr * d_E_W_ix;
    (*unit).b_i = (*unit).b_i - lr * d_E_b_i;
    (*unit).W_Ch = (*unit).W_Ch - lr * d_E_W_Ch;
    (*unit).W_Cx = (*unit).W_Cx - lr * d_E_W_Cx;
    (*unit).b_C = (*unit).b_C - lr * d_E_b_C;
    (*unit).W_oh = (*unit).W_oh - lr * d_E_W_oh;
    (*unit).W_ox = (*unit).W_ox - lr * d_E_W_ox;
    (*unit).b_o = (*unit).b_o - lr * d_E_b_o;
    return 1;
}
