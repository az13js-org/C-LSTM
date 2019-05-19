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
