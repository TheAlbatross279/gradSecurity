#ifndef CUDA_RSA_H
#define CUDA_RSA_H

#include "bigInt.h"

#define NUM_KEYS 2
#define INT_ARRAY_SIZE 6250
#define BASE_10 10


void setUpKernel(bigInt *arr, int *bitMatrix);

bigInt testKernel(bigInt x);


#endif 
