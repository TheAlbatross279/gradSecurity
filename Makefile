CFLAGS = -lgmp 
CC= gcc
FLAGS= -o

all: rsaCrack.o gmpFuncts.o rsa.o
	$(CC)  $(FLAGS) rsaCrack rsaCrack.o gmpFuncts.o rsa.o $(CFLAGS)
main: rsaCrack.o
	$(CC)rsaCrack.c $(CFLAGS)

gmp_functs: gmpFucnts.o 
	$(CC) gmpFuncts.c $(CFLAGS)

rsa: rsa.o
	$(CC) rsa.c $(CFLAGS)
