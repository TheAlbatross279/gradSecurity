/*
 * Author: Kim Paterson
 * 1/25/14
 */


#include <gmp.h>

#include "gmpFuncts.h"

int main(int argc, char**argv) {
  printf("Generating random number\n");
  mpz_t rop;
  mpz_init(rop);
  genRandNum(rop);
 
  int isPrimeInt = isPrime(rop);
  mpz_t op;
  mpz_init(op);
  mpz_nextprime (op, rop);

  if (isPrimeInt) {
    printf("The number is prime.\n");
  } else {
    printf("The number is NOT prime.\n");
  }

  isPrimeInt = isPrime(op);
  if (isPrimeInt) {
    printf("The number is prime.\n");
  } else {
    printf("The number is NOT prime.\n");
  }

  
  printf("Checking RSA keys...\n");

  mpz_t n1, n2, n3, n4, n5, n6;
  mpz_init(n1);
  mpz_init(n2);
  mpz_init(n3);
  mpz_init(n4);
  mpz_init(n5);
  mpz_init(n6);

  printf("Opening files...\n");
  FILE *n1_file = fopen("n1.txt", "r");
  FILE *n2_file = fopen("n2.txt", "r");
  FILE *n3_file = fopen("n3.txt", "r");
  FILE *n4_file = fopen("n4.txt", "r");
  FILE *n5_file = fopen("n5.txt", "r");
  FILE *n6_file = fopen("n6.txt", "r");

  printf("Reading in files...\n");
  readMPZ(n1, n1_file);
  readMPZ(n2, n2_file);
  readMPZ(n3, n3_file);
  readMPZ(n4, n4_file);
  readMPZ(n5, n5_file);
  readMPZ(n6, n6_file);

  int i, j;
  mpz_t arr[6];
  for (i=0; i <6; i++) {
    mpz_init(arr[i]);
  }
  mpz_set (arr[0], n1);
  mpz_set (arr[1], n2);
  mpz_set (arr[2], n3);
  mpz_set (arr[3], n4);
  mpz_set (arr[4], n5);
  mpz_set (arr[5], n6);

  mpz_t gcd;
  mpz_init(gcd);
  int matches[2] = {-1, -1};

  for (i=0; i < 6; i++) {
    for (j=0; j < 6; j++) {
      if (i != j) {
        mpz_gcd (gcd, arr[i], arr[j]);
        if (mpz_cmp_ui(gcd, 1) != 0) {
          printf("gcd is prme: %d\n", isPrime(gcd));
          printf("%d, %d\n", i, j);
          printMPZ(gcd);
          matches[0] = i;
          matches[1] = j;
          break;
        }
      }

    }
  }

  char *files[6] = {"n1", "n2", "n3", "n4", "n5", "n6"};

  printf("RESULT: %s and %s have a common prime factor\n", files[matches[0]], files[matches[1]]);
  
  fclose(n1_file);
  fclose(n2_file);
  fclose(n3_file);
  fclose(n4_file);
  fclose(n5_file);
  fclose(n6_file);

  return 0;
}
