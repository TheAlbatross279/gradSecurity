#ifndef CUDA_RSA_H
#define CUDA_RSA_H

#define NUM_KEYS 200000
#define BYTE_ARRAY_SIZE 25000

void setUpKernel(mpz_t *arr, char *bitMatrix);


#endif 