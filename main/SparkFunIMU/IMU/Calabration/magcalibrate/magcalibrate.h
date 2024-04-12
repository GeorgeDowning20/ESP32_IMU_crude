//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// magcalibrate.h
//
// Code generation for function 'magcalibrate'
//

#ifndef MAGCALIBRATE_H
#define MAGCALIBRATE_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void magcalibrate(const double x[36], const double y[36],
                         const double z[36], double A[9], double b[3],
                         double *expmfs);

#endif
// End of code generation (magcalibrate.h)
