NCC=nvcc
NVFLAGS=-gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35
CFLAGS = -pg -g
CC= gcc
FLAGS= -O -c
lib= -L/home/clupo/gmp/lib
INC= -I/home/clupo/gmp/include
libL= -lgmp


rsa-cuda: cuda-rsa.cu bigInt.cu kernel-rsa.cu 
	$(NCC) $(NVFLAGS) $(INC) -o cudaRSA $^ $(CFLAGS) $(lib) $(libL)

rsa-gpu: cuda-rsa.o bigInt.o rsaio.o
	$(CC) -o cudaRSA cuda-rsa.o bigInt.o rsaio.o $(CFLAGS) $(libL)
main-rsa: cuda-rsa.c 
	$(CC) $(FLAGS) cuda-rsa.c $(CFLAGS) $(libL)
key-rsa: rsaio.c
	$(CC) $(FLAGS) $(CFLAGS) rsaio.c $(libL) 
bigInt: bigInt.c
	$(CC) $(FLAGS) $(CFLAGS) bigInt.c $(libL) 

rsa_cpu: rsaCrack.o gmpFuncts.o rsa.o
	$(CC) -o rsaCrack rsaCrack.o gmpFuncts.o rsa.o  $(CFLAGS) $(libL)
main: rsaCrack.c
	$(CC) $(FLAGS) rsaCrack.c $(CFLAGS) $(libL)
gmp_functs: gmpFucnts.o 
	$(CC) $(FLAGS) gmpFuncts.c $(CFLAGS) $(libL)
rsa: rsa.c
	$(CC) $(FLAGS) rsa.c $(CFLAGS) $(libL)


clean:
	rm *.o ./rsaCrack ./cudaRSA
