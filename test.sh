#!/bin/sh

gcc -O3 lstmlib.c test.c -lm -o test.out
./test.out

gcc -O3 lstmlib.c test_create.c -lm -o test_create.out
./test_create.out

gcc -O3 lstmlib.c test_run.c -lm -o test_run.out
./test_run.out

gcc -O3 lstmlib.c test_mse.c -lm -o test_mse.out
./test_mse.out
