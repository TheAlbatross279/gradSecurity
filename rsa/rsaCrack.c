/*
 * Author: Kim Paterson
 * 1/25/14
 */


#include <gmp.h>
#include "rsa.h"
#include "gmpFuncts.h"

int main(int argc, char**argv) {
  printf("Generating random number...\n");
  mpz_t rop;
  mpz_init(rop);
  genRandNum(rop);
  printf("done.\n");
  printf("Checking RSA keys...\n");

  mpz_t n1, n2, n3, n4, n5, n6;
  mpz_init(n1);
  mpz_init(n2);
  mpz_init(n3);
  mpz_init(n4);
  mpz_init(n5);
  mpz_init(n6);


  FILE *n1_file = fopen("n1.txt", "r");
  FILE *n2_file = fopen("n2.txt", "r");
  FILE *n3_file = fopen("n3.txt", "r");
  FILE *n4_file = fopen("n4.txt", "r");
  FILE *n5_file = fopen("n5.txt", "r");
  FILE *n6_file = fopen("n6.txt", "r");

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
    for (j=i+1; j < 6; j++) {
        mpz_gcd (gcd, arr[i], arr[j]);
        if (mpz_cmp_ui(gcd, 1) != 0) {
          matches[0] = i;
          matches[1] = j;
          break;
        }
    }
    if (matches[1] != -1) {
      break;
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
  printf("done.\n");

  printf("Testing RSA decrypt...\n");
  //read in ciphertext
  FILE *c_file = fopen("ciphertext.txt", "r");
  mpz_t ciphertext;
  mpz_init(ciphertext);
  readMPZ(ciphertext, c_file);
  fclose(c_file);
  

  mpz_t privateKey, publicKey, plaintext;
  mpz_init(privateKey);
  mpz_init(publicKey);
  mpz_init(plaintext);
  
  mpz_set_ui(publicKey, E);


  printf("Decrypting...\n");
  //get n
  mpz_t n;
  mpz_init(n);
  
  mpz_t p, q;
  mpz_init(p);
  mpz_init(q);

  mpz_set(p, gcd);
  //product divided by prime
  //n2/p = q
  mpz_tdiv_q_ui(q, n2, p);
  //q is now other prime
  
  //get keys
  getKeysWithPrimes(p, q, publicKey, privateKey);
  totient(p, q, n);
  decrypt(plaintext, privateKey, n, ciphertext);

  printPlaintext(plaintext);
  
  return 0;
}
