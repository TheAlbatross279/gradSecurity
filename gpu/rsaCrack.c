/*
 * Author: Kim Paterson
 * 1/25/14
 */

#include <gmp.h>
#include "rsa.h"
#include "gmpFuncts.h"
#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#include <stdio.h>
#endif

#define NUM_KEYS 200000

int main(int argc, char**argv) {
  printf("Checking RSA keys...\n");
  FILE *keys_file = fopen("keys.txt", "r");

  mpz_t rop;
  mpz_init(rop);

  mpz_t arr[NUM_KEYS];
  int j, i = 0;
  
  // initialize array
  while(mpz_inp_str(rop, keys_file, BASE_10) && i < NUM_KEYS) {
    mpz_init(arr[i]);
    mpz_set(arr[i], rop);
    i++;
//    mpz_init(rop);
  }
  fclose(keys_file);

  mpz_t gcd, p, privateKey, publicKey;
  mpz_init(gcd);
//  int matches[NUM_KEYS][NUM_KEYS];
  int count = 0;
  mpz_init(privateKey);
  mpz_init(publicKey);
  //set public key
  mpz_set_ui(publicKey, E);
  FILE *file = fopen("privateKeys.txt", "w");
  for (i=0; i < NUM_KEYS; i++) {
//    matches[i] = (int *)calloc(NUM_KEYS, sizeof(int));
    for (j=i+1; j < NUM_KEYS-2; j++) {
      mpz_init(p);
      mpz_gcd (gcd, arr[i], arr[j]);
        if (mpz_cmp_ui(gcd, 1) != 0) {
//           matches[i][j] = 1;
           count++;
           mpz_set(p, gcd);
           getPrivateKey(p, arr[i], publicKey, privateKey);

           outputPrivateKey(privateKey, file);
           fprintf(file, "\n");
        } 
    }
  }

  fclose(file);
  printf("done.\n");

  printf("Keys that match...\n");
  printf("   Percent of matches: %.4f%%, %d/%d\n", ((double)count)/NUM_KEYS, count, NUM_KEYS);

  return 0;
}

