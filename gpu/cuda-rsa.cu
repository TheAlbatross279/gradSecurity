/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */

#ifndef GMP
#define GMP
#include <gmp.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rsaio.h"
#include "cuda-rsa.h"
#include "bigInt.h"

int main(int argc, char **argv) {
  //read in keys

//   printf("Keys:\n");
   FILE *keys_file = fopen("test.txt", "r");
   FILE *out_file = fopen("outfile.txt", "w");
   
   //read file
   int i = 0;
   mpz_t *arr = (mpz_t *)calloc(sizeof(mpz_t), NUM_KEYS);
   if (!arr) {
      perror("calloc");
      exit(1);
   }

   //alloc array of keys
   bigInt *key_arr = (bigInt *)calloc(sizeof(bigInt), NUM_KEYS);
   if (!key_arr) {
      perror("calloc");
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
     convertMPZtoInt(rop, key_arr[i].values);
     //testing mpz

     i++;
   }


   if (!mpz_cmp(newRes, arr[1]))
      printf("Success!\n");

   fclose(keys_file);
   printf("done.\n");

   //create matrix for key -- calloc
   int *bit_arr = (int *)calloc(sizeof(int), INT_ARRAY_SIZE * 
    INT_ARRAY_SIZE);

  //copy key to device
//   setUpKernel(key_arr, bit_arr);

   //generate keys from each pair 
   

  //output priavte keys that match
   //outputKeys(bit_arr, out_file, INT_ARRAY_SIZE, arr);
   
  return 0;
}
