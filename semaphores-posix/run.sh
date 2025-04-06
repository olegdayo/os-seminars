#!/bin/sh

gcc -pthread -o ./bin/${1} "${1}.c" -lpthread
./bin/${1}
