del mlib.pc
cl /O2 /TP /I../include /c *.c
lib /OUT:mlib.pc *.obj
del *.obj
