#-------------------------------------------------
#  FILE:   Makefile
#  AUTHOR: Simon Sedlacek
#  EMAIL:  xsedla1h@stud.fit.vutbr.cz
#  DATE:   5.4.2019
#  BRIEF:  IOS 2019 - second assignment - River Crossing Problem
#  NOTE: 
#-------------------------------------------------

CFLAGS=-std=gnu99 -Wall -Wextra -pedantic -g -pthread

all: proj2

proj2: proj2.o arguments.o resources.o process.o generate.o
	gcc $(CFLAGS) $^ -o $@

proj2.o: proj2.c
	gcc $(CLFAGS) -c -o $@ $<

arguments.o: arguments.c arguments.h
	gcc $(CLFAGS) -c -o $@ $<

resources.o: resources.c resources.h
	gcc $(CLFAGS) -c -o $@ $<

process.o: process.c process.h
	gcc $(CLFAGS) -c -o $@ $<

generate.o: generate.c generate.h
	gcc $(CLFAGS) -c -o $@ $<


.PHONY: clean
clean:
	rm -f *.o proj2
