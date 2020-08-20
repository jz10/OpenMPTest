// Test case for std data structure

#include "sdtio.h"

#include <vector>

using namespace std;

#pragma omp declare target
vector<int> IntVec;
#pragma omp end declare target

int main(int argv) {
#pragma omp requires(unified_shared_memory)
  IntVec.push_back(argv);

#pragma omp target 
#ifdef TEST_MAP
  map(always tofrom: IntVec) 
#endif
  {
    IntVec[0] += 1;
    IntVec[99] = 99;
  }

  printf(“IntVec[0] = %d and IntVec[99] = %d\n”, IntVec[0], IntVec[99]); 

  // TODO: make assertion for IntVec

  return 0;
}
