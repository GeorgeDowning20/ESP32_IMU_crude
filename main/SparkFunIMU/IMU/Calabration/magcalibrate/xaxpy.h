//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xaxpy.h
//
// Code generation for function 'xaxpy'
//

#ifndef XAXPY_H
#define XAXPY_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void b_xaxpy(int n, double a, int ix0, double y[100], int iy0);

void xaxpy(int n, double a, int ix0, double y[49], int iy0);

void xaxpy(int n, double a, const array<double, 1U> &x, int ix0, double y[36],
           int iy0);

void xaxpy(int n, double a, const double x[36], int ix0, array<double, 1U> &y,
           int iy0);

void xaxpy(int n, double a, int ix0, array<double, 1U> &y, int iy0);

} // namespace blas
} // namespace internal
} // namespace coder

#endif
// End of code generation (xaxpy.h)
