/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */

#include <stdio.h>
#include "./cuda-rsa-master/src/mpz/mpz.h"

extern "C" {
#include "cuda-rsa.h"
}


/*This macro was taken from the book CUDA by example.*/
static void HandleError(cudaError_t err, const char *file, int line ) { 
   if (err != cudaSuccess) {
      printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
      exit(1);
   }   
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))


__global__ void findGCD(mpz_t *arrD, int keyPos, char *bitRowD) {
   /*Move key to be gcd'd into sharedMem*/
   __shared__ mpz_t key;
   mpz_init(&key);
   mpz_set(&key, &arrD[keyPos]);
   int toComp = blockIdx.x * blockDim.x + threadIdx.x;
   char mask = 1 << (toComp % sizeof(char));
   mpz_t a, b, c, quo, one;
   
   mpz_init(&one);
   mpz_init(&a);
   mpz_init(&b);
   mpz_set_ui(&one, 1);
   mpz_init(&quo);
   mpz_init(&c);
   mpz_set(&a, &key);
   mpz_set(&b, &arrD[toComp]);

   if (toComp > keyPos) {
      while(!digits_is_zero(a.digits, a.capacity)) {
         mpz_set(&c, &a);
         mpz_div(&quo, &a, &b, &a);
         mpz_set(&b, &c);
      }
     
      if (mpz_compare(&one, &b)) {
      /*GCD greater than one was found*/
         bitRowD[toComp / sizeof(char)] |= mask;
      }
   }
   
}

/*Sets up the GPU for the kernel call.*/
extern "C"
void setUpKernel(mpz_t *arr, char *bitMatrix) {
   /*Set up kernel to run 200000 threads*/
   dim3 dimGrid(2000);
   dim3 dimBlock(100);

   mpz_t *arrD;
   char *bitRowD;
   int count = 0, keyArrSize = sizeof(mpz_t) * NUM_KEYS;
   int rowSize = sizeof(char) * BYTE_ARRAY_SIZE;
   
   /*Allocate space on device for bitMatrix, and keys*/
   HANDLE_ERROR(cudaMalloc(&arrD, keyArrSize));
   HANDLE_ERROR(cudaMalloc(&bitRowD, rowSize));
   
   /*Copy keys onto device*/
   HANDLE_ERROR(cudaMemcpy(arrD, arr, keyArrSize, cudaMemcpyHostToDevice));
     
   while(count < NUM_KEYS) {
      /*Clear the bit vector row*/
      HANDLE_ERROR(cudaMemset(bitRowD, 0, rowSize));
      
      /*Launch Kernel*/
      printf("launching kernel\n");
      findGCD<<<dimGrid, dimBlock>>>(arrD, count, bitRowD);
      printf("back from kernel\n");
      /*Copy computed bit vector into bit matrix*/
      HANDLE_ERROR(cudaMemcpy(bitMatrix + (count * BYTE_ARRAY_SIZE), 
       bitRowD, rowSize, cudaMemcpyDeviceToHost));

      count = NUM_KEYS;
   }
}

