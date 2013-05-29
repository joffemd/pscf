path=%1\bin;%1\..\pthreads-win32\dll-latest\lib;%path%

echo %1 > prog.txt

prog.exe >> prog.txt 2>&1

del lock