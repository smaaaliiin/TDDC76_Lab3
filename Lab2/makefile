 #
 # FILNAMN:       makefile
 # LABORATION:    Lab 2
 # PROGRAMMERARE: Björn Wilke, 870617-0415, Ii#a
 #                Malin Aspelin, 910527-5524, FyN3
 # DATUM:         2014-10-05
 #
 # BESKRIVNING 
 # Makefli som kompilerar våra filer "lab2.cc" och "monetary.cc" och skapar
 # en körbar fil, "lab2".
 #

    CCC = g++
CCFLAGS = -g -std=c++11 -pedantic -Wall -Wextra -Werror
LDFLAGS = -L/sw/gcc-${GCC4_V}/lib -static-libstdc++


lab2: lab2.o Monetary.o
	$(LINK.cc) lab2.o Monetary.o -o lab2

lab1-5.o: lab2.cc
	$(CCC) $(CCFLAGS) -c lab2.cc

List.o: Monetary.cc
	$(CCC) $(CCFLAGS) -c Monetary.cc

# Städa arbetsmappen
clean:
	@ \rm -f *.o
