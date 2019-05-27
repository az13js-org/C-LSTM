#!/bin/sh

gcc -O3 src/lstmlib.c src/test.c -lm -o test.out
./test.out

gcc -O3 src/lstmlib.c src/test_create.c -lm -o test_create.out
./test_create.out

gcc -O3 src/lstmlib.c src/test_run.c -lm -o test_run.out
./test_run.out

gcc -O3 src/lstmlib.c src/test_mse.c -lm -o test_mse.out
./test_mse.out

gcc -O3 src/lstmlib.c src/test_fitunit.c -lm -o test_fitunit.out
./test_fitunit.out

gcc -O3 src/lstmlib.c src/test_sin_cos.c -lm -o test_sin_cos.out
./test_sin_cos.out >test_sin_cos.csv

gcc -O3 src/lstmlib.c src/test_sin_cos_pre.c -lm -o test_sin_cos_pre.out
./test_sin_cos_pre.out >test_sin_cos_pre.csv

gcc -O3 src/lstmlib.c src/test_rectangle_cos_pre.c -lm -o test_rectangle_cos_pre.out
./test_rectangle_cos_pre.out >test_rectangle_cos_pre.csv

gcc -O3 src/lstmlib.c src/test_params_change.c -lm -o test_params_change.out
./test_params_change.out >test_params_change.csv

gcc -O3 src/lstmlib.c src/test_save.c -lm -o test_save.out
./test_save.out
