# general settings, such as fonts, grid, labels

TITLE = ARG1
XLABEL = ARG2
YLABEL = ARG3

print "Title = ", TITLE
print "xlabel = ", XLABEL
print "ylabel = ", YLABEL

set title font "Helvetica, 20"
set xlabel font "Helvetica, 16"
set ylabel font "Helvetica, 16"
set xtics font "Helvetica, 14"
set ytics font "Helvetica, 14"
set key top left box
set key font "Helvetica, 16"

# set keybox width
set key width 1

# set keybox height

set key height 1

# turn grid on

set grid

# set plot title

set title TITLE

# set axes titles

set xlabel XLABEL
set ylabel YLABEL


