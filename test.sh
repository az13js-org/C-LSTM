#!/bin/sh

gcc -O3 lstmlib.c test.c -lm -o test.out
./test.out
