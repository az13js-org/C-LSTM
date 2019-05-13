#ifndef LSTMLIB

#define LSTMLIB

struct lstmlib
{
    int length;
    double *x;
    double *h;
    double *f;
    double *i;
    double *tilde_C;
    double *C;
    double *o;
    double *hat_h;
    double W_fh;
    double W_fx;
    double b_f;
    double W_ih;
    double W_ix;
    double b_i;
    double W_Ch;
    double W_Cx;
    double b_C;
    double W_oh;
    double W_ox;
    double b_o;
    int error_no;
    char *error_msg;
};

struct lstmlib* lstmlib_create(int length);

#endif
