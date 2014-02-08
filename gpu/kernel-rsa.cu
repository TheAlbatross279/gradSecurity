/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */

#include <stdio.h>

#define BLOCK_SIZE 32
#define GRID_SIZE 200

//extern "C" {
#include "cuda-rsa.h"
//}


/*This macro was taken from the book CUDA by example.*/
static void HandleError(cudaError_t err, const char *file, int line ) { 
   if (err != cudaSuccess) {
      printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
      exit(1);
   }   
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))


/*This function shifts x to the right by one bit.*/
__global__ void parallelShiftR1(uint32_t *x) {
   unsigned int carry;

   if (threadIdx.x) {
      carry = x[threadIdx.x - 1];
   }
   
   x[threadIdx.x] = (x[threadIdx.x] >> 1) | (carry << 31);
}


/* Returns 1 if x >= y*/
__device__ int parallelGeq(uint32_t *x, uint32_t *y) {
   __shared__ int pos;

   if (threadIdx.x == 0) {
      pos = 31;
   }

   if (x[threadIdx.x] != y[threadIdx.x]) {
      atomicMin(&pos, threadIdx.x);
   }
   return x[pos] >= y[pos];
}

/*This function doese parrallel subtraction on x and y and stores the 
  result into result.*/
__device__  void parallelSubtract(uint32_t *result, uint32_t *x, 
 uint32_t *y) {
   __shared__ uint32_t borrows[32];
   uint32_t t;

   if (!threadIdx.x) 
      borrows[31] = 0;
   
   t = x[threadIdx.x] - y[threadIdx.x];

   if (threadIdx.x)
      borrows[threadIdx.x - 1] = (t > x[threadIdx.x]);

   while (__any(borrows[threadIdx.x])) {
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

__device__ int gcd(uint32_t *x, uint32_t *y) {
   
   /*while (__any(x[threadIdx.x])) {
      while ((x[31] & 1) == 0) {
         parallelShiftR1(x);
      }
      while ((y[31] & 1) == 0) {
         parallelShiftR1(y);
      }
      if (parallelGeq(x, y)) {
         parallelSubtract(x, x, y);
         parallelShiftR1(x);
      }
      else {
         parallelSubtract(y, y, x);
         parallelShiftR1(y);
      }  
   }
   parallelShiftR1(y);*/
   return __any(y[threadIdx.x]);
}


bigInt testKernel(bigInt x) {
   dim3 dimGrid(1);
   dim3 dimBlock(32);

   bigInt *xD;
   bigInt result;
   int *rD;

   HANDLE_ERROR(cudaMalloc(&xD, sizeof(bigInt)));     

   HANDLE_ERROR(cudaMemcpy(xD, &x, sizeof(bigInt), cudaMemcpyHostToDevice));
   
   parallelShiftR1<<<dimGrid, dimBlock>>>(xD->values);

   HANDLE_ERROR(cudaMemcpy(&result, xD, sizeof(bigInt), 
    cudaMemcpyDeviceToHost));

   cudaFree(xD);

   return result;
}
/*Sets up the GPU for the kernel call.*/
extern "C"
void setUpKernel(bigInt *arr, uint32_t *bitVector) {
   dim3 dimGrid(GRID_SIZE);
   dim3 dimBlock(BLOCK_SIZE);

   bigInt *arrD;
   uint32_t *bitRowD;
   
   int count = 0, ndx = 0, byteOffset = 0;
   int keyArrSize = sizeof(bigInt) * NUM_KEYS;   

   /*Allocate space on device for bitMatrix, and keys*/
   HANDLE_ERROR(cudaMalloc(&arrD, sizeof(bigInt) * NUM_KEYS));
   HANDLE_ERROR(cudaMalloc(&bitRowD, sizeof(uint32_t) * INT_ARRAY_SIZE));

   /*Copy keys onto device*/
   HANDLE_ERROR(cudaMemcpy(arrD, arr, keyArrSize, cudaMemcpyHostToDevice));

   while(ndx < NUM_KEYS) {
      /*Clear the bit vector row*/
      //HANDLE_ERROR(cudaMemset(bitRowD, 0, ROW_SIZE));

      /*Launch Kernel*/
      printf("launching kernel\n");
      //findGCD<<<dimGrid, dimBlock>>>(arrD, ndx, bitRowD);
      printf("back from kernel\n");
      /*Copy computed bit vector into bit matrix*/
      //HANDLE_ERROR(cudaMemcpy(bitMatrix + byteOffset, bitRowD, ROW_SIZE, 
       //cudaMemcpyDeviceToHost));
      byteOffset += 2;
      //count += KEYS_PER_KERNEL;
      if (count > NUM_KEYS) {
         count = 0; 
         ndx++;
      }
   }
}

