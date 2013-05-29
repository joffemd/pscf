rm lib.pc
g++ -O3 -c -Wall -Wextra -D_WINDOWS -I../include *.c
ar r lib.pc *.o
rm *.o

g++ -static -o ../../system/bin/syncheck lib.pc ../utils/lib.pc
