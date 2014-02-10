#ifndef CUDA_RSA_H
#define CUDA_RSA_H

#include "bigInt.h"

#define NUM_KEYS 4096
#define INT_ARRAY_SIZE 128
#define BASE_10 10


int setUpKernel(bigInt *arr, uint32_t *bitMatrix);

#endif 
