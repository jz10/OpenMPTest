// Test case for co-operating with teams and distributed parallel for loop

#include "sdtio.h"

int main(int argv) {
  int N = 100;
  omp_set_default_device(0);

#pragma omp requires(unified_shared_memory)
  double * data = new double[N]; 

#pragma omp target teams distribute parallel for 
  for (int i = 0; i < N; i ++)
    data[i] = i * 0.11;

  printf("data[%d] = %g\n", 99, data[99]);
 
  delete[] data;
  
  return 0; 
}
