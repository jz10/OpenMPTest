// Test case for std data structure

#include "stdio.h"

#pragma omp requires unified_shared_memory

#pragma omp declare target
struct CustomizedDataStructure {
  int x;
  int* data;
} A[100];
#pragma omp end declare target

int main(int argv, char** argc) {
  // omp_set_default_device(0);

  // #pragma omp requires unified_shared_memory

  int data[100];
  for (int i = 0; i < 100; i ++) {
    A[i].x = argv * i;
    data[i] = i;
    A[i].data = &data[i];
  }

#pragma omp target teams distribute parallel for
  for (int i = 0; i < 100; i ++) {
    * (A[i].data) += A[i].x;
  }

  printf("A[99].x = %d and A[99].data = %d\n", A[99].x, * A[99].data); 

  // TODO: make assertion for A

  return 0;
}
