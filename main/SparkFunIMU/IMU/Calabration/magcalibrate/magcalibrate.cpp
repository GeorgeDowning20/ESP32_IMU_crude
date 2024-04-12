//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// magcalibrate.cpp
//
// Code generation for function 'magcalibrate'
//

// Include files
#include "magcalibrate.h"
#include "chol.h"
#include "coder_array.h"
#include "magcal.h"
#include "magcalibrate_data.h"
#include "magcalibrate_rtwutil.h"
#include "mldivide.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "sqrtm.h"
#include "svd.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdio.h>

// Function Definitions
void magcalibrate(const double x[36], const double y[36], const double z[36],
                  double A[9], double b[3], double *expmfs)
{
  static coder::array<double, 1U> U;
  static coder::array<double, 1U> d;
  static creal_T b_y[108];
  static creal_T spherept[108];
  static creal_T radsq[36];
  static creal_T A7[9];
  static creal_T b_radsq;
  static double b_A[144];
  static double D[108];
  static double V[49];
  static double b_bv_tmp[36];
  static double bv[36];
  static double bv_tmp[36];
  static double c_bv_tmp[36];
  static double c_A[9];
  static double d_A[9];
  static double beta[7];
  static double soln[4];
  static double b_x[3];
  double A7_re_tmp;
  double b_A7_re_tmp;
  double b_d;
  double dA;
  double det3root;
  double er;
  double magB7;
  double y2n;
  int i;
  int k;
  int xj;
  int xoffset;
  boolean_T varargin_1[9];
  boolean_T exitg1;
  boolean_T ispd10;
  boolean_T p;
  U.set_size(252);
  d.set_size(252);
  for (xoffset = 0; xoffset < 36; xoffset++) {
    A7_re_tmp = x[xoffset];
    D[xoffset] = A7_re_tmp;
    b_A7_re_tmp = y[xoffset];
    D[xoffset + 36] = b_A7_re_tmp;
    b_d = z[xoffset];
    D[xoffset + 72] = b_d;
    det3root = A7_re_tmp * A7_re_tmp;
    bv_tmp[xoffset] = det3root;
    y2n = b_A7_re_tmp * b_A7_re_tmp;
    b_bv_tmp[xoffset] = y2n;
    dA = b_d * b_d;
    c_bv_tmp[xoffset] = dA;
    bv[xoffset] = (det3root + y2n) + dA;
    b_A[xoffset] = A7_re_tmp;
    b_A[xoffset + 36] = b_A7_re_tmp;
    b_A[xoffset + 72] = b_d;
    b_A[xoffset + 108] = 1.0;
  }
  coder::mldivide(b_A, bv, soln);
  std::memset(&A[0], 0, 9U * sizeof(double));
  A[0] = 1.0;
  A7_re_tmp = 0.5 * soln[0];
  b[0] = A7_re_tmp;
  b_x[0] = A7_re_tmp * A7_re_tmp;
  A[4] = 1.0;
  A7_re_tmp = 0.5 * soln[1];
  b[1] = A7_re_tmp;
  b_x[1] = A7_re_tmp * A7_re_tmp;
  A[8] = 1.0;
  A7_re_tmp = 0.5 * soln[2];
  b[2] = A7_re_tmp;
  *expmfs = std::sqrt(soln[3] + ((b_x[0] + b_x[1]) + A7_re_tmp * A7_re_tmp));
  dA = 0.0;
  A7_re_tmp = soln[0];
  b_A7_re_tmp = soln[1];
  b_d = soln[2];
  det3root = soln[3];
  for (i = 0; i < 36; i++) {
    y2n = (((b_A[i] * A7_re_tmp + b_A[i + 36] * b_A7_re_tmp) +
            b_A[i + 72] * b_d) +
           b_A[i + 108] * det3root) -
          bv[i];
    dA += y2n * y2n;
    d[i] = bv_tmp[i];
    d[i + 36] = b_bv_tmp[i];
    d[i + 72] = c_bv_tmp[i];
    d[i + 108] = D[i];
    d[i + 144] = D[i + 36];
    d[i + 180] = D[i + 72];
    d[i + 216] = 1.0;
  }
  er = 1.0 / (2.0 * *expmfs * *expmfs) * std::sqrt(dA / 36.0);
  p = true;
  for (k = 0; k < 252; k++) {
    if ((!p) || (std::isinf(d[k]) || std::isnan(d[k]))) {
      p = false;
    }
  }
  if (p) {
    coder::internal::svd(d, U, beta, V);
  } else {
    for (i = 0; i < 49; i++) {
      V[i] = rtNaN;
    }
  }
  for (i = 0; i < 7; i++) {
    beta[i] = V[i + 42];
  }
  std::memset(&c_A[0], 0, 9U * sizeof(double));
  c_A[0] = V[42];
  c_A[4] = V[43];
  c_A[8] = V[44];
  dA = V[42] * V[43] * V[44];
  if (dA < 0.0) {
    for (i = 0; i < 9; i++) {
      c_A[i] = -c_A[i];
    }
    for (i = 0; i < 7; i++) {
      beta[i] = -V[i + 42];
    }
    dA = -dA;
  }
  b_x[0] = -0.5 * (beta[3] / beta[0]);
  b_x[1] = -0.5 * (beta[4] / beta[1]);
  b_x[2] = -0.5 * (beta[5] / beta[2]);
  det3root = rt_powd_snf(dA, 0.33333333333333331);
  if ((!std::isinf(det3root)) && (!std::isnan(det3root)) && (dA != 0.0)) {
    y2n = rt_powd_snf(det3root, 3.0);
    b_d = y2n - dA;
    if (b_d != 0.0) {
      det3root -= b_d / (3.0 * (y2n / det3root));
    }
  }
  for (i = 0; i < 9; i++) {
    d_A[i] = c_A[i] / det3root;
  }
  coder::sqrtm(d_A, A7);
  magB7 = std::sqrt(
              std::abs(((c_A[0] * b_x[0] * b_x[0] + b_x[1] * c_A[4] * b_x[1]) +
                        b_x[2] * c_A[8] * b_x[2]) -
                       beta[6])) /
          std::sqrt(det3root);
  for (i = 0; i < 36; i++) {
    dA = D[i] - b_x[0];
    b_d = D[i + 36] - b_x[1];
    det3root = D[i + 72] - b_x[2];
    for (xoffset = 0; xoffset < 3; xoffset++) {
      double c_A7_re_tmp;
      double d_A7_re_tmp;
      double e_A7_re_tmp;
      y2n = A7[xoffset].re;
      A7_re_tmp = A7[xoffset].im;
      b_A7_re_tmp = A7[xoffset + 3].re;
      c_A7_re_tmp = A7[xoffset + 3].im;
      d_A7_re_tmp = A7[xoffset + 6].re;
      e_A7_re_tmp = A7[xoffset + 6].im;
      xj = i + 36 * xoffset;
      spherept[xj].re = ((y2n * dA - A7_re_tmp * 0.0) +
                         (b_A7_re_tmp * b_d - c_A7_re_tmp * 0.0)) +
                        (d_A7_re_tmp * det3root - e_A7_re_tmp * 0.0);
      spherept[xj].im = ((y2n * 0.0 + A7_re_tmp * dA) +
                         (b_A7_re_tmp * 0.0 + c_A7_re_tmp * b_d)) +
                        (d_A7_re_tmp * 0.0 + e_A7_re_tmp * det3root);
    }
  }
  for (k = 0; k < 108; k++) {
    A7_re_tmp = spherept[k].re;
    b_A7_re_tmp = spherept[k].im;
    b_y[k].re = A7_re_tmp * A7_re_tmp - b_A7_re_tmp * b_A7_re_tmp;
    A7_re_tmp *= b_A7_re_tmp;
    b_y[k].im = A7_re_tmp + A7_re_tmp;
  }
  std::copy(&b_y[0], &b_y[36], &radsq[0]);
  for (k = 0; k < 2; k++) {
    xoffset = (k + 1) * 36;
    for (xj = 0; xj < 36; xj++) {
      i = xoffset + xj;
      radsq[xj].re += b_y[i].re;
      radsq[xj].im += b_y[i].im;
    }
  }
  dA = magB7 * magB7;
  b_d = 0.0;
  det3root = 0.0;
  for (i = 0; i < 36; i++) {
    y2n = radsq[i].re - dA;
    A7_re_tmp = radsq[i].im;
    radsq[i].re = y2n;
    b_A7_re_tmp = y2n * A7_re_tmp;
    b_d += y2n * y2n - A7_re_tmp * A7_re_tmp;
    det3root += b_A7_re_tmp + b_A7_re_tmp;
  }
  if (det3root == 0.0) {
    b_radsq.re = b_d / 36.0;
    b_radsq.im = 0.0;
  } else if (b_d == 0.0) {
    b_radsq.re = 0.0;
    b_radsq.im = det3root / 36.0;
  } else {
    b_radsq.re = b_d / 36.0;
    b_radsq.im = det3root / 36.0;
  }
  coder::b_sqrt(b_radsq);
  dA = 1.0 / (2.0 * magB7 * magB7) * b_radsq.re;
  xj = coder::internal::chol(c_A, xoffset);
  for (i = 0; i < 9; i++) {
    varargin_1[i] = (A7[i].im == 0.0);
  }
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 9)) {
    if (!varargin_1[k]) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if ((xj == 0) && p && (dA < er)) {
    for (i = 0; i < 9; i++) {
      A[i] = A7[i].re;
    }
    b[0] = b_x[0];
    b[1] = b_x[1];
    b[2] = b_x[2];
    *expmfs = magB7;
    er = dA;
  }
  dA = coder::correctEllipsoid10(&D[0], &D[36], &D[72], A7, b_x, b_d, ispd10);
  for (i = 0; i < 9; i++) {
    varargin_1[i] = (A7[i].im == 0.0);
  }
  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 9)) {
    if (!varargin_1[k]) {
      p = false;
      exitg1 = true;
    } else {
      k++;
    }
  }
  if (ispd10 && p && (b_d < er)) {
    for (i = 0; i < 9; i++) {
      A[i] = A7[i].re;
    }
    b[0] = b_x[0];
    b[1] = b_x[1];
    b[2] = b_x[2];
    *expmfs = dA;
  }
  //  Calibration coefficients
}

// End of code generation (magcalibrate.cpp)
