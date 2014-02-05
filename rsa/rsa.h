#define E 65537
void genreateKeys(mpz_t privateKey, mpz_t publicKey);
void getKeysWithPrimes(mpz_t p, mpz_t q, mpz_t publicKey, mpz_t privateKey);
void computeN(mpz_t p, mpz_t q, mpz_t n);
void totient(mpz_t prime1, mpz_t prime2, mpz_t n);
void generateN(mpz_t prime1, mpz_t prime2, mpz_t n);
void printPlaintext(mpz_t plaintext);
mpz_t getPrivateKey(mpz_t p, mpz_t modulii, mpz_t publicKey);
