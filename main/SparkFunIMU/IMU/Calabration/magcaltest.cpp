#include "magcal.h"
#include "magcalibrate/magcalibrate.h"
#include "magcalibrate/magcalibrate_terminate.h"
#include "magcalibrate/rt_nonfinite.h"
#include <stdio.h>

// Function Declarations
static void argInit_36x1_real_T(double result[36]);

static double argInit_real_T();

// Function Definitions
static void argInit_36x1_real_T(double result[36])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 36; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

static double argInit_real_T()
{
  return 0.0;
}


  double x_data[36] = {-50,-67.6335575687742,-78.5316954888546,-78.5316954888546,-67.6335575687742,-50,-50,-55.4490689600402,-58.8167787843871,-58.8167787843871,-55.4490689600402,-50,-50,-35.7341522555727,-26.9173734711856,-26.9173734711856,-35.7341522555727,-50,-50,-35.7341522555727,-26.9173734711856,-26.9173734711856,-35.7341522555727,-50,-50,-55.4490689600402,-58.8167787843871,-58.8167787843871,-55.4490689600402,-50,-50,-67.6335575687742,-78.5316954888546,-78.5316954888546,-67.6335575687742,-50};
  double y_data[36] = {20,20,20,20,20,20,20,8.81966011250105,1.90983005625053,1.90983005625053,8.81966011250105,20,20,13.0901699437495,8.81966011250105,8.81966011250105,13.0901699437495,20,20,26.9098300562505,31.1803398874990,31.1803398874990,26.9098300562505,20,20,31.1803398874990,38.0901699437495,38.0901699437495,31.1803398874990,20,20,20,20,20,20,20};
  double z_data[36] = {50,59.5491502812526,84.5491502812526,115.450849718747,140.450849718747,150,50,59.5491502812526,84.5491502812526,115.450849718747,140.450849718747,150,50,59.5491502812526,84.5491502812526,115.450849718747,140.450849718747,150,50,59.5491502812526,84.5491502812526,115.450849718747,140.450849718747,150,50,59.5491502812526,84.5491502812526,115.450849718747,140.450849718747,150,50,59.5491502812526,84.5491502812526,115.450849718747,140.450849718747,150};

  

void main_magcalibrate()
{

  double A[9];
  double b[3];
  double expmfs;
  // Initialize function 'magcalibrate' input arguments.
  // Initialize function input argument 'x'.
  // argInit_36x1_real_T(x_data);
  // argInit_36x1_real_T(y_data);
  // argInit_36x1_real_T(z_data);

  printf("x: %f %f %f\n", x_data[0], x_data[1], x_data[2]);
  // Initialize function input argument 'y'.
  // Initialize function input argument 'z'.
  // Call the entry-point 'magcalibrate'.
  magcalibrate(x_data, y_data, z_data, A, b, &expmfs);

  printf("A: %f %f %f\n", A[0], A[1], A[2]);
  printf("A: %f %f %f\n", A[3], A[4], A[5]);
  printf("A: %f %f %f\n", A[6], A[7], A[8]);
  printf("b: %f %f %f\n", b[0], b[1], b[2]);
  // printf("A: %f %f %f\n", A[3], A[4], A[5]);
}

int mainmagcal()
{
  printf("Starting\n");
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_magcalibrate();

  printf("Successfully completed\n");
  // Terminate the application.
  // You do not need to do this more than one time.
  magcalibrate_terminate();
  return 0;
}