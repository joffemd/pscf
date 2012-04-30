cl /O2 /TP /I../include /c main.c

link /OUT:..\..\bin\errmap.exe main.obj ..\utils\mlib.pc libcmt.lib
