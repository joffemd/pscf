path=%1\bin;%path%

echo %1 > genprog.txt
echo %2 >> genprog.txt
echo %3 >> genprog.txt
echo %4 >> genprog.txt
echo %1 >> genprog.txt
echo %2\bin\genprog2 %2\templates\tpl2.txt %3 %4 >> genprog.txt

%2\bin\genprog2 %2\templates\tpl2.txt %3 %4 >> genprog.txt 2>& 1

del lock