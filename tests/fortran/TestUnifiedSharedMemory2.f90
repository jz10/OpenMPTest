!! Test array shared between host and device

PROGRAM Test_OMP_Unified_Shared_Memory
  IMPLICIT NONE
  !$OMP REQUIRES UNIFIED_SHARED_MEMORY
  INTEGER, PARAMETER :: SIZE = 100
  INTEGER :: data(SIZE)
  INTEGER :: i, Test_Function
  
  DO i = 1, SIZE, 1
     data(i) = i
  END DO
  
  PRINT *, 'Test result:  ', Test_Function(data, SIZE)
END PROGRAM Test_OMP_Unified_Shared_Memory

FUNCTION Test_Function(data, size)
  IMPLICIT NONE

  INTEGER, INTENT(IN) :: size
  INTEGER, INTENT(OUT) :: data(size)

  INTEGER :: Test_Function            ! function type 
  INTEGER :: i

  !$OMP TARGET 
  DO i = 1, SIZE, 1
     data(i) = data(i) + 1
  END DO

  Test_Function = data(99)
  !$OMP END TARGET 
     
END FUNCTION Test_Function
