//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xaxpy.cpp
//
// Code generation for function 'xaxpy'
//

// Include files
#include "xaxpy.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
namespace coder {
namespace internal {
namespace blas {
void b_xaxpy(int n, double a, int ix0, double y[100], int iy0)
{
  if (!(a == 0.0)) {
    int i;
    i = n - 1;
    for (int k{0}; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] += a * y[(ix0 + k) - 1];
    }
  }
}

void xaxpy(int n, double a, int ix0, double y[49], int iy0)
{
  if (!(a == 0.0)) {
    int i;
    i = n - 1;
    for (int k{0}; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] += a * y[(ix0 + k) - 1];
    }
  }
}

void xaxpy(int n, double a, const array<double, 1U> &x, int ix0, double y[36],
           int iy0)
{
  if (!(a == 0.0)) {
    int i;
    i = n - 1;
    for (int k{0}; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] += a * x[(ix0 + k) - 1];
    }
  }
}

void xaxpy(int n, double a, const double x[36], int ix0, array<double, 1U> &y,
           int iy0)
{
  if (!(a == 0.0)) {
    int i;
    i = n - 1;
    for (int k{0}; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] = y[i1] + a * x[(ix0 + k) - 1];
    }
  }
}

void xaxpy(int n, double a, int ix0, array<double, 1U> &y, int iy0)
{
  if (!(a == 0.0)) {
    int i;
    i = n - 1;
    for (int k{0}; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] = y[i1] + a * y[(ix0 + k) - 1];
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

// End of code generation (xaxpy.cpp)
