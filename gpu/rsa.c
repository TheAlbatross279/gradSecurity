/* Textbook RSA
 * Author: Kim Paterson
 * 1/25/14
 */

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

  getKeysWithPrimes(prime1, prime2, publicKey, privateKey);
  
}

void getKeysWithPrimes(mpz_t p, mpz_t q, mpz_t publicKey, mpz_t privateKey) {
  mpz_t n;
  mpz_init(n);
  //compute totient
  totient(p, q, n);
  
  //compute d/private key
  mpz_t neg_one;
  mpz_init(neg_one);
  mpz_set_si(neg_one, -1);

  mpz_set_ui(publicKey, E);

  //set privateKey
  modExponentMPZ(publicKey, neg_one, n, privateKey);
  mpz_clear(neg_one);

}

void computeN(mpz_t p, mpz_t q, mpz_t n) {
     mpz_mul(n, p, q);
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
  mpz_clear(p);
  mpz_clear(q);
}

void encrypt(mpz_t plaintext, mpz_t publicKey, mpz_t n, mpz_t ciphertext) {
  modExponentMPZ(plaintext, publicKey, n, ciphertext); 
}

void decrypt(mpz_t plaintext, mpz_t privateKey, mpz_t n, mpz_t ciphertext) {
   modExponentMPZ(ciphertext, privateKey, n, plaintext);
}

void generateN(mpz_t prime1, mpz_t prime2, mpz_t n) {
  mpz_mul(n, prime1, prime2);
}

void printPlaintext(mpz_t plaintext) {
   size_t count = 1024;
   char *buffer = (char *)calloc(count, sizeof(char));
   
   mpz_export((void*)buffer, &count, 1, sizeof( char), 1, 0, plaintext);
   printf("%s\n", buffer);
}

void getPrivateKey(mpz_t p, mpz_t q, mpz_t modulii, mpz_t publicKey, mpz_t privateKey) {
  
  mpz_cdiv_q(q, modulii, p);
  //q is now other prime

  //get keys
  getKeysWithPrimes(p, q, publicKey, privateKey);

}

void outputPrivateKey(mpz_t privateKey, FILE *file) {
  mpz_out_str(file, 10, privateKey);
}
