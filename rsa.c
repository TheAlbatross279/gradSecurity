/* Textbook RSA
 * Author: Kim Paterson
 * 1/25/14
 */

#define E 65537
#include <gmp.h>
#include "gmpFuncts.h"
#include "rsa.h"

void genreateKeys(mpz_t privateKey, mpz_t publicKey) {
  //generate two primes
  mpz_t prime1, prime2;
  mpz_init(prime1);
  mpz_init(prime2);

  genRandNum(prime1);
  if(!isPrime(prime1)) {
    mpz_nextprime(prime1, prime1);
  }
  genRandNum(prime2);
  if(!isPrime(prime2)) {
    mpz_nextprime(prime2, prime2);
  }

  mpz_t n;
  mpz_init(n);
  //compute totient
  totient(prime1, prime2, n);
  
  //compute d/private key
  mpz_t neg_one;
  mpz_init(neg_one);
  mpz_set_ui(neg_one, -1);

  mpz_set_ui(publicKey, E);

  //set privateKey
  modExponentMPZ(publicKey, neg_one, n, privateKey);
  
}

void totient(mpz_t prime1, mpz_t prime2, mpz_t n) {
  //totient(n) = totient(p)*totient(q) = (p-1)(q-1)
  unsigned long int one = 1;
  mpz_t p, q;
  mpz_init(p);
  mpz_init(q);

  //subtract one from each 
  mpz_sub_ui(p, prime1, one);
  mpz_sub_ui(q, prime2, one);

  //(p-1)(q-1)
  mpz_mul(n, p, q);
  
}

void encrypt() {
  
}

void decrypt() {


}

void generateN(mpz_t prime1, mpz_t prime2, mpz_t n) {
  mpz_mul(n, prime1, prime2);
}
