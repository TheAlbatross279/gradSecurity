#ifndef BIG_INT_H
#define BIG_INT_H
#ifndef GMP
#define GMP
#include <gmp.h>
#endif
#include <stdint.h>

typedef struct {
   uint32_t values[32];
} bigInt;

void convertMPZtoInt(mpz_t integer, uint32_t *toFill);
void convertIntToMPZ(uint32_t *integer, mpz_t toFill);
#endif
