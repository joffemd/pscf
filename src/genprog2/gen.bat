rm lib.pc
g++ -g -c -Wall -Wextra -D_WINDOWS -I../include *.c
ar r lib.pc *.o
rm *.o

g++ -static -o ../../system/bin/genprog2 lib.pc ../utils/lib.pc
