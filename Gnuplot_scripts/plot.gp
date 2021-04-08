# Use plotting command with points and yerrorbars

DATAFILE = ARG1
FIT = ARG2

COEFFS = "coefficients.dat"

CMD = sprintf("head -1 %s | awk '{print $1}'", COEFFS)

a = system(CMD);


CMD = sprintf("tail -1 %s | awk '{print $1}'", COEFFS)

b = system(CMD);

print "a = ", a
print "b = ", b

a = a + 0
b = b + 0

f(x) = a * x + b

TITLE = sprintf("y = %.3f * x + %.3f", a, b)

print TITLE

if (FIT eq "true") {
    print "Plotting line"
    plot DATAFILE using 1:2:3 notitle lt 7 lc 1 with yerrorbars, f(x) title TITLE
} else {
    print "No line plot"
    plot DATAFILE using 1:2:3 notitle lt 7 lc 1 with yerrorbars
}


