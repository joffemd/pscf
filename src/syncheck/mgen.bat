del mlib.pc
cl /O2 /TP /DYY_NO_UNISTD_H=1 /I../include /c *.c
lib /OUT:mlib.pc *.obj 
del *.obj
lib /EXTRACT:main.obj mlib.pc
lib /REMOVE:main.obj mlib.pc

link /OUT:..\..\bin\syncheck.exe main.obj mlib.pc ..\utils\mlib.pc libcmt.lib
