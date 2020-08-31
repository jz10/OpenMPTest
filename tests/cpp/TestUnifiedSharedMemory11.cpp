// Test case for task dependency

#include "stdio.h"

#pragma omp declare target
struct CustomizedDataStructure {
  int x;
  int* data;
} A[100];
#pragma omp end declare target

int main(int argv, char** argc) {
  // omp_set_default_device(0);

#pragma omp requires unified_shared_memory

  int data[100];

#pragma omp task depend (out:A) 
  for (int i = 0; i < 100; i ++) {
    A[i].x = argv * i;
    data[i] = i;
    A[i].data = &data[i];
  }

#pragma omp target nowait depend(in: A)
  #pragma omp teams distribute parallel for
  for (int i = 0; i < 100; i ++) {
    * (A[i].data) += A[i].x;
  }

#pragma omp taskwait

  printf("A[99].x = %d and A[99].data = %d\n", A[99].x, * A[99].data); 

  // TODO: make assertion for A

  return 0;
}
