set datafile separator ','
set grid
set terminal pngcairo size 1100,650
set output 'plot.png'
set title 'Altitude: original vs filtered'
set xlabel 't'
set ylabel 'H'
plot 'original.csv' using 1:2 with linespoints title 'original',\
     'filtered.csv' using 1:2 with linespoints title 'filtered'
