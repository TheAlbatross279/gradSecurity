/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */

#include <stdint.h>
#include <stdlib.h>
#include "bigInt.h"
#include "cuda-rsa.h"

void convertMPZtoInt(mpz_t integer, uint32_t *toFill) {
  //int *bigInt = (int *)calloc(sizeof(int), BYTE_ARRAY_SIZE);
  int temp = INT_ARRAY_SIZE;
  mpz_export(toFill, &temp, 1, 4, 0, 0, integer);
}
