/* GMP integer functions 
 * Author: Kim Paterson
 * 1/25/14
 */
#define BASE_10 10
#include <stdio.h>
#include <stdlib.h>


void genRandNum(mpz_t rop);
int isPrime(mpz_t rop);
int getRandomPrime(mpz_t rop);
void printMPZ(mpz_t rop);
void readMPZ(mpz_t rop, FILE *filestream);
void writeMPZ(mpz_t rop, FILE *filestream);


void addMPZ(mpz_t rop1, mpz_t rop2, mpz_t result);
void subtractMPZ(mpz_t rop1, mpz_t rop2, mpz_t result);
void multMPZ(mpz_t rop1, mpz_t rop2, mpz_t result);
void modExponentMPZ(mpz_t a, mpz_t b, mpz_t c, mpz_t result);
