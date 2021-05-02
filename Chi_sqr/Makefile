CXX = g++
SOURCE = ./source
INCLUDE = ./include
BINS = ./bin
SAMPLES = ./samples
CXXFLAGS = -Wall -g -Werror -O0 -I $(INCLUDE)
SOURCES = $(SOURCE)/main.cpp $(SOURCE)/calculations.cpp
HEADERS = $(HEADERS)/include
INSTALL = /usr/bin

all:
	$(CXX) $(CXXFLAGS) $(SOURCE)/main.cpp $(SOURCE)/calculations.cpp -o chi

install: all
	cp chi $(INSTALL)

clean:
	-rm $(SAMPLES)/coefficients.dat
	-rm $(BINS)/chi
	-rm -r chi.dSYM
	-rm coefficients.dat
