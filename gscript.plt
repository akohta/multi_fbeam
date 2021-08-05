set terminal postscript eps color enhanced "Arial" 16 size 8in,8in
set output "I_example2.pdf"

set pm3d map

set size square
set multiplot layout 2,2

set xrange [-4e-6 : 4e-6]
set yrange [-4e-6 : 4e-6]
set xtics -4e-6, 2e-6, 4e-6
set ytics -4e-6, 2e-6, 4e-6

set title "y=0 plane"
set xlabel "{/Arial-Italic x} (m)"
set ylabel "{/Arial-Italic z} (m)"
splot "Ie_xz.txt"

set title "x=0 plane"
set xlabel "{/Arial-Italic y} (m)"
splot "Ie_yz.txt"

set title "z=0 plane"
set xlabel "{/Arial-Italic x} (m)"
set ylabel "{/Arial-Italic y} (m)"
splot "Ie_xy.txt"

unset multiplot
set terminal x11
