! Test the shared used defined type arrray with target related constructs and directives
  
PROGRAM Test_OMP_Unified_Shared_Memory
  IMPLICIT NONE
  !$OMP REQUIRES UNIFIED_SHARED_MEMORY               
  INTEGER, PARAMETER :: SIZE = 100
  REAL :: B(SIZE), C(SIZE)
  INTEGER :: i
  REAL :: Test_Function, x 

  TYPE TestStruct
     INTEGER :: i
     REAL    :: f
  END TYPE TestStruct
  
  TYPE(TestStruct) :: D(SIZE)

  DO i = 1, SIZE, 1
     B(i) = i
     D(i)%i = i
     D(i)%f = i * 0.1
  END DO

  x = Test_Function(B, D, SIZE, 10, 10, 10)
  PRINT *, 'Test result:  ', x
END PROGRAM Test_OMP_Unified_Shared_Memory

function Test_Function(B, D, N, block_size, num_teams, block_threads) result(sum)
  implicit none
  real    :: B(N), sum
  integer :: N, block_size, num_teams, block_threads, i, i0

  TYPE TestStruct
     INTEGER :: i
     REAL    :: f
  END TYPE TestStruct

  type(TestStruct) :: D(N)

  sum = 0.0e0
  !$omp target 
  !$omp teams num_teams(num_teams) thread_limit(block_threads) &
  !$omp&  reduction(+:sum)
  !$omp distribute
  do i0=1,N, block_size
     !$omp parallel do reduction(+:sum)
     do i = i0, min(i0+block_size,N)
        sum = sum + B(i) * D(i)%f
     end do
  end do
  !$omp end teams
  !$omp end target
  
end function Test_Function
