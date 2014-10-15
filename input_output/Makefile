# A simple makefile for CSE 100 P3

CC=g++
CXXFLAGS=-g
LDFLAGS=-g

all: driver

driver: BitInputStream.o BitOutputStream.o

BitOutputStream.o: BitOutputStream.hpp

BitInputStream.o: BitInputStream.hpp

clean:
	rm -f driver *.o core*
