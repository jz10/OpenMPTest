// Test case for global variable

#include "stdio.h"
#include "omp.h"

#pragma omp requires unified_address

#pragma omp declare target
int runtest(int* arr, int idx) {
  return arr[idx + 1] ++;
}
#pragma omp end declare target

int main(int argv, char** argc) {
  int res = 0;
  int * arr = (int *)omp_target_alloc(sizeof(int) * 100, omp_get_default_device());

#pragma omp target teams distribute parallel for
  for (int i = 0; i < 100; i ++){
    arr[i] = i;
  }

#pragma omp target 
  res = runtest(arr, 98);

  printf("res = %d\n", res); 

  // TODO: make assertion 

  return 0;
}
