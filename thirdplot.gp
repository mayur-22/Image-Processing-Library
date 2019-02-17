set title "Ratio of normal/pthreads" 
set yrange [0:2]
set xrange [0:2200]
set ytics 1
set boxwidth 10
set ylabel "time in ms"
set xlabel "Matrix size"
plot 'thirdplot.dat' using 1:2 title 'Ratio' with lines
