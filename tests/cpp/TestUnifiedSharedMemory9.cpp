// Test case for std data structure with team and distributed parallel for loop

#include "stdio.h"

#include <map>

using namespace std;

#pragma omp requires unified_shared_memory

#pragma omp declare target
map<int, int> IntMap;
#pragma omp end declare target

int main(int argv, char** argc) {
  // omp_set_default_device(0);

  // #pragma omp requires unified_shared_memory

#pragma omp target teams distribute parallel for
  for (int i = 0; i < 100; i ++) {
      IntMap[i] = argv + i;
    }
  
  printf("IntMap[0] = %d and IntMap[99] = %d\n", IntMap[0], IntMap[99]); 

  // TODO: make assertion for IntMap

  return 0;
}
