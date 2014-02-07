/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */
#include <stdio.h>
#include <stdlib.h>
#include "rsaio.h"
#include "cuda-rsa.h"
#include "bigInt.h"

#ifndef GMP
#define GMP
#include <gmp.h>
#endif
int main(int argc, char **argv) {
  //read in keys

//   printf("Keys:\n");
   FILE *keys_file = fopen("keys.txt", "r");
   FILE *out_file = fopen("outfile.txt", "w");
   
   //read file

   int i = 0;
   mpz_t *arr = (mpz_t *)calloc(sizeof(mpz_t), NUM_KEYS);
   if (!arr) {
      fprintf(stderr, "Calloc failed to allocate memory\n");
      exit(1);
   }
   mpz_t rop;
   mpz_init(rop);
   printf("Reading in keys...\n");
   while(mpz_inp_str(rop, keys_file, BASE_10) && i < NUM_KEYS) {
     if (!arr[i]) {
       perror("malloc");
       exit(1);
     }
     mpz_init(arr[i]);
     mpz_set(arr[i], rop);
     i++;
   }
   mpz_clear(rop);

   fclose(keys_file);
   printf("done.\n");

   //create matrix for key -- calloc
   int *bit_arr = (int *)calloc(sizeof(int), BYTE_ARRAY_SIZE * 
    BYTE_ARRAY_SIZE);

   //convert to our big-integer format
   for (i=0; i < NUM_KEYS; i++) {
     
   }

  //copy key to device
//   setUpKernel(arr, bit_arr);

   //generate keys from each pair 
   

  //output priavte keys that match
   //outputKeys(bit_arr, out_file);
   
  return 0;
}
