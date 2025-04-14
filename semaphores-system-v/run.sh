#!/bin/sh

gcc -o ./bin/w1 w1.c
gcc -o ./bin/w2 w2.c

./bin/w1 & ./bin/w2
