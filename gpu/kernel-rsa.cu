/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */

#include <stdio.h>
#include "./cuda-rsa-master/src/mpz/mpz.h"

#define ROW_SIZE 8
#define KEYS_PER_KERNEL 64

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


/*Device function that returns zero if the int passed is zero and 1 if
  the int passed is nonzero*/
__device__ int parallelNonZero(int *x) {
   if (__any(x[threadIdx.x]))
      return 1;
   return 0;
}


/*This function doese parrallel subtraction on x and y and stores the 
  result into result.*/
__device__ void parallelSubtract(int *result, int *x, int *y) {
   unsigned int borrows[32];
   unsigned int t;

   if (!threadIdx.x) 
      borrows[31] = 0;
   
   t = x[threadIdx.x] - y[threadIdx.x];

   if (threadIdx.x)
      borrows[threadIdx.x - 1] = (t > x[threadIdx.x]);

   while (parallelNonZero(borrows)) {
      if (borrows[threadIdx.x]) {
         t--;
      }
      
      if (threadIdx.x) {
         borrows[threadIdx.x - 1] = (t == 0xffffffffU && 
          borrows[threadIdx.x]);
      }
   }
   result[threadIdx.x] = t;
}

__global__ void findGCD(mpz_t *arrD, int keyPos, int *bitRowD) {
   /*Move key to be gcd'd into sharedMem*/
   __shared__ mpz_t key;
   mpz_init(&key);
   mpz_set(&key, &arrD[keyPos]);
   int toComp = blockIdx.x * blockDim.x + threadIdx.x;
   int mask = 1 << (toComp % sizeof(int));
   mpz_t a, b, c, quo, one;
   
   mpz_init(&one);
   mpz_init(&a);
   mpz_init(&b);
   mpz_set_ui(&one, 1);
   mpz_init(&quo);
   mpz_init(&c);
   mpz_set(&a, &key);
   mpz_set(&b, &arrD[toComp + keyPos]);

   if (toComp + keyPos > keyPos && toComp + keyPos < NUM_KEYS) {
      while(!digits_is_zero(a.digits, a.capacity)) {
         mpz_set(&c, &a);
         mpz_div(&quo, &a, &b, &a);
         mpz_set(&b, &c);
      }
     
      if (mpz_compare(&one, &b)) {
      /*GCD greater than one was found*/
         atomicOr(&bitRowD[toComp / sizeof(int)], mask);
      }
   }
   
}

/*Sets up the GPU for the kernel call.*/
extern "C"
void setUpKernel(mpz_t *arr, int *bitMatrix) {
   /*Set up kernel to run 200000 threads*/
   dim3 dimGrid(8);
   dim3 dimBlock(8);

   mpz_t *arrD;
   int *bitRowD;
   int count = 0, keyArrSize = sizeof(mpz_t) * NUM_KEYS;
   //int rowSize = 80; //sizeof(char) * BYTE_ARRAY_SIZE;
   int byteOffset = 0;
   int ndx = 0;
   
   /*Allocate space on device for bitMatrix, and keys*/
   HANDLE_ERROR(cudaMalloc(&arrD, keyArrSize));
   HANDLE_ERROR(cudaMalloc(&bitRowD, ROW_SIZE));
   
   /*Copy keys onto device*/
   HANDLE_ERROR(cudaMemcpy(arrD, arr, keyArrSize, cudaMemcpyHostToDevice));
     
   while(ndx < NUM_KEYS) {
      /*Clear the bit vector row*/
      HANDLE_ERROR(cudaMemset(bitRowD, 0, ROW_SIZE));
      
      /*Launch Kernel*/
      printf("launching kernel\n");
      findGCD<<<dimGrid, dimBlock>>>(arrD, ndx, bitRowD);
      printf("back from kernel\n");
      /*Copy computed bit vector into bit matrix*/
      HANDLE_ERROR(cudaMemcpy(bitMatrix + byteOffset, bitRowD, ROW_SIZE, 
       cudaMemcpyDeviceToHost));
      byteOffset += 2;
      count += KEYS_PER_KERNEL;
      if (count > NUM_KEYS) {
         count = 0; 
         ndx++;
      }
   }
}

