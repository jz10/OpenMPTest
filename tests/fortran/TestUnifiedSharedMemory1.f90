!! Test variables shared between host and device

PROGRAM Test_OMP_Unified_Shared_Memory
  IMPLICIT NONE
  REAL :: a, b, c, Test_Function
  PRINT *, 'Please enter the lengths of the 3 sides.'
  READ *, a, b, c
  PRINT *, 'Test result:  ', Test_Function(a,b,c)
END PROGRAM Test_OMP_Unified_Shared_Memory

FUNCTION Test_Function(x,y,z)
  IMPLICIT NONE
!$OMP REQUIRES UNIFIED_SHARED_MEMORY
  REAL :: Test_Function            ! function type 
  REAL, INTENT( IN ) :: x, y, z
  REAL :: theta, height
  theta = ACOS((x**2+y**2-z**2)/(2.0*x*y))

  !$OMP TARGET 
  height = x*SIN(theta);
  Test_Function = 0.5*y*height
  !$OMP END TARGET 
     
END FUNCTION Test_Function
