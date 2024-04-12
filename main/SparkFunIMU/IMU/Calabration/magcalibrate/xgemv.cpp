//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xgemv.cpp
//
// Code generation for function 'xgemv'
//

// Include files
#include "xgemv.h"
#include "magcalibrate_rtwutil.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions
namespace coder {
namespace internal {
namespace blas {
void xgemv(int m, int n, const double A[9], int ia0, const double x[9], int ix0,
           double y[3])
{
  if (n != 0) {
    int i;
    i = static_cast<unsigned char>(n);
    std::memset(&y[0], 0, static_cast<unsigned int>(i) * sizeof(double));
    i = ia0 + 3 * (n - 1);
    for (int iac{ia0}; iac <= i; iac += 3) {
      double c;
      int i1;
      c = 0.0;
      i1 = (iac + m) - 1;
      for (int ia{iac}; ia <= i1; ia++) {
        c += A[ia - 1] * x[((ix0 + ia) - iac) - 1];
      }
      i1 = div_nde_s32_floor(iac - ia0, 3);
      y[i1] += c;
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

// End of code generation (xgemv.cpp)
