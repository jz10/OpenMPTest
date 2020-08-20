// Test case for global variable

#include "sdtio.h"

#pragma omp declare target
int a = 1;

int runtest() {
  return ++ a;
}
#pragma omp end declare target

int main(int argv) {
  int res = 0;

#pragma omp requires(unified_shared_memory)

#pragma omp target 
  res = runtest();

  printf(“a = %d; res = %d\n”, a, res); 

  // TODO: make assertion 

  return 0;
}
