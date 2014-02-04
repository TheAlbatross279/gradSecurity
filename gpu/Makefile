CFLAGS = -pg -g
CC= gcc
FLAGS= -o

rsa-gpu: cuda-rsa.o
	$(CC) $(FLAGS) cudaRSA cuda-rsa.o $(CFLAGS)
main-rsa: cuda-rsa.o
	$(CC) cuda-rsa.c $(CFLAGS)

rsa_cpu: rsaCrack.o gmpFuncts.o rsa.o
	$(CC)  $(FLAGS) rsaCrack rsaCrack.o gmpFuncts.o rsa.o -I/home/clupo/gmp/include/ -L/home/clupo/gmp/lib $(CFLAGS)
main: rsaCrack.o
	$(CC)rsaCrack.c  -I/home/clupo/gmp/include/ -L/home/clupo/gmp/lib $(CFLAGS)

gmp_functs: gmpFucnts.o 
	$(CC) gmpFuncts.c  -I/home/clupo/gmp/include/ -L/home/clupo/gmp/lib $(CFLAGS)

rsa: rsa.o
	$(CC) rsa.c -I/home/clupo/gmp/include/ -L/home/clupo/gmp/lib $(CFLAGS)

clean:
	rm *.o ./rsaCrack
