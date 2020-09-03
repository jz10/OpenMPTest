// Test case for std data structure

#include "stdio.h"

#include <vector>

using namespace std;

#pragma omp requires unified_shared_memory

#pragma omp declare target
struct CustomizedDataStructure {
  int x;
  int y;
} A[100];
#pragma omp end declare target

int main(int argv) {
  // omp_set_default_device(0);

  // #pragma omp requires unified_shared_memory
  A[99].x = argv ++;
  A[99].y = argv;

  CustomizedDataStructure *ptr = &A[0];

#pragma omp target 
#ifdef TEST_MAP
  map(always tofrom: IntVec) 
#endif
  {
    ptr += 99;
    ptr->x ++;
    ptr->y ++;
  }

  printf("A[99].x = %d and A[99].y = %d\n", A[99].x, A[99].y); 

  // TODO: make assertion for A

  return 0;
}
