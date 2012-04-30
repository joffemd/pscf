g++ -O3 -Wall -Wextra -I../include -c *.c
ar r lib.pc *.o
rm *.o

g++ -o ../../bin/errmap lib.pc ../utils/lib.pc
