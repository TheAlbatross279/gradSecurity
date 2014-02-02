/*
 * Author: Kim Paterson
 * 1/25/14
 */

#include <gmp.h>
#include "rsa.h"
#include "gmpFuncts.h"
#define NUM_KEYS 200000

int main(int argc, char**argv) {

  printf("Checking RSA keys...\n");
  FILE *keys_file = fopen("keys.txt", "r");

  mpz_t rop;
  mpz_init(rop);
  mpz_t arr[NUM_KEYS];
  int j, i = 0;
  
  // initialize array
  while(mpz_inp_str(rop, keys_file, BASE_10)) {
    mpz_init(arr[i]);
    i++;
    mpz_set(arr[i], rop);
  }


  mpz_t gcd;
  mpz_init(gcd);
  int matches[NUM_KEYS][NUM_KEYS];

  for (i=0; i < NUM_KEYS; i++) {
    for (j=i+1; j < NUM_KEYS; j++) {
        mpz_gcd (gcd, arr[i], arr[j]);
        if (mpz_cmp_ui(gcd, 1) != 0) {
           matches[i][j] = 1;
        } else {
           matches[i][j] = 0;
        }
    }
  }

  printf("done.\n");

  printf("Keys that match...\n");
  int count = 0;
  
  for (i=0; i < NUM_KEYS; i++) {
       for (j=0; j < NUM_KEYS; j++) {
          printf("%d, ", matches[i][ij]);
          if (matches[i][j]) {
             count++;
          }
          
       }
       printf("\n");
  }

  printf("\n\n% of matches: %f\n", (double)count/NUM_KEYS);

  return 0;
}
