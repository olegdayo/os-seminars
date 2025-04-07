#!/bin/sh

gcc -o ./bin/${1} "${1}.c" -lpthread
./bin/${1}
