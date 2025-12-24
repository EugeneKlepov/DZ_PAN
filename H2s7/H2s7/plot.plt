set datafile separator ','
set grid
set terminal pngcairo size 1000,600
set output 'plot.png'
set title 'x(t)'
set xlabel 't'
set ylabel 'x'
plot 'traj_used.csv' using 1:2 with linespoints title 'x(t)'
