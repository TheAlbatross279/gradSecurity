/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */
#include "bigInt.h"
#include "cuda-rsa.h"
#include <stdlib.h>
int *convertMPZtoInt(mpz_t integer) {
  int *bigInt = (int *)calloc(sizeof(int), BYTE_ARRAY_SIZE);
  int temp = BYTE_ARRAY_SIZE;
  return mpz_export(bigInt, &temp, 1, 4, 0, 0, integer);
}
