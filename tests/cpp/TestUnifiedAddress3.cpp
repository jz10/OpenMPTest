// Test case for std data structure

#include "stdio.h"

#include "omp.h"

using namespace std;

#pragma omp requires unified_address

typedef struct CustomizedDataStructure {
  int x;
  int y;
} CustomizedDataStruct;

int main(int argv, char** argc) {
  CustomizedDataStruct * ptr = (CustomizedDataStruct *)omp_target_alloc(sizeof(CustomizedDataStruct) * 100, omp_get_default_device());

  #pragma omp target teams distribute parallel for
  for (int i = 0; i < 100; i ++){
    CustomizedDataStruct* cds = ptr ++; // Use same stride value as loop iterator
    cds->x = i;
    cds->y = 100 - i;
  }

  printf("res = %d\n", ptr[90].x);

  return 0;
}
