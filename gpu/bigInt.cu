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
  size_t temp = 32;
  mpz_export(toFill, &temp, 1, 4, 0, 0, integer);
}

void convertIntToMPZ(uint32_t *integer, mpz_t toFill) {
  int temp = 32;
  mpz_import(toFill, temp, 1, 4, 0, 0, integer);
}
