CFLAGS = -lgmp -pg -g
CC= gcc
FLAGS= -o

rsa-gpu: cuda-rsa.o
	$(CC) $(FLAGS) cudaRSA cuda-rsa.o $(CFLAGS)
main-rsa: cuda-rsa.o
	$(CC) cuda-rsa.c $(CFLAGS)

rsa_cpu: rsaCrack.o gmpFuncts.o rsa.o
	$(CC)  $(FLAGS) rsaCrack rsaCrack.o gmpFuncts.o rsa.o $(CFLAGS)
main: rsaCrack.o
	$(CC)rsaCrack.c $(CFLAGS)

gmp_functs: gmpFucnts.o 
	$(CC) gmpFuncts.c $(CFLAGS)

rsa: rsa.o
	$(CC) rsa.c $(CFLAGS)

clean:
	rm *.o ./rsaCrack
