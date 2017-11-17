#!/usr/bin/bash
gcc -Wall -Werror -fpic -c -g3 src-akhil/*.c -o target.o &&
gcc -shared -o libtarget.so target.o &&
rm target.o
