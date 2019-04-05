#-------------------------------------------------
#  FILE:   Makefile
#  AUTHOR: Simon Sedlacek
#  EMAIL:  xsedla1h@stud.fit.vutbr.cz
#  DATE:   5.4.2019
#  BRIEF:  
#  NOTE: 
#-------------------------------------------------

CFLAGS=-std=gnu99 -Wall -Wextra -pedantic -g

all: proj2

proj2: proj2.o arguments.o
	gcc $(CFLAGS) proj2.o arguments.o -o proj2

proj2.o: proj2.c
	gcc $(CLFAGS) -c -o proj2.o proj2.c

arguments.o: arguments.c arguments.h
	gcc $(CLFAGS) -c -o arguments.o arguments.c

.PHONY: clean

clean:
	rm -f *.o proj2
