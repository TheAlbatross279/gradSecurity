/* GMP integer functions 
 * Author: Kim Paterson
 * 1/25/14
 */

#include <gmp.h>
#include "gmpFuncts.h"
#include <time.h>
#define BIT_COUNT 512
#define REPS 25
#define BASE_10 10

/* Generate 512 bit pseudo-random number */
void genRandNum(mpz_t rop) {
  //Initialize state
  gmp_randstate_t state;
  gmp_randinit_mt(state);
  unsigned long int seed = time(NULL);
  gmp_randseed_ui(state, seed);

  //get random number
  mp_bitcnt_t n = BIT_COUNT;
  mpz_urandomb (rop, state, n);
}

/* Returns 1 or 0 if the number is probably prime */
int isPrime(mpz_t rop) {
  return mpz_probab_prime_p (rop, REPS);
}

/* Just prints the number to stdout */
void printMPZ(mpz_t rop) {
  gmp_printf("%Zd\n", rop);
}

/* Reads a large integer from disk */
void readMPZ(mpz_t rop, FILE *filestream) {
  size_t result = mpz_inp_str (rop, filestream, BASE_10);
}

/* Writes a large integer to disk */
void writeMPZ(mpz_t rop, FILE *filestream) {
  size_t result = mpz_out_str (filestream, BASE_10, rop);
}

/* Adds two large integers and stores result in 
 * result argument
 */
void addMPZ(mpz_t rop1, mpz_t rop2, mpz_t result) {
  mpz_add(result, rop1, rop2);
}

/* Subtracts two large integers and stores result in 
 * result argument
 */
void subtractMPZ(mpz_t rop1, mpz_t rop2, mpz_t result) {
  mpz_sub(result, rop1, rop2);
}

/* Multiplies two large integers and stores result in 
 * result argument
 */
void multMPZ(mpz_t rop1, mpz_t rop2, mpz_t result) {
  mpz_mul(result, rop1, rop2);
}

/* Performs modular exponentiation (i.e. a^b mod c) */
void modExponentMPZ(mpz_t base, mpz_t exp, mpz_t mod, mpz_t result) {
  mpz_powm (result, base, exp, mod);
}

/* Finds the GCD of two integers */
unsigned long int gcd (unsigned long int a, unsigned long int b)
{
  unsigned long int c;
  while (a != 0) {
    c = a;
    a = b%a; 
    b = c;
  }
  return b;
}
