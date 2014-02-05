/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */
#include <stdio.h>
#include "./cuda-rsa-master/src/mpz/mpz.h"
#define NUM_KEYS 6
#define BYTE_ARRAY_SIZE 25000

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

   mpz_t arr[NUM_KEYS];
   
   printf("Reading in keys...\n");
   
   while(fgets(buf, 1024, keys_file) && i < NUM_KEYS) {
      mpz_init(arr[i]);
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

   //create row for key -- calloc
   char *bit_arr[25000];

  //copy key to device

  //output priavte keys that match
  return 0;
}
