void shiftRight(int countOfInts, ints*) {
   for(int i = 0; i < countOfInts - 1; i++) {
      ints[i] >> 1;
      int bit = ints[i + 1] & 1;
      if (bit) {
         ints[i] | 1 << 31;
      }
   } 
   ints[countOfInts - 1] >> 1;
}

void shiftLeft(int countOfInts, ints*) {
   for(int i = countOfInts - 1; i > 0; i--) {
      ints[i] << 1;
      if(ints[i - 1] & (1 << 31)) {
         ints[i] | 1;
      }
   }
   ints[0] << 1;
}

int greaterThanOrEqualTo(int *a, int *b, int numWords)
{
   for(int i = numWords - 1; i >= 0; i--) {
      if(a[i] == b[i]) {
         continue;
      }
      int minimum = min(a[i], b[i]);
      if(minimum == a[i]) {
         return false;
      } else {
         return true;
      }
   }
   return true;
}
