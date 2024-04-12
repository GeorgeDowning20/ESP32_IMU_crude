//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xdotc.cpp
//
// Code generation for function 'xdotc'
//

// Include files
#include "xdotc.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
namespace coder {
namespace internal {
namespace blas {
double b_xdotc(int n, const double x[100], int ix0, const double y[100],
               int iy0)
{
  double d;
  int i;
  d = 0.0;
  i = static_cast<unsigned char>(n);
  for (int k{0}; k < i; k++) {
    d += x[(ix0 + k) - 1] * y[(iy0 + k) - 1];
  }
  return d;
}

double xdotc(int n, const double x[49], int ix0, const double y[49], int iy0)
{
  double d;
  int i;
  d = 0.0;
  i = static_cast<unsigned char>(n);
  for (int k{0}; k < i; k++) {
    d += x[(ix0 + k) - 1] * y[(iy0 + k) - 1];
  }
  return d;
}

double xdotc(int n, const array<double, 1U> &x, int ix0,
             const array<double, 1U> &y, int iy0)
{
  double d;
  int i;
  d = 0.0;
  i = static_cast<unsigned char>(n);
  for (int k{0}; k < i; k++) {
    d += x[(ix0 + k) - 1] * y[(iy0 + k) - 1];
  }
  return d;
}

} // namespace blas
} // namespace internal
} // namespace coder

// End of code generation (xdotc.cpp)
