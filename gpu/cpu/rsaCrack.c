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
#include <time.h>
#endif

#define NUM_KEYS 256

int main(int argc, char**argv) {
  printf("Checking RSA keys...\n");
  FILE *keys_file = fopen("../256-keys.txt", "r");

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

  mpz_t gcd, p, q, privateKey, publicKey;
  mpz_init(gcd);
//  int matches[NUM_KEYS][NUM_KEYS];
  int count = 0;
  mpz_init(privateKey);
  mpz_init(publicKey);
  //set public key
  mpz_set_ui(publicKey, E);
  FILE *badkeys = fopen("256-cpu-badkeys.txt", "w");


  mpz_init(p);
  mpz_init(q);
  time_t start = time(NULL);
  time_t end;
  for (i=0; i < NUM_KEYS-1; i++) {
    for (j=i+1; j < NUM_KEYS; j++) {
      mpz_gcd (gcd, arr[i], arr[j]);
        if (mpz_cmp_ui(gcd, 1) > 0) {
           count++;
           mpz_set(p, gcd);
           outputPrivateKey(arr[i], badkeys);
           getPrivateKey(p, q, arr[i], publicKey, privateKey);
           fprintf(badkeys, ":");
           outputPrivateKey(privateKey, badkeys);
           fprintf(badkeys, "\n");


           outputPrivateKey(arr[j], badkeys);
           fprintf(badkeys, ":");
           getPrivateKey(p, q, arr[j], publicKey, privateKey);
           outputPrivateKey(privateKey, badkeys);
           fprintf(badkeys, "\n");
        } 
    }
    if (i%100 == 0) {
      end = time(NULL);
      printf("reached %d modulii at %d time\n", i, (int)end-(int)start);
      start = time(NULL);
    }
  }
  fclose(badkeys);
  printf("done.\n");

  printf("Keys that match...\n");
  printf("   Percent of matches: %.4f%%, %d/%d\n", ((double)count)/NUM_KEYS, count, NUM_KEYS);

  return 0;
}

