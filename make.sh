#!/usr/bin/bash
gcc -Wall -Werror -fpic -c -g3 src-akhil/*.c -o target.o &&
gcc -Wall -Werror -fpic -c -g3 ctype_tests/*.c -o test.o &&
gcc -shared -o libtarget.so target.o &&
gcc -shared -o libtest.so test.o target.o &&
rm target.o
rm test.o
