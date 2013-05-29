path=%1\bin;%path%

echo %1 > compiled.txt
echo %3 >> compiled.txt
echo %4 >> compiled.txt

echo g++ %4 -o prog.exe -I%3\boost_1_48 -I%3\..\pthreads-win32\dll-latest\include prog.c %3\..\pthreads-win32\dll-latest\lib\pthreadGC2.dll >> compiled.txt

g++ %4 -o prog.exe -I%3\boost_1_48 -I%3\..\pthreads-win32\dll-latest\include prog.c %3\..\pthreads-win32\dll-latest\lib\pthreadGC2.dll >> compiled.txt 2>&1

del lock