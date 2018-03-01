reset                                                                           
set ylabel 'time(sec)'
set style fill solid
set key center top 
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:0.210]'output.txt' using 2:xtic(1) with histogram title 'original', \
'' using 3:xtic(1) with histogram title 'optimized'  , \
'' using 4:xtic(1) with histogram title 'hashfunction'  , \
'' using 5:xtic(1) with histogram title 'bst'  , \
'' using ($0-0.200):(0.110):2 with labels title ' ' textcolor lt 1, \
'' using ($0-0.200):(0.120):3 with labels title ' ' textcolor lt 2, \
'' using ($0-0.200):(0.130):4 with labels title ' ' textcolor lt 3, \
'' using ($0-0.200):(0.140):5 with labels title ' ' textcolor lt 4,
