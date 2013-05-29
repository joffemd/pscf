rm lib.pc
g++ -O3 -c -Wall -Wextra -I../include *.c
ar r lib.pc *.o
rm *.o

g++ -static -o ../../system/bin/errmap lib.pc ../utils/lib.pc
