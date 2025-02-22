#!/bin/sh

gcc -o ./bin/${1} "${1}.c"
./bin/${1} ${2}

