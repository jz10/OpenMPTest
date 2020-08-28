// Test case for pointer operation with target team and distribute parallel for

#include "stdio.h"


#pragma omp declare target
int A[100];
#pragma omp end declare target

int main(int argv, char** argc) {
  // omp_set_default_device(0);

#pragma omp requires unified_shared_memory
  A[99] = argv;

  int *ptr = &A[0];

#pragma omp target teams distribute parallel for
  for (int i = 0; i < 100; i ++) {
    int * localPtr = ptr + i; 
    (* localPtr) ++; 
  }

  printf("A[99] = %d\n", A[99]); 

  // TODO: make assertion for A[99]

  return 0;
}
