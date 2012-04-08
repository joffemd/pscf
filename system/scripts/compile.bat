path=%1\bin;%path%

g++ -O3 -o prog.exe -I%3\boost_1_48 prog.c > compiled.txt 2>&1

del lock