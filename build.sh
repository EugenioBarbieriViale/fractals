#!/bin/bash

set -xe

gcc mandelbrot.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra

./a.out

rm a.out

exit
