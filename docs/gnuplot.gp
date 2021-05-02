# general settings, such as fonts, grid, labels

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

set title "This is title"

# set axes titles

set xlabel "x"
set ylabel "y"

# plotting commands

plot "gnu_test.dat" using 1:2 title "Пермаллой"

# accessing values in columns with $ example

plot "./data/permal.dat" using ($1 * 11.1):($2 * 0.842) title "Пермаллой"

# specify single error value for x and y (deltax = 0.02 ,deltay = 0.001)

plot "./data/permal.dat" using ($1 * 11.1):($2 * 0.842):(0.02):(0.001) title "Пермаллой"

# plot data with yerrorbars
# linetype 7 is a simple line, linecolor 0 is line color

plot "silver_1.dat" using 1:2:3 title "0.2 A" linetype 7 linecolor 0 with yerrorbars,

# load and run script file

load "scriptname.gp" 

# setting axis range
set xrange [-10:10]
