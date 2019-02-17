set title "performance on matrix of size 1000" 
set yrange [0:100]
set xrange [0:40]
set ytics 5
set boxwidth 10
set ylabel "time in ms"
set xtics scale 0 ("pthreads" 10, "mkl" 20, "OpenBLAS" 30)
plot 'boxplot.dat' using 1:2:3:5:6 with candlesticks lt 3 lw 2 title 'Spread around mean' whiskerbars, 'boxplot.dat' using 1:4:4:4:4 with candlesticks lt -1 lw 2 notitle