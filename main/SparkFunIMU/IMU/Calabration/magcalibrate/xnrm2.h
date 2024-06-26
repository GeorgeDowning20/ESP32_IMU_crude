//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xnrm2.h
//
// Code generation for function 'xnrm2'
//

#ifndef XNRM2_H
#define XNRM2_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
double b_xnrm2(int n, const double x[7], int ix0);

double b_xnrm2(int n, const array<double, 1U> &x, int ix0);

double c_xnrm2(int n, const double x[10], int ix0);

double xnrm2(int n, const double x[144], int ix0);

double xnrm2(int n, const array<double, 1U> &x, int ix0);

double xnrm2(int n, const double x[3]);

} // namespace blas
} // namespace internal
} // namespace coder

#endif
// End of code generation (xnrm2.h)
