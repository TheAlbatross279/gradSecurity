NCC=nvcc
NVFLAGS=-gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35
CFLAGS = -pg -g
CC= gcc
FLAGS= -O
lib= -L/home/clupo/gmp/lib
INC= -I/home/clupo/gmp/include
libL= -lgmp


rsa-cuda: cuda-rsa.c kernel-rsa.cu
	$(NCC) $(NVFLAGS) -o cudaRSA $^ $(CFLAGS)

rsa-gpu: cuda-rsa.o 
	$(CC) -o cudaRSA cuda-rsa.o $(CFLAGS)
main-rsa: cuda-rsa.c ./cuda-rsa-master/src/mpz/mpz.h 
	$(CC) $(FLAGS) cuda-rsa.c $(CFLAGS)
convert: convert.c
	$(CC) $(CFLAGS) $(INC) $(lib) convert.c $(libL)

rsa_cpu: rsaCrack.o gmpFuncts.o rsa.o
	$(CC) $(FLAGS)  $(include) $(lib) rsaCrack rsaCrack.o gmpFuncts.o rsa.o  $(CFLAGS)
main: rsaCrack.o
	$(CC)  $(include) $(lib) rsaCrack.c $(CFLAGS)
gmp_functs: gmpFucnts.o 
	$(CC)  $(include) $(lib) gmpFuncts.c $(CFLAGS)
rsa: rsa.o
	$(CC)  $(include) $(lib) rsa.c $(CFLAGS)


clean:
	rm *.o ./rsaCrack ./cudaRSA
