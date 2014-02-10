/* Brady Thomas & Kim Paterson
 * CSC 419/556 Cuda-RSA 
 * Feb, 2014
 * 
 * Cuda-rsa code licensed from https://github.com/dmatlack/cuda-rsa
 */

#include <stdio.h>

#define BLOCK_SIZE 32
#define GRID_SIZE 4096

#include "cuda-rsa.h"


/*This macro was taken from the book CUDA by example.*/
static void HandleError(cudaError_t err, const char *file, int line ) { 
   if (err != cudaSuccess) {
      printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
      exit(1);
   }   
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))


/*This function shifts x to the right by one bit.*/
__device__ void parallelShiftR1(uint32_t *x) {
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

   if (!threadIdx.x) {
      borrows[31] = 0;
   }
   
   t = x[threadIdx.x] - y[threadIdx.x];

   if (threadIdx.x) {
      borrows[threadIdx.x - 1] = (t > x[threadIdx.x]);
   }

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

__device__ void gcd(uint32_t *x, uint32_t *y, int *res) {
   /*__shared__ uint32_t x[32];
   __shared__ uint32_t y[32];

   x[threadIdx.x] = x1[threadIdx.x];
   y[threadIdx.x] = y1[threadIdx.y];*/
   
   while (__any(x[threadIdx.x])) {
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
   parallelShiftR1(y);
   *res = __any(y[threadIdx.x]);
}

__global__ void doGCD(bigInt *keys, int toComp, int start, 
 uint32_t *vector, bigInt *comp, bigInt *comp2) {
   int res;
   if (start + blockIdx.x < NUM_KEYS) {
      comp[blockIdx.x].values[threadIdx.x] = 
       keys[toComp].values[threadIdx.x];
      comp2[blockIdx.x].values[threadIdx.x] = 
       keys[start + blockIdx.x].values[threadIdx.x];
      gcd(comp[blockIdx.x].values, comp2[blockIdx.x].values, &res);
      if (res) {
         if (threadIdx.x == 0) {
           //printf("FOUND A KEY at: %d, %d\n", toComp, start + blockIdx.x);
            atomicOr(&vector[(blockIdx.x + start) / 32], 1 << 
             ((blockIdx.x + start) % 32));
            atomicOr(&vector[toComp / 32], 1 << (toComp % 32));
         }
      }
   }
}

/*Sets up the GPU for the kernel call.*/
int setUpKernel(bigInt *arr, uint32_t *bitVector, int **indexs) {
   dim3 dimGrid(GRID_SIZE);
   dim3 dimBlock(BLOCK_SIZE);

   bigInt *arrD, *compD, *comp2D;
   uint32_t *bitVectorD;

   
   int count = 1, ndx = 0;
   int keyArrSize = sizeof(bigInt) * NUM_KEYS; 
   int bitVecSize = sizeof(uint32_t) * INT_ARRAY_SIZE;  
   
   /*Allocate space on device for bitMatrix, and keys*/
   HANDLE_ERROR(cudaMalloc(&arrD, keyArrSize));
   HANDLE_ERROR(cudaMalloc(&bitVectorD, bitVecSize)); 
   HANDLE_ERROR(cudaMalloc(&compD, sizeof(bigInt) * GRID_SIZE));
   HANDLE_ERROR(cudaMalloc(&comp2D, sizeof(bigInt) * GRID_SIZE));
   HANDLE_ERROR(cudaMemset(bitVectorD, 0, bitVecSize));
   
   /*Copy keys onto device*/
   HANDLE_ERROR(cudaMemcpy(arrD, arr, keyArrSize, cudaMemcpyHostToDevice));

   while(ndx < NUM_KEYS - 1) {
      //printf("ndx: %d, start: %d\n", ndx, count);
      doGCD<<<dimGrid, dimBlock>>>(arrD, ndx, count, bitVectorD, compD, comp2D);
      count += GRID_SIZE;
      if (count >= NUM_KEYS) {
         ndx++;
         count = ndx + 1;
      }
   }

   HANDLE_ERROR(cudaMemcpy(bitVector, bitVectorD, bitVecSize, 
    cudaMemcpyDeviceToHost));
   
   uint32_t mask;
   int total = 0;
   int inCount = 0;

   for (count = 0; count < INT_ARRAY_SIZE; count++) {
      for (inCount = 0; inCount < 32; inCount++) {
         mask = 1 << inCount;
         if (bitVector[count] & mask) {
            total++;
            //printf("key location: %d\n", (count * 32) + inCount);
            //printf("count: %d, inCound: %d\n", count, inCount);
            
         }
      }
   }
   *indexs = (int *)calloc(total, sizeof(int));
   if (!indexs) {
      perror("calloc");
      exit(1);
   }

   int pairs = 0;
   for (count = 0; count < INT_ARRAY_SIZE; count++) {
      for (inCount = 0; inCount < 32; inCount++) {
         mask = 1 << inCount;
         if (bitVector[count] & mask) {
            //printf("key location: %d\n", (count * 32) + inCount);
            indexs[0][pairs++] = (count * 32) + inCount;
         }
      }
   }

   for (count = 0; count < total; count++) {
      printf("count: %d ndx: %d\n", count, indexs[0][count]);
   }
 
   printf("total: %d\n", total);
   return total;
}

