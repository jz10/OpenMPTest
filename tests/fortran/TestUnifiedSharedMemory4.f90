! Test the shared arrray with target related constructs and directives

PROGRAM Test_OMP_Unified_Shared_Memory
  IMPLICIT NONE
  !$OMP REQUIRES UNIFIED_SHARED_MEMORY                                                                  
  INTEGER, PARAMETER :: SIZE = 100
  REAL :: B(SIZE), C(SIZE)
  INTEGER :: i
  REAL :: Test_Function

  DO i = 1, SIZE, 1
     B(i) = i
     C(i) = i
  END DO

  Test_Function(B, C, SIZE, 10, 10, 10)
  PRINT *, 'Test result:  ', C(9)
END PROGRAM Test_OMP_Unified_Shared_Memory

function Test_Function(B,C,N, block_size, num_teams, block_threads) result(sum)
  implicit none
  real    :: B(N), C(N), sum
  integer :: N, block_size, num_teams, block_threads, i, i0
  
  sum = 0.0e0
  !$omp target 
  !$omp teams num_teams(num_teams) thread_limit(block_threads) &
  !$omp&  reduction(+:sum)
  !$omp distribute
  do i0=1,N, block_size
     !$omp parallel do reduction(+:sum)
     do i = i0, min(i0+block_size,N)
        sum = sum + B(i) * C(i)
     end do

     C(i0) = sum
  end do
  !$omp end teams
  !$omp end target
  
end function Test_Function
