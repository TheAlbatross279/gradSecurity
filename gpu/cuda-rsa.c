/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */
#include <stdio.h>
#include "rsaio.h"
#include "cuda-rsa.h"
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
      mpz_init(arr[i]);
      mpz_set_str(arr[i], buf);
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
   char *bit_arr = (char *)calloc(sizeof(char), BYTE_ARRAY_SIZE * 
    BYTE_ARRAY_SIZE);

  //copy key to device
   setUpKernel(arr, bit_arr);

   //generate keys from each pair 
   

  //output priavte keys that match
   //outputKeys(bit_arr, out_file);
   
  return 0;
}