//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// chol.cpp
//
// Code generation for function 'chol'
//

// Include files
#include "chol.h"
#include "magcalibrate_rtwutil.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Definitions
namespace coder {
namespace internal {
int chol(double A[9], int &jmax)
{
  int flag;
  int i;
  int info;
  int j;
  boolean_T exitg1;
  info = -1;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j < 3)) {
    double c;
    double ssq;
    int idxA1j;
    int idxAjj;
    int k;
    idxA1j = j * 3;
    idxAjj = idxA1j + j;
    ssq = 0.0;
    if (j >= 1) {
      for (k = 0; k < j; k++) {
        c = A[idxA1j + k];
        ssq += c * c;
      }
    }
    ssq = A[idxAjj] - ssq;
    if (ssq > 0.0) {
      ssq = std::sqrt(ssq);
      A[idxAjj] = ssq;
      if (j + 1 < 3) {
        int idxAjjp1;
        k = idxA1j + 4;
        idxAjjp1 = idxAjj + 4;
        if (j != 0) {
          i = (idxA1j + 3 * (1 - j)) + 4;
          for (int iac{k}; iac <= i; iac += 3) {
            int i1;
            c = 0.0;
            i1 = (iac + j) - 1;
            for (int ia{iac}; ia <= i1; ia++) {
              c += A[ia - 1] * A[(idxA1j + ia) - iac];
            }
            i1 = (idxAjj + div_nde_s32_floor((iac - idxA1j) - 4, 3) * 3) + 3;
            A[i1] -= c;
          }
        }
        ssq = 1.0 / ssq;
        i = (idxAjj + 3 * (1 - j)) + 4;
        for (k = idxAjjp1; k <= i; k += 3) {
          A[k - 1] *= ssq;
        }
      }
      j++;
    } else {
      A[idxAjj] = ssq;
      info = j;
      exitg1 = true;
    }
  }
  flag = info + 1;
  if (info + 1 == 0) {
    jmax = 3;
  } else {
    jmax = info;
  }
  for (j = 0; j <= jmax - 2; j++) {
    i = j + 2;
    if (i <= jmax) {
      std::memset(&A[(j * 3 + i) + -1], 0,
                  static_cast<unsigned int>((jmax - i) + 1) * sizeof(double));
    }
  }
  return flag;
}

} // namespace internal
} // namespace coder

// End of code generation (chol.cpp)
