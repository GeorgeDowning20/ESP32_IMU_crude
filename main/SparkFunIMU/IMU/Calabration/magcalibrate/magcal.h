//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// magcal.h
//
// Code generation for function 'magcal'
//

#ifndef MAGCAL_H
#define MAGCAL_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
double correctEllipsoid10(const double x[36], const double y[36],
                          const double z[36], creal_T Winv[9], double V[3],
                          double &er, boolean_T &ispd);

}

#endif
// End of code generation (magcal.h)
