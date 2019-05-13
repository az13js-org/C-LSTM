#!/bin/sh

gcc -O3 lstmlib.c test.c -lm -o test.out
./test.out

gcc -O3 lstmlib.c test_create.c -lm -o test_create.out
./test_create.out
