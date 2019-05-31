#include "lstmlib.h"

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
    lstmlib_run_unit(unit);
    (*unit).x = input_back;
    (*unit).h = output_back;
    return 1;
}

char lstmlib_run_unit(struct lstmlib *unit)
{
    int i, length;
    double s;
    if (NULL == unit) {
        return 0;
    }
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
    double temp1, temp2, temp3, temp4;
    double d_h_W_fh = 0.0, d_h_W_fx = 0.0, d_h_b_f = 0.0;
    double d_h_W_ih = 0.0, d_h_W_ix = 0.0, d_h_b_i = 0.0;
    double d_h_W_Ch = 0.0, d_h_W_Cx = 0.0, d_h_b_C = 0.0;
    double d_h_W_oh = 0.0, d_h_W_ox = 0.0, d_h_b_o = 0.0;
    double d_h_W_fh_last = 0.0, d_h_W_fx_last = 0.0, d_h_b_f_last = 0.0;
    double d_h_W_ih_last = 0.0, d_h_W_ix_last = 0.0, d_h_b_i_last = 0.0;
    double d_h_W_Ch_last = 0.0, d_h_W_Cx_last = 0.0, d_h_b_C_last = 0.0;
    double d_h_W_oh_last = 0.0, d_h_W_ox_last = 0.0, d_h_b_o_last = 0.0;
    double d_C_W_fh = 0.0, d_C_W_fx = 0.0, d_C_b_f = 0.0;
    double d_C_W_ih = 0.0, d_C_W_ix = 0.0, d_C_b_i = 0.0;
    double d_C_W_Ch = 0.0, d_C_W_Cx = 0.0, d_C_b_C = 0.0;
    double d_C_W_oh = 0.0, d_C_W_ox = 0.0, d_C_b_o = 0.0;
    double d_C_W_fh_last = 0.0, d_C_W_fx_last = 0.0, d_C_b_f_last = 0.0;
    double d_C_W_ih_last = 0.0, d_C_W_ix_last = 0.0, d_C_b_i_last = 0.0;
    double d_C_W_Ch_last = 0.0, d_C_W_Cx_last = 0.0, d_C_b_C_last = 0.0;
    double d_C_W_oh_last = 0.0, d_C_W_ox_last = 0.0, d_C_b_o_last = 0.0;
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
            temp2 = 1.0 / (1.0 + exp(-((*unit).W_ix * (*unit).x[i] + (*unit).b_i)));
            d_h_b_i = (*unit).o[i] * (1.0 - temp1 * temp1) * (*unit).tilde_C[i] * (1.0 - temp2) * temp2;
            d_h_W_ih = 0.0;
            d_h_W_ix = d_h_b_i * (*unit).x[i];
            temp2 = tanh((*unit).W_Cx * (*unit).x[i] + (*unit).b_C);
            d_h_b_C = (*unit).o[i] * (1.0 - temp1 * temp1) * (*unit).i[i] * (1.0 - temp2 * temp2);
            d_h_W_Ch = 0.0;
            d_h_W_Cx = d_h_b_C * (*unit).x[i];
            temp2 = 1.0 / (1.0 + exp(-((*unit).W_ox * (*unit).x[i] + (*unit).b_o)));
            d_h_b_o = temp1 * (1.0 - temp2) * temp2;
            d_h_W_oh = 0.0;
            d_h_W_ox = d_h_b_o * (*unit).x[i];
        } else {
            // 这里计算当 t>1 时的情况，需要算出的变量是所有的 d_h_xxx，也就是一共 12 个参数分成 12 个部分
            // Part 1
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * (*unit).W_oh * d_h_W_fh_last;
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * ((*unit).h[i - 1] + (*unit).W_fh * d_h_W_fh_last);
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * (*unit).W_ih * d_h_W_fh_last;
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * (*unit).W_Ch * d_h_W_fh_last;
            d_C_W_fh = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_W_fh_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_W_fh = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_W_fh;
            // Part 2
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * (*unit).W_oh * d_h_W_fx_last;
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * ((*unit).W_fh * d_h_W_fx_last + (*unit).x[i]);
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * (*unit).W_ih * d_h_W_fx_last;
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * (*unit).W_Ch * d_h_W_fx_last;
            d_C_W_fx = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_W_fx_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_W_fx = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_W_fx;
            // Part 3
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * (*unit).W_oh * d_h_b_f_last;
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * ((*unit).W_fh * d_h_b_f_last + 1.0);
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * (*unit).W_ih * d_h_b_f_last;
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * (*unit).W_Ch * d_h_b_f_last;
            d_C_b_f = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_b_f_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_b_f = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_b_f;
            // Part 4
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * (*unit).W_oh * d_h_W_ih_last;
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * (*unit).W_fh * d_h_W_ih_last;
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * ((*unit).h[i - 1] + (*unit).W_ih * d_h_W_ih_last);
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * (*unit).W_Ch * d_h_W_ih_last;
            d_C_W_ih = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_W_ih_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_W_ih = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_W_ih;
            // Part 5
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * (*unit).W_oh * d_h_W_ix_last;
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * (*unit).W_fh * d_h_W_ix_last;
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * ((*unit).W_ih * d_h_W_ix_last + (*unit).x[i]);
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * (*unit).W_Ch * d_h_W_ix_last;
            d_C_W_ix = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_W_ix_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_W_ix = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_W_ix;
            // Part 6
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * (*unit).W_oh * d_h_b_i_last;
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * (*unit).W_fh * d_h_b_i_last;
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * ((*unit).W_ih * d_h_b_i_last + 1.0);
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * (*unit).W_Ch * d_h_b_i_last;
            d_C_b_i = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_b_i_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_b_i = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_b_i;
            // Part 7
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * (*unit).W_oh * d_h_W_Ch_last;
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * (*unit).W_fh * d_h_W_Ch_last;
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * (*unit).W_ih * d_h_W_Ch_last;
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * ((*unit).h[i - 1] + (*unit).W_Ch * d_h_W_Ch_last);
            d_C_W_Ch = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_W_Ch_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_W_Ch = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_W_Ch;
            // Part 8
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * (*unit).W_oh * d_h_W_Cx_last;
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * (*unit).W_fh * d_h_W_Cx_last;
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * (*unit).W_ih * d_h_W_Cx_last;
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * ((*unit).W_Ch * d_h_W_Cx_last + (*unit).x[i]);
            d_C_W_Cx = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_W_Cx_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_W_Cx = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_W_Cx;
            // Part 9
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * (*unit).W_oh * d_h_b_C_last;
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * (*unit).W_fh * d_h_b_C_last;
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * (*unit).W_ih * d_h_b_C_last;
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * ((*unit).W_Ch * d_h_b_C_last + 1.0);
            d_C_b_C = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_b_C_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_b_C = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_b_C;
            // Part 10
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * ((*unit).h[i - 1] + (*unit).W_oh * d_h_W_oh_last);
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * (*unit).W_fh * d_h_W_oh_last;
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * (*unit).W_ih * d_h_W_oh_last;
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * (*unit).W_Ch * d_h_W_oh_last;
            d_C_W_oh = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_W_oh_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_W_oh = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_W_oh;
            // Part 11
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * ((*unit).W_oh * d_h_W_ox_last + (*unit).x[i]);
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * (*unit).W_fh * d_h_W_ox_last;
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * (*unit).W_ih * d_h_W_ox_last;
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * (*unit).W_Ch * d_h_W_ox_last;
            d_C_W_ox = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_W_ox_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_W_ox = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_W_ox;
            // Part 12
            temp1 = (*unit).W_oh * (*unit).h[i - 1] + (*unit).W_ox * (*unit).x[i] + (*unit).b_o;
            temp1 = 1.0 / (1.0 + exp(-temp1));
            temp1 = temp1 * (1.0 - temp1) * ((*unit).W_oh * d_h_b_o_last + 1.0);
            temp2 = (*unit).W_fh * (*unit).h[i - 1] + (*unit).W_fx * (*unit).x[i] + (*unit).b_f;
            temp2 = 1.0 / (1.0 + exp(-temp2));
            temp2 = temp2 * (1.0 - temp2) * (*unit).W_fh * d_h_b_o_last;
            temp3 = (*unit).W_ih * (*unit).h[i - 1] + (*unit).W_ix * (*unit).x[i] + (*unit).b_i;
            temp3 = 1.0 / (1.0 + exp(-temp3));
            temp3 = temp3 * (1.0 - temp3) * (*unit).W_ih * d_h_b_o_last;
            temp4 = (*unit).W_Ch * (*unit).h[i - 1] + (*unit).W_Cx * (*unit).x[i] + (*unit).b_C;
            temp4 = tanh(temp4);
            temp4 = (1.0 - temp4 * temp4) * (*unit).W_Ch * d_h_b_o_last;
            d_C_b_o = temp2 * (*unit).C[i - 1] + (*unit).f[i] * d_C_b_o_last + temp3 * (*unit).tilde_C[i] + (*unit).i[i] * temp4;
            d_h_b_o = temp1 * tanh((*unit).C[i]) + (*unit).o[i] * (1.0 - tanh((*unit).C[i]) * tanh((*unit).C[i])) * d_C_b_o;
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

        d_h_W_fh_last = d_h_W_fh; d_h_W_fx_last = d_h_W_fx; d_h_b_f_last = d_h_b_f;
        d_h_W_ih_last = d_h_W_ih; d_h_W_ix_last = d_h_W_ix; d_h_b_i_last = d_h_b_i;
        d_h_W_Ch_last = d_h_W_Ch; d_h_W_Cx_last = d_h_W_Cx; d_h_b_C_last = d_h_b_C;
        d_h_W_oh_last = d_h_W_oh; d_h_W_ox_last = d_h_W_ox; d_h_b_o_last = d_h_b_o;

        d_C_W_fh_last = d_C_W_fh; d_C_W_fx_last = d_C_W_fx; d_C_b_f_last = d_C_b_f;
        d_C_W_ih_last = d_C_W_ih; d_C_W_ix_last = d_C_W_ix; d_C_b_i_last = d_C_b_i;
        d_C_W_Ch_last = d_C_W_Ch; d_C_W_Cx_last = d_C_W_Cx; d_C_b_C_last = d_C_b_C;
        d_C_W_oh_last = d_C_W_oh; d_C_W_ox_last = d_C_W_ox; d_C_b_o_last = d_C_b_o;
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

int lstmlib_save(struct lstmlib *unit, char *file_name)
{
    FILE *file;
    int write = 0;
    if (NULL == unit) {
        return 0;
    }
    if (0 != (*unit).error_no) {
        return 0;
    }
    file = fopen(file_name, "w");
    if (NULL == file) {
        return 0;
    }
    write += fprintf(file, "0\n"); // version
    write += fprintf(file, "%d\n", (*unit).length);
    write += fprintf(file, "%lf\n", (*unit).W_fh);
    write += fprintf(file, "%lf\n", (*unit).W_fx);
    write += fprintf(file, "%lf\n", (*unit).b_f);
    write += fprintf(file, "%lf\n", (*unit).W_ih);
    write += fprintf(file, "%lf\n", (*unit).W_ix);
    write += fprintf(file, "%lf\n", (*unit).b_i);
    write += fprintf(file, "%lf\n", (*unit).W_Ch);
    write += fprintf(file, "%lf\n", (*unit).W_Cx);
    write += fprintf(file, "%lf\n", (*unit).b_C);
    write += fprintf(file, "%lf\n", (*unit).W_oh);
    write += fprintf(file, "%lf\n", (*unit).W_ox);
    write += fprintf(file, "%lf\n", (*unit).b_o);
    fclose(file);
    return write;
}
