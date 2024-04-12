//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// magcal.cpp
//
// Code generation for function 'magcal'
//

// Include files
#include "magcal.h"
#include "chol.h"
#include "magcalibrate_data.h"
#include "magcalibrate_rtwutil.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "sqrtm.h"
#include "svd.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>

// Function Definitions
namespace coder {
double correctEllipsoid10(const double x[36], const double y[36],
                          const double z[36], creal_T Winv[9], double V[3],
                          double &er, boolean_T &ispd)
{
  static array<double, 1U> U;
  static array<double, 1U> d;
  static creal_T c_y[108];
  static creal_T spherept[108];
  static creal_T radsq[36];
  static creal_T b_radsq;
  static double b_V[100];
  static double beta[10];
  static double A[9];
  static double b_x[9];
  static double c_x[7];
  static const signed char iv[9]{0, 1, 2, 1, 3, 4, 2, 4, 5};
  double B;
  double Winv_re_tmp;
  double b_y;
  double dA;
  double s;
  double smax;
  double y2n;
  int b_i;
  int i;
  int jA;
  int jp1j;
  int r3;
  int rtemp;
  signed char ipiv[3];
  boolean_T isodd;
  U.set_size(360);
  d.set_size(360);
  for (i = 0; i < 36; i++) {
    y2n = x[i];
    dA = 2.0 * y2n;
    d[i] = y2n * y2n;
    smax = y[i];
    d[i + 36] = dA * smax;
    s = z[i];
    d[i + 72] = dA * s;
    d[i + 108] = smax * smax;
    d[i + 144] = 2.0 * smax * s;
    d[i + 180] = s * s;
    d[i + 216] = y2n;
    d[i + 252] = smax;
    d[i + 288] = s;
    d[i + 324] = 1.0;
  }
  isodd = true;
  for (rtemp = 0; rtemp < 360; rtemp++) {
    if ((!isodd) || (std::isinf(d[rtemp]) || std::isnan(d[rtemp]))) {
      isodd = false;
    }
  }
  if (isodd) {
    internal::b_svd(d, U, beta, b_V);
  } else {
    for (b_i = 0; b_i < 100; b_i++) {
      b_V[b_i] = rtNaN;
    }
  }
  std::copy(&b_V[90], &b_V[100], &beta[0]);
  for (b_i = 0; b_i < 3; b_i++) {
    A[3 * b_i] = b_V[iv[3 * b_i] + 90];
    i = 3 * b_i + 1;
    A[i] = b_V[iv[i] + 90];
    i = 3 * b_i + 2;
    A[i] = b_V[iv[i] + 90];
  }
  std::copy(&A[0], &A[9], &b_x[0]);
  ipiv[0] = 1;
  ipiv[1] = 2;
  for (int j{0}; j < 2; j++) {
    int b_tmp;
    int mmj_tmp;
    mmj_tmp = 1 - j;
    b_tmp = j << 2;
    jp1j = b_tmp + 2;
    r3 = 3 - j;
    jA = 0;
    smax = std::abs(b_x[b_tmp]);
    for (rtemp = 2; rtemp <= r3; rtemp++) {
      s = std::abs(b_x[(b_tmp + rtemp) - 1]);
      if (s > smax) {
        jA = rtemp - 1;
        smax = s;
      }
    }
    if (b_x[b_tmp + jA] != 0.0) {
      if (jA != 0) {
        i = j + jA;
        ipiv[j] = static_cast<signed char>(i + 1);
        smax = b_x[j];
        b_x[j] = b_x[i];
        b_x[i] = smax;
        smax = b_x[j + 3];
        b_x[j + 3] = b_x[i + 3];
        b_x[i + 3] = smax;
        smax = b_x[j + 6];
        b_x[j + 6] = b_x[i + 6];
        b_x[i + 6] = smax;
      }
      b_i = (b_tmp - j) + 3;
      for (i = jp1j; i <= b_i; i++) {
        b_x[i - 1] /= b_x[b_tmp];
      }
    }
    jA = b_tmp;
    for (r3 = 0; r3 <= mmj_tmp; r3++) {
      smax = b_x[(b_tmp + r3 * 3) + 3];
      if (smax != 0.0) {
        b_i = jA + 5;
        jp1j = (jA - j) + 6;
        for (rtemp = b_i; rtemp <= jp1j; rtemp++) {
          b_x[rtemp - 1] += b_x[((b_tmp + rtemp) - jA) - 4] * -smax;
        }
      }
      jA += 3;
    }
  }
  isodd = (ipiv[0] > 1);
  dA = b_x[0] * b_x[4] * b_x[8];
  if (ipiv[1] > 2) {
    isodd = !isodd;
  }
  if (isodd) {
    dA = -dA;
  }
  if (dA < 0.0) {
    for (b_i = 0; b_i < 9; b_i++) {
      A[b_i] = -A[b_i];
    }
    for (b_i = 0; b_i < 10; b_i++) {
      beta[b_i] = -b_V[b_i + 90];
    }
    dA = -dA;
  }
  std::copy(&A[0], &A[9], &b_x[0]);
  i = 0;
  jA = 1;
  r3 = 2;
  smax = std::abs(A[0]);
  s = std::abs(A[1]);
  if (s > smax) {
    smax = s;
    i = 1;
    jA = 0;
  }
  if (std::abs(A[2]) > smax) {
    i = 2;
    jA = 1;
    r3 = 0;
  }
  b_x[jA] = A[jA] / A[i];
  b_x[r3] /= b_x[i];
  b_x[jA + 3] -= b_x[jA] * b_x[i + 3];
  b_x[r3 + 3] -= b_x[r3] * b_x[i + 3];
  b_x[jA + 6] -= b_x[jA] * b_x[i + 6];
  b_x[r3 + 6] -= b_x[r3] * b_x[i + 6];
  if (std::abs(b_x[r3 + 3]) > std::abs(b_x[jA + 3])) {
    rtemp = jA;
    jA = r3;
    r3 = rtemp;
  }
  b_x[r3 + 3] /= b_x[jA + 3];
  b_x[r3 + 6] -= b_x[r3 + 3] * b_x[jA + 6];
  smax = beta[i + 6];
  V[1] = beta[jA + 6] - smax * b_x[jA];
  V[2] = (beta[r3 + 6] - smax * b_x[r3]) - V[1] * b_x[r3 + 3];
  V[2] /= b_x[r3 + 6];
  V[0] = smax - V[2] * b_x[i + 6];
  V[1] -= V[2] * b_x[jA + 6];
  V[1] /= b_x[jA + 3];
  V[0] -= V[1] * b_x[i + 3];
  V[0] /= b_x[i];
  V[0] *= -0.5;
  V[1] *= -0.5;
  V[2] *= -0.5;
  c_x[0] = A[0] * V[0] * V[0];
  c_x[1] = 2.0 * A[1] * V[1] * V[0];
  c_x[2] = 2.0 * A[2] * V[2] * V[0];
  c_x[3] = V[1] * A[4] * V[1];
  c_x[4] = 2.0 * A[5] * V[1] * V[2];
  c_x[5] = V[2] * A[8] * V[2];
  c_x[6] = -beta[9];
  b_y = c_x[0];
  for (rtemp = 0; rtemp < 6; rtemp++) {
    b_y += c_x[rtemp + 1];
  }
  s = rt_powd_snf(dA, 0.33333333333333331);
  if ((!std::isinf(s)) && (!std::isnan(s)) && (dA != 0.0)) {
    y2n = rt_powd_snf(s, 3.0);
    smax = y2n - dA;
    if (smax != 0.0) {
      s -= smax / (3.0 * (y2n / s));
    }
  }
  for (b_i = 0; b_i < 9; b_i++) {
    b_x[b_i] = A[b_i] / s;
  }
  sqrtm(b_x, Winv);
  B = std::sqrt(std::abs(b_y)) / std::sqrt(s);
  for (b_i = 0; b_i < 36; b_i++) {
    smax = x[b_i] - V[0];
    s = y[b_i] - V[1];
    y2n = z[b_i] - V[2];
    for (jp1j = 0; jp1j < 3; jp1j++) {
      double b_Winv_re_tmp;
      double c_Winv_re_tmp;
      double d_Winv_re_tmp;
      dA = Winv[jp1j].re;
      Winv_re_tmp = Winv[jp1j].im;
      b_y = Winv[jp1j + 3].re;
      b_Winv_re_tmp = Winv[jp1j + 3].im;
      c_Winv_re_tmp = Winv[jp1j + 6].re;
      d_Winv_re_tmp = Winv[jp1j + 6].im;
      i = b_i + 36 * jp1j;
      spherept[i].re =
          ((dA * smax - Winv_re_tmp * 0.0) + (b_y * s - b_Winv_re_tmp * 0.0)) +
          (c_Winv_re_tmp * y2n - d_Winv_re_tmp * 0.0);
      spherept[i].im =
          ((dA * 0.0 + Winv_re_tmp * smax) + (b_y * 0.0 + b_Winv_re_tmp * s)) +
          (c_Winv_re_tmp * 0.0 + d_Winv_re_tmp * y2n);
    }
  }
  for (rtemp = 0; rtemp < 108; rtemp++) {
    y2n = spherept[rtemp].re;
    dA = spherept[rtemp].im;
    c_y[rtemp].re = y2n * y2n - dA * dA;
    y2n *= dA;
    c_y[rtemp].im = y2n + y2n;
  }
  std::copy(&c_y[0], &c_y[36], &radsq[0]);
  for (rtemp = 0; rtemp < 2; rtemp++) {
    i = (rtemp + 1) * 36;
    for (jA = 0; jA < 36; jA++) {
      b_i = i + jA;
      radsq[jA].re += c_y[b_i].re;
      radsq[jA].im += c_y[b_i].im;
    }
  }
  b_y = B * B;
  smax = 0.0;
  s = 0.0;
  for (b_i = 0; b_i < 36; b_i++) {
    y2n = radsq[b_i].re - b_y;
    dA = radsq[b_i].im;
    radsq[b_i].re = y2n;
    Winv_re_tmp = y2n * dA;
    smax += y2n * y2n - dA * dA;
    s += Winv_re_tmp + Winv_re_tmp;
  }
  if (s == 0.0) {
    b_radsq.re = smax / 36.0;
    b_radsq.im = 0.0;
  } else if (smax == 0.0) {
    b_radsq.re = 0.0;
    b_radsq.im = s / 36.0;
  } else {
    b_radsq.re = smax / 36.0;
    b_radsq.im = s / 36.0;
  }
  b_sqrt(b_radsq);
  er = 1.0 / (2.0 * B * B) * b_radsq.re;
  i = internal::chol(A, r3);
  ispd = (i == 0);
  return B;
}

} // namespace coder

// End of code generation (magcal.cpp)
