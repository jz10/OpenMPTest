// Test case for std data structure

#include "stdio.h"

#include "omp.h"

using namespace std;

#pragma omp requires unified_address

int main(int argv, char** argc) {
  omp_set_default_device(0);
  int N = 100;

  double *data = new double[2];
  double *data2 = new double[N];

#pragma omp target teams distribute parallel for map(from:data2[0:N])
  for (int i = 0; i < N; ++i)
    data2[i] = data[i%2] + i*0.1;

  printf("check res = %d\n", data2[90]);

  delete [] data;
  delete [] data2;

  return 0;
}
