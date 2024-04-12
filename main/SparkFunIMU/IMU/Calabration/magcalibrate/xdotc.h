//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xdotc.h
//
// Code generation for function 'xdotc'
//

#ifndef XDOTC_H
#define XDOTC_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
double b_xdotc(int n, const double x[100], int ix0, const double y[100],
               int iy0);

double xdotc(int n, const double x[49], int ix0, const double y[49], int iy0);

double xdotc(int n, const array<double, 1U> &x, int ix0,
             const array<double, 1U> &y, int iy0);

} // namespace blas
} // namespace internal
} // namespace coder

#endif
// End of code generation (xdotc.h)
