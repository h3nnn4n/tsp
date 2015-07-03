#!/usr/bin/gnuplot

set terminal pngcairo
set output 'tsp.png'

set xlabel "Size"
set autoscale

set ylabel "Time"
set title "BnB TSP"

set grid
set style data points

set key top left
unset key

set style line 1 lc rgb  '#8b1a0e' pt 1  ps 1 lt 1 lw 2
set style line 2 lc rgb  '#5e9c36' pt 2  ps 1 lt 1 lw 2 
set style line 3 lc rgb  '#f2520d' pt 3  ps 1 lt 1 lw 2 
set style line 4 lc rgb  '#6228d7' pt 4  ps 1 lt 1 lw 2 
set style line 5 lc rgb  '#2a8f1e' pt 5  ps 1 lt 1 lw 2 
set style line 6 lc rgb  '#8b1a0e' pt 6  ps 1 lt 1 lw 2
set style line 7 lc rgb  '#cc3396' pt 7  ps 1 lt 1 lw 2 
set style line 8 lc rgb  '#1972e6' pt 8  ps 1 lt 1 lw 2 
set style line 9 lc rgb  '#468db9' pt 9  ps 1 lt 1 lw 2 
set style line 10 lc rgb '#55aa97' pt 10 ps 1 lt 1 lw 2 
set style line 11 lc rgb '#3a858e' pt 11 ps 1 lt 1 lw 2
set style line 12 lc rgb '#fa440f' pt 12 ps 1 lt 1 lw 2 
set style line 13 lc rgb '#946b93' pt 13 ps 1 lt 1 lw 2 
set style line 14 lc rgb '#8ffab3' pt 14 ps 1 lt 1 lw 2 
set style line 15 lc rgb '#fdb4bd' pt 15 ps 1 lt 1 lw 2 
set style line 16 lc rgb '#ed9821' pt 15 ps 1 lt 1 lw 2 

set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12

set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror

plot    'out_0'   using 2:1 title 'out0'   with lp ls 1,  \
        'out_1'   using 2:1 title 'out1'   with lp ls 2,  \
        'out_2'   using 2:1 title 'out2'   with lp ls 3,  \
        'out_3'   using 2:1 title 'out3'   with lp ls 4,  \
        'out_4'   using 2:1 title 'out4'   with lp ls 5,  \
        'out_5'   using 2:1 title 'out5'   with lp ls 6,  \
        'out_6'   using 2:1 title 'out6'   with lp ls 7,  \
        'out_7'   using 2:1 title 'out7'   with lp ls 8,  \
        'out_8'   using 2:1 title 'out8'   with lp ls 9,  \
        'out_9'   using 2:1 title 'out9'   with lp ls 10, \
        'out_10'  using 2:1 title 'out10'  with lp ls 11, \
        'out_11'  using 2:1 title 'out11'  with lp ls 12, \
        'out_12'  using 2:1 title 'out12'  with lp ls 13, \
        'out_13'  using 2:1 title 'out13'  with lp ls 14, \
        'out_14'  using 2:1 title 'out14'  with lp ls 15, \
        'out_15'  using 2:1 title 'out15'  with lp ls 16
                                            
