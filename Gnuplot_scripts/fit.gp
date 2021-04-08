# Use for fitting data and calculating coefficients


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

plot f(x) title TITLE
