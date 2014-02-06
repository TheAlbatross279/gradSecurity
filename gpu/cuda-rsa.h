#ifndef CUDA_RSA_H
#define CUDA_RSA_H

#define NUM_KEYS 200000
#define BYTE_ARRAY_SIZE 6250

void setUpKernel(mpz_t *arr, int *bitMatrix);


#endif 
