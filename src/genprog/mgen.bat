del mlib.pc
cl /O2 /TP /I../include /c *.c
lib /OUT:mlib.pc *.obj
del *.obj
lib /EXTRACT:main.obj mlib.pc
lib /REMOVE:main.obj mlib.pc

link /OUT:..\..\bin\genprog.exe main.obj mlib.pc ..\utils\mlib.pc libcmt.lib
