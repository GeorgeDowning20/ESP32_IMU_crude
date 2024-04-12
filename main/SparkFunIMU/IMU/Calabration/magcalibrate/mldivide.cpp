//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// mldivide.cpp
//
// Code generation for function 'mldivide'
//

// Include files
#include "mldivide.h"
#include "magcalibrate_rtwutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
namespace coder {
void mldivide(const double A[144], const double B[36], double Y[4])
{
  static double b_A[144];
  static double b_B[36];
  double tau[4];
  double vn1[4];
  double vn2[4];
  double work[4];
  double absxk;
  double scale;
  double smax;
  double t;
  int b_i;
  int ix0;
  int iy;
  int kend;
  int lastc;
  int rankA;
  signed char jpvt[4];
  std::copy(&A[0], &A[144], &b_A[0]);
  for (lastc = 0; lastc < 4; lastc++) {
    jpvt[lastc] = static_cast<signed char>(lastc + 1);
    tau[lastc] = 0.0;
    work[lastc] = 0.0;
    ix0 = lastc * 36;
    smax = 0.0;
    scale = 3.3121686421112381E-170;
    kend = ix0 + 36;
    for (iy = ix0 + 1; iy <= kend; iy++) {
      absxk = std::abs(A[iy - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        smax = smax * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        smax += t * t;
      }
    }
    absxk = scale * std::sqrt(smax);
    vn1[lastc] = absxk;
    vn2[lastc] = absxk;
  }
  for (int i{0}; i < 4; i++) {
    int ii;
    int ip1;
    int pvt;
    ip1 = i + 2;
    ii = i * 36 + i;
    kend = 4 - i;
    iy = 0;
    if (4 - i > 1) {
      smax = std::abs(vn1[i]);
      for (lastc = 2; lastc <= kend; lastc++) {
        scale = std::abs(vn1[(i + lastc) - 1]);
        if (scale > smax) {
          iy = lastc - 1;
          smax = scale;
        }
      }
    }
    pvt = i + iy;
    if (pvt != i) {
      kend = pvt * 36;
      iy = i * 36;
      for (lastc = 0; lastc < 36; lastc++) {
        rankA = kend + lastc;
        smax = b_A[rankA];
        ix0 = iy + lastc;
        b_A[rankA] = b_A[ix0];
        b_A[ix0] = smax;
      }
      kend = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = static_cast<signed char>(kend);
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }
    t = b_A[ii];
    ix0 = ii + 2;
    tau[i] = 0.0;
    smax = internal::blas::xnrm2(35 - i, b_A, ii + 2);
    if (smax != 0.0) {
      absxk = b_A[ii];
      scale = rt_hypotd_snf(absxk, smax);
      if (absxk >= 0.0) {
        scale = -scale;
      }
      if (std::abs(scale) < 1.0020841800044864E-292) {
        kend = 0;
        b_i = (ii - i) + 36;
        do {
          kend++;
          for (lastc = ix0; lastc <= b_i; lastc++) {
            b_A[lastc - 1] *= 9.9792015476736E+291;
          }
          scale *= 9.9792015476736E+291;
          t *= 9.9792015476736E+291;
        } while ((std::abs(scale) < 1.0020841800044864E-292) && (kend < 20));
        scale = rt_hypotd_snf(t, internal::blas::xnrm2(35 - i, b_A, ii + 2));
        if (t >= 0.0) {
          scale = -scale;
        }
        tau[i] = (scale - t) / scale;
        smax = 1.0 / (t - scale);
        for (lastc = ix0; lastc <= b_i; lastc++) {
          b_A[lastc - 1] *= smax;
        }
        for (lastc = 0; lastc < kend; lastc++) {
          scale *= 1.0020841800044864E-292;
        }
        t = scale;
      } else {
        tau[i] = (scale - absxk) / scale;
        smax = 1.0 / (absxk - scale);
        b_i = (ii - i) + 36;
        for (lastc = ix0; lastc <= b_i; lastc++) {
          b_A[lastc - 1] *= smax;
        }
        t = scale;
      }
    }
    b_A[ii] = t;
    if (i + 1 < 4) {
      int lastv;
      b_A[ii] = 1.0;
      iy = ii + 37;
      if (tau[i] != 0.0) {
        boolean_T exitg2;
        lastv = 36 - i;
        kend = (ii - i) + 35;
        while ((lastv > 0) && (b_A[kend] == 0.0)) {
          lastv--;
          kend--;
        }
        lastc = 2 - i;
        exitg2 = false;
        while ((!exitg2) && (lastc + 1 > 0)) {
          int exitg1;
          kend = (ii + lastc * 36) + 36;
          rankA = kend;
          do {
            exitg1 = 0;
            if (rankA + 1 <= kend + lastv) {
              if (b_A[rankA] != 0.0) {
                exitg1 = 1;
              } else {
                rankA++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = -1;
      }
      if (lastv > 0) {
        if (lastc + 1 != 0) {
          std::memset(&work[0], 0,
                      static_cast<unsigned int>(lastc + 1) * sizeof(double));
          b_i = (ii + 36 * lastc) + 37;
          for (ix0 = iy; ix0 <= b_i; ix0 += 36) {
            smax = 0.0;
            pvt = (ix0 + lastv) - 1;
            for (rankA = ix0; rankA <= pvt; rankA++) {
              smax += b_A[rankA - 1] * b_A[(ii + rankA) - ix0];
            }
            kend = div_nde_s32_floor((ix0 - ii) - 37, 36);
            work[kend] += smax;
          }
        }
        if (!(-tau[i] == 0.0)) {
          kend = ii;
          for (int j{0}; j <= lastc; j++) {
            absxk = work[j];
            if (absxk != 0.0) {
              smax = absxk * -tau[i];
              b_i = kend + 37;
              pvt = lastv + kend;
              for (rankA = b_i; rankA <= pvt + 36; rankA++) {
                b_A[rankA - 1] += b_A[((ii + rankA) - kend) - 37] * smax;
              }
            }
            kend += 36;
          }
        }
      }
      b_A[ii] = t;
    }
    for (int j{ip1}; j < 5; j++) {
      kend = i + (j - 1) * 36;
      absxk = vn1[j - 1];
      if (absxk != 0.0) {
        smax = std::abs(b_A[kend]) / absxk;
        smax = 1.0 - smax * smax;
        if (smax < 0.0) {
          smax = 0.0;
        }
        scale = absxk / vn2[j - 1];
        scale = smax * (scale * scale);
        if (scale <= 1.4901161193847656E-8) {
          absxk = internal::blas::xnrm2(35 - i, b_A, kend + 2);
          vn1[j - 1] = absxk;
          vn2[j - 1] = absxk;
        } else {
          vn1[j - 1] = absxk * std::sqrt(smax);
        }
      }
    }
  }
  rankA = 0;
  smax = 7.9936057773011271E-14 * std::abs(b_A[0]);
  while ((rankA < 4) && (!(std::abs(b_A[rankA + 36 * rankA]) <= smax))) {
    rankA++;
  }
  std::copy(&B[0], &B[36], &b_B[0]);
  for (int j{0}; j < 4; j++) {
    Y[j] = 0.0;
    if (tau[j] != 0.0) {
      smax = b_B[j];
      b_i = j + 2;
      for (int i{b_i}; i < 37; i++) {
        smax += b_A[(i + 36 * j) - 1] * b_B[i - 1];
      }
      smax *= tau[j];
      if (smax != 0.0) {
        b_B[j] -= smax;
        for (int i{b_i}; i < 37; i++) {
          b_B[i - 1] -= b_A[(i + 36 * j) - 1] * smax;
        }
      }
    }
  }
  for (int i{0}; i < rankA; i++) {
    Y[jpvt[i] - 1] = b_B[i];
  }
  for (int j{rankA}; j >= 1; j--) {
    kend = jpvt[j - 1] - 1;
    iy = 36 * (j - 1);
    Y[kend] /= b_A[(j + iy) - 1];
    for (int i{0}; i <= j - 2; i++) {
      ix0 = jpvt[i] - 1;
      Y[ix0] -= Y[kend] * b_A[i + iy];
    }
  }
}

} // namespace coder

// End of code generation (mldivide.cpp)
