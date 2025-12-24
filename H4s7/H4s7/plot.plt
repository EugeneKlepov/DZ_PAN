set datafile separator ','
set grid
set terminal pngcairo size 1100,650
set output 'plot.png'
set title 'Speed magnitude v(t)'
set xlabel 't'
set ylabel 'v'
plot 'tv.csv' using 1:2 with linespoints title 'v(t)'
