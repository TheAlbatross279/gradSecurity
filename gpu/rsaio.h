#include "./cuda-rsa-master/src/mpz/mpz.h"

#define E 65537
void getPrivateKey(mpz_t p, mpz_t modulii, mpz_t publicKey, mpz_t privateKey);
void getKeysWithPrimes(mpz_t p, mpz_t q, mpz_t publicKey, mpz_t privateKey);
void totient(mpz_t prime1, mpz_t prime2, mpz_t n);
void modExponentMPZ(mpz_t base, mpz_t exp, mpz_t mod, mpz_t result);
void outputKeys(int *bit_arr, FILE *outfile, int byte_array_size);
void outputPrivateKey(mpz_t privateKey, FILE *file);
void generateKeys(mpz_t modulii1, mpz_t modulii2, mpz_t privateKey);
