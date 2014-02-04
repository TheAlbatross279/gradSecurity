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
  while(mpz_inp_str(rop, keys_file, BASE_10) && i < NUM_KEYS) {
    mpz_init(arr[i]);
    mpz_set(arr[i], rop);
    i++;
//    mpz_init(rop);
  }
  fclose(keys_file);

  mpz_t gcd;
  mpz_init(gcd);
  int *matches[NUM_KEYS];

  for (i=0; i < NUM_KEYS; i++) {
    matches[i] = (int *)calloc(NUM_KEYS, sizeof(int));
    for (j=i+1; j < NUM_KEYS-1; j++) {
        mpz_gcd (gcd, arr[i], arr[j]);
        if (mpz_cmp_ui(gcd, 1) != 0) {
           matches[i][j] = 1;
        } 
    }
  }

  printf("done.\n");

  printf("Keys that match...\n");
  int count = 0;
//  FILE  *output = fopen("cpu-output.txt", "w");  
  for (i=0; i < NUM_KEYS; i++) {
    for (j=0; j < NUM_KEYS; j++) {
//      fprintf(output, "%d ", matches[i][j]);
      if (matches[i][j] == 1) {
        count++;
//             matches[j][i] = 1;
      }
    }
//    fprintf(output,"\n");
  }
  //fclose(output);
  printf("   Percent of matches: %.4f%%, %d/%d\n", ((double)count)/NUM_KEYS, count, NUM_KEYS);

  return 0;
}
