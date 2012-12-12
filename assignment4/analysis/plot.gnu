
set title "Quicksort"
set xlabel "n"
set ylabel "T(n)"
set style data lines 

plot "q4.txt" title "Experimental Value", "ideal" title "Theoritical Value" 

pause -1
