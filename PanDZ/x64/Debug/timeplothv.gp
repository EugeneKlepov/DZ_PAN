set terminal wxt size 800,600
set output 'trajectory.png'
set title 'Траектория полета'
set xlabel 'Скорость, км/ч'
set ylabel 'Высота, м'
set grid
plot 'hv.csv' using 2:1 with linespoints title 'Траектория полета'
