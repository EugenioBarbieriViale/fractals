#!/bin/bash

set -xe

g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra

./a.out

rm a.out

exit
