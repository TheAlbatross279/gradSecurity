/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */
//#include "/home/clupo/gmp/mpz.h"
#include <gmp.h>
#include <stdint.h>
#include "rsaio.h"
#include "cuda-rsa.h"

void outputKeys(int *bad_keys, FILE *outfile, mpz_t *arr, int num_bad_keys) {
  int i = 0, j = 0;
  mpz_t gcd;
  mpz_init(gcd);

  mpz_t privateKey;
  mpz_init(privateKey);

  for (i=0; i < num_bad_keys; i++) {
     for (j=i+1; j < num_bad_keys; j++) {
        mpz_gcd (gcd, arr[bad_keys[j]], arr[bad_keys[i]]);
                   
        //if it's not 1, then output
        if (mpz_cmp_ui(gcd, 1) != 0) {
//           printf("%d and %d are bad keys\n", bad_keys[i], bad_keys[j]);
           //generate keys
           generateKeys(gcd, arr[bad_keys[i]], privateKey);
                      
           //output i key and private key
           outputPrivateKey(arr[bad_keys[i]], outfile);
           fprintf(outfile, ":");
           outputPrivateKey(privateKey, outfile);
           fprintf(outfile, "\n");

           //get j private key
           generateKeys(gcd, arr[bad_keys[j]], privateKey);
                
           //output j key and private key
           outputPrivateKey(arr[bad_keys[j]], outfile);
           fprintf(outfile, ":");
           outputPrivateKey(privateKey, outfile);
           fprintf(outfile, "\n");
        }
     }
  
  }
}
    

void outputPrivateKey(mpz_t privateKey, FILE *file) {
  mpz_out_str(file, 10, privateKey);
}

void generateKeys(mpz_t gcd, mpz_t modulii, mpz_t privateKey) {
  //set public key
  mpz_t publicKey;
  mpz_init(publicKey);
  mpz_set_ui(publicKey, E);  
  getPrivateKey(gcd, modulii, publicKey, privateKey);
  
}

void getPrivateKey(mpz_t p, mpz_t modulii, mpz_t publicKey, mpz_t privateKey) {
  mpz_t q;
  mpz_init(q);
  
  mpz_cdiv_q(q, modulii, p);
  //q is now other prime

  //get keys
  getKeysWithPrimes(p, q, publicKey, privateKey);

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

void modExponentMPZ(mpz_t base, mpz_t exp, mpz_t mod, mpz_t result) {
  mpz_powm (result, base, exp, mod);
}
