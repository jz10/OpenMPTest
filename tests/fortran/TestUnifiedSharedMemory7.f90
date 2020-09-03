! Test the shared 2-dim arrray with target related constructs and directives

PROGRAM Test_OMP_Unified_Shared_Memory
  IMPLICIT NONE

  !$OMP REQUIRES UNIFIED_SHARED_MEMORY 
  INTEGER, PARAMETER :: SIZE = 100
  real :: B(SIZE)
  INTEGER :: i
  real :: Test_Function, x

  DO i = 1, SIZE, 1
     B(i) = i
  END DO

  x = Test_Function(B, SIZE, 10, 10, 10)
  PRINT *, 'Test result:  ', x
END PROGRAM Test_OMP_Unified_Shared_Memory

function Test_Function(B, N, block_size, num_teams, block_threads) !result(sum)
  implicit none
  real    :: Test_Function
  real    :: sum
  real, target :: C(N, N)
  real, pointer :: pval(:, :)
  real    :: B(N)
  integer :: N, block_size, num_teams, block_threads, i, i0
  real, pointer, dimension (:) :: pra

  do i = 1, N, 1
     do i0 = 1, N, 1
        C(i, i0) = i * 0.1
     end do
  end do

  pval => C(1:block_size, 1:block_size)
  sum = 0.0e0
  !$omp target 
  !$omp teams num_teams(num_teams) thread_limit(block_threads) &
  !$omp&  reduction(+:sum)
  !$omp distribute
  do i0=1,N, block_size
     !$omp parallel do reduction(+:sum)
     do i = i0, min(i0+block_size,N)
        C(i, i0) = B(i) * sum
        sum = sum + C(i, i0)
     end do
  end do
  !$omp end teams
  !$omp end target
  
  do i = 1, block_size, 1
     do i0 = 1,block_size, 1
        sum = pval(i, i0)
     end do
  end do

  Test_Function = sum
end function Test_Function
