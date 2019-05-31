#ifndef LSTMLIB

#define LSTMLIB

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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
char lstmlib_random_params(struct lstmlib *unit, double min, double max);
char lstmlib_run(struct lstmlib *unit, double *input, double *output);
char lstmlib_run_unit(struct lstmlib *unit);
double lstmlib_get_mse(struct lstmlib *unit);
char lstmlib_fit_unit(struct lstmlib *unit, double lr);
int lstmlib_save(struct lstmlib *unit, char *file_name);

#endif
