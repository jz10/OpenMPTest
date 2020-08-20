// Test case for global array

#include "sdtio.h"


#pragma omp declare target
int A[100];
#pragma omp end declare target

int main(int argv) {
#pragma omp requires(unified_shared_memory)
  A[99] = argv;

#pragma omp target 
#ifdef TEST_MAP
  map(always tofrom: A) 
#endif
  {
    A[99]++;
  }

  printf(“A[99] = %d\n”, A[99]); 

  // TODO: make assertion for A[99]

  return 0;
}
