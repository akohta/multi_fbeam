# Gnuplot script file
set terminal postscript eps color enhanced "Arial" 20 size 7in,14in
set output "I_example2.eps"

set pm3d map

set size square
set multiplot layout 4,2

set xrange [-4 : 4]
set yrange [-4 : 4]
set xtics -4, 2, 4
set ytics -4, 2, 4

set title "electric field intensity on y=0 plane"
set xlabel "{/Arial-Italic x}"
set ylabel "{/Arial-Italic z}"
splot "Ie_xz.txt"

set title "electric field intensity on x=0 plane"
set xlabel "{/Arial-Italic y}"
splot "Ie_yz.txt"

set title "electric field intensity on z=0 plane"
set xlabel "{/Arial-Italic x}"
set ylabel "{/Arial-Italic y}"
splot "Ie_xy.txt"

clear

set title "magnetic field intensity on y=0 plane"
set xlabel "{/Arial-Italic x}"
set ylabel "{/Arial-Italic z}"
splot "Ih_xz.txt"

set title "magnetic field intensity on x=0 plane"
set xlabel "{/Arial-Italic y}"
splot "Ih_yz.txt"

set title "magnetic field intensity on z=0 plane"
set xlabel "{/Arial-Italic x}"
set ylabel "{/Arial-Italic y}"
splot "Ih_xy.txt"

unset multiplot
set terminal x11
