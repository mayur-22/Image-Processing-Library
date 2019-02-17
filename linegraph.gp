set title "Performance on matrix" 
set yrange [0:300]
set xrange [0:2200]
set ytics 100
set boxwidth 10
set ylabel "time in ms"
set xlabel "Matrix size"
plot 'linegraph.dat' using 1:2 title 'Pthreads' with lines, 'linegraph.dat' using 1:3 title 'MKL' with lines, 'linegraph.dat' using 1:4 title 'OpenBLAS' with lines, 'linegraph.dat' using 1:5 title 'Normal' with lines
