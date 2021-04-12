CXX = g++
CXXFLAGS = -Wall -Werror -g -O0
SOURCES = main.cpp

all:
	$(CXX) $(CXXFLAGS) main.cpp -o tabgen

install: all
	cp tabgen /usr/bin/
