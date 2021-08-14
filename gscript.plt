# Gnuplot script file
set terminal postscript eps color enhanced "Arial" 16 size 7in,7in
set output "I_example2.eps"

set pm3d map

set size square
set multiplot layout 2,2

set xrange [-4 : 4]
set yrange [-4 : 4]
set xtics -4, 2, 4
set ytics -4, 2, 4

set title "y=0 plane"
set xlabel "{/Arial-Italic x}"
set ylabel "{/Arial-Italic z}"
splot "Ie_xz.txt"

set title "x=0 plane"
set xlabel "{/Arial-Italic y}"
splot "Ie_yz.txt"

set title "z=0 plane"
set xlabel "{/Arial-Italic x}"
set ylabel "{/Arial-Italic y}"
splot "Ie_xy.txt"

unset multiplot
set terminal x11
