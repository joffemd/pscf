path=%1\bin;%path%

%2\bin\syncheck model.tab series.tab check.txt check-m.txt check-s.txt > syncheck.txt 2>& 1

del lock
