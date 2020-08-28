// Test case for global variable

#include "stdio.h"

#pragma omp declare target
int a = 1;

int runtest() {
  return ++ a;
}
#pragma omp end declare target

int main(int argv, char** argc) {
  int res = 0;

  // omp_set_default_device(0);

#pragma omp requires unified_shared_memory

#pragma omp target 
  res = runtest();

  printf("a = %d; res = %d\n", a, res); 

  // TODO: make assertion 

  return 0;
}
