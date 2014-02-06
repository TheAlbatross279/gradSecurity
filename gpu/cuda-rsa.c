/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */
#include <stdio.h>
#include "./cuda-rsa-master/src/mpz/mpz.h"
#include "cuda-rsa.h"


int main(int argc, char **argv) {
  //read in keys
   mpz_t hello;
   mpz_init(&hello);

//   printf("Keys:\n");
   FILE *keys_file = fopen("keys.txt", "r");
   FILE *out_file = fopen("outfile.txt", "w");
   
   //read file
   char buf[400];
   char buf2[1024];
   int i = 0;
   mpz_t *arr = (mpz_t *)calloc(sizeof(mpz_t), NUM_KEYS);
   if (!arr) {
      fprintf(stderr, "Calloc failed to allocate memory\n");
      exit(1);
   }
   
   printf("Reading in keys...\n");
   
   while(fgets(buf, 1024, keys_file) && i < NUM_KEYS) {
      mpz_init(&arr[i]);
      mpz_set_str(&arr[i], buf);
/*      mpz_get_str(&hello, buf2, 1024);
        fprintf(out_file, "%s\n", buf2);
      memset(buf2, 0, 1024);
*/
      memset(buf, 0, 400);
      i++;
   }
   fclose(keys_file);
   printf("done.\n");

   //create matrix for key -- calloc
   int *bit_arr = (int *)calloc(sizeof(int), BYTE_ARRAY_SIZE * 
    BYTE_ARRAY_SIZE);

  //copy key to device
   setUpKernel(arr, bit_arr);

  //output priavte keys that match
   
  return 0;
}
