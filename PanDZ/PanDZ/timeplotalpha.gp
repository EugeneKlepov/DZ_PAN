set terminal wxt size 800,600
set output 'alpha.png'
set title 'Траектория полета'
set xlabel 'Время, с'
set ylabel 'Alpha, градусы'
set grid
plot 'alpha.csv' using 2:1 with linespoints title 'Траектория полета'
