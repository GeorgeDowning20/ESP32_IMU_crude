//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// svd.cpp
//
// Code generation for function 'svd'
//

// Include files
#include "svd.h"
#include "rt_nonfinite.h"
#include "xaxpy.h"
#include "xdotc.h"
#include "xnrm2.h"
#include "xrot.h"
#include "xrotg.h"
#include "xswap.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
namespace coder {
namespace internal {
void b_svd(const array<double, 1U> &A, array<double, 1U> &U, double s[10],
           double V[100])
{
  static double Vf[100];
  static double work[36];
  static double b_s[10];
  static double e[10];
  array<double, 1U> b_A;
  double nrm;
  double rt;
  double snorm;
  double sqds;
  int i;
  int jj;
  int m;
  int qjj;
  int qp1;
  int qp1q;
  int qq;
  b_A.set_size(360);
  U.set_size(360);
  for (i = 0; i < 360; i++) {
    b_A[i] = A[i];
  }
  std::memset(&b_s[0], 0, 10U * sizeof(double));
  std::memset(&e[0], 0, 10U * sizeof(double));
  std::memset(&work[0], 0, 36U * sizeof(double));
  for (i = 0; i < 360; i++) {
    U[i] = 0.0;
  }
  std::memset(&Vf[0], 0, 100U * sizeof(double));
  for (int q{0}; q < 10; q++) {
    boolean_T apply_transform;
    qp1 = q + 2;
    qq = q + 36 * q;
    qp1q = qq + 1;
    apply_transform = false;
    nrm = blas::b_xnrm2(36 - q, b_A, qq + 1);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq] < 0.0) {
        nrm = -nrm;
      }
      b_s[q] = nrm;
      if (std::abs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        i = (qq - q) + 36;
        for (int k{qp1q}; k <= i; k++) {
          b_A[k - 1] = nrm * b_A[k - 1];
        }
      } else {
        i = (qq - q) + 36;
        for (int k{qp1q}; k <= i; k++) {
          b_A[k - 1] = b_A[k - 1] / b_s[q];
        }
      }
      b_A[qq] = b_A[qq] + 1.0;
      b_s[q] = -b_s[q];
    } else {
      b_s[q] = 0.0;
    }
    for (jj = qp1; jj < 11; jj++) {
      qjj = q + 36 * (jj - 1);
      if (apply_transform) {
        qp1q = 36 - q;
        nrm = 0.0;
        for (int k{0}; k < qp1q; k++) {
          nrm += b_A[qq + k] * b_A[qjj + k];
        }
        nrm = -(nrm / b_A[qq]);
        if (!(nrm == 0.0)) {
          i = 35 - q;
          for (int k{0}; k <= i; k++) {
            qp1q = qjj + k;
            b_A[qp1q] = b_A[qp1q] + nrm * b_A[qq + k];
          }
        }
      }
      e[jj - 1] = b_A[qjj];
    }
    for (jj = q + 1; jj < 37; jj++) {
      qp1q = (jj + 36 * q) - 1;
      U[qp1q] = b_A[qp1q];
    }
    if (q + 1 <= 8) {
      nrm = blas::c_xnrm2(9 - q, e, q + 2);
      if (nrm == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -nrm;
        } else {
          e[q] = nrm;
        }
        nrm = e[q];
        if (std::abs(e[q]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[q];
          for (int k{qp1}; k < 11; k++) {
            e[k - 1] *= nrm;
          }
        } else {
          for (int k{qp1}; k < 11; k++) {
            e[k - 1] /= nrm;
          }
        }
        e[q + 1]++;
        e[q] = -e[q];
        for (jj = qp1; jj < 37; jj++) {
          work[jj - 1] = 0.0;
        }
        for (jj = qp1; jj < 11; jj++) {
          blas::xaxpy(35 - q, e[jj - 1], b_A, (q + 36 * (jj - 1)) + 2, work,
                      q + 2);
        }
        for (jj = qp1; jj < 11; jj++) {
          blas::xaxpy(35 - q, -e[jj - 1] / e[q + 1], work, q + 2, b_A,
                      (q + 36 * (jj - 1)) + 2);
        }
      }
      for (jj = qp1; jj < 11; jj++) {
        Vf[(jj + 10 * q) - 1] = e[jj - 1];
      }
    }
  }
  m = 8;
  e[8] = b_A[332];
  e[9] = 0.0;
  for (int q{9}; q >= 0; q--) {
    qp1 = q + 2;
    qq = q + 36 * q;
    if (b_s[q] != 0.0) {
      for (jj = qp1; jj < 11; jj++) {
        qjj = (q + 36 * (jj - 1)) + 1;
        blas::xaxpy(36 - q, -(blas::xdotc(36 - q, U, qq + 1, U, qjj) / U[qq]),
                    qq + 1, U, qjj);
      }
      for (jj = q + 1; jj < 37; jj++) {
        qp1q = (jj + 36 * q) - 1;
        U[qp1q] = -U[qp1q];
      }
      U[qq] = U[qq] + 1.0;
      for (jj = 0; jj < q; jj++) {
        U[jj + 36 * q] = 0.0;
      }
    } else {
      for (jj = 0; jj < 36; jj++) {
        U[jj + 36 * q] = 0.0;
      }
      U[qq] = 1.0;
    }
  }
  for (int q{9}; q >= 0; q--) {
    if ((q + 1 <= 8) && (e[q] != 0.0)) {
      qp1 = q + 2;
      qp1q = (q + 10 * q) + 2;
      for (jj = qp1; jj < 11; jj++) {
        qq = (q + 10 * (jj - 1)) + 2;
        blas::b_xaxpy(9 - q,
                      -(blas::b_xdotc(9 - q, Vf, qp1q, Vf, qq) / Vf[qp1q - 1]),
                      qp1q, Vf, qq);
      }
    }
    std::memset(&Vf[q * 10], 0, 10U * sizeof(double));
    Vf[q + 10 * q] = 1.0;
  }
  qp1 = 0;
  snorm = 0.0;
  for (int q{0}; q < 10; q++) {
    nrm = b_s[q];
    if (nrm != 0.0) {
      rt = std::abs(nrm);
      nrm /= rt;
      b_s[q] = rt;
      if (q + 1 < 10) {
        e[q] /= nrm;
      }
      qp1q = 36 * q;
      i = qp1q + 36;
      for (int k{qp1q + 1}; k <= i; k++) {
        U[k - 1] = nrm * U[k - 1];
      }
    }
    if (q + 1 < 10) {
      nrm = e[q];
      if (nrm != 0.0) {
        rt = std::abs(nrm);
        nrm = rt / nrm;
        e[q] = rt;
        b_s[q + 1] *= nrm;
        qp1q = 10 * (q + 1);
        i = qp1q + 10;
        for (int k{qp1q + 1}; k <= i; k++) {
          Vf[k - 1] *= nrm;
        }
      }
    }
    snorm = std::fmax(snorm, std::fmax(std::abs(b_s[q]), std::abs(e[q])));
  }
  while ((m + 2 > 0) && (qp1 < 75)) {
    boolean_T exitg1;
    qjj = m + 1;
    jj = m + 1;
    exitg1 = false;
    while (!(exitg1 || (jj == 0))) {
      nrm = std::abs(e[jj - 1]);
      if ((nrm <= 2.2204460492503131E-16 *
                      (std::abs(b_s[jj - 1]) + std::abs(b_s[jj]))) ||
          (nrm <= 1.0020841800044864E-292) ||
          ((qp1 > 20) && (nrm <= 2.2204460492503131E-16 * snorm))) {
        e[jj - 1] = 0.0;
        exitg1 = true;
      } else {
        jj--;
      }
    }
    if (jj == m + 1) {
      qp1q = 4;
    } else {
      qq = m + 2;
      qp1q = m + 2;
      exitg1 = false;
      while ((!exitg1) && (qp1q >= jj)) {
        qq = qp1q;
        if (qp1q == jj) {
          exitg1 = true;
        } else {
          nrm = 0.0;
          if (qp1q < m + 2) {
            nrm = std::abs(e[qp1q - 1]);
          }
          if (qp1q > jj + 1) {
            nrm += std::abs(e[qp1q - 2]);
          }
          rt = std::abs(b_s[qp1q - 1]);
          if ((rt <= 2.2204460492503131E-16 * nrm) ||
              (rt <= 1.0020841800044864E-292)) {
            b_s[qp1q - 1] = 0.0;
            exitg1 = true;
          } else {
            qp1q--;
          }
        }
      }
      if (qq == jj) {
        qp1q = 3;
      } else if (qq == m + 2) {
        qp1q = 1;
      } else {
        qp1q = 2;
        jj = qq;
      }
    }
    switch (qp1q) {
    case 1: {
      rt = e[m];
      e[m] = 0.0;
      for (int k{qjj}; k >= jj + 1; k--) {
        double sm;
        sm = blas::xrotg(b_s[k - 1], rt, sqds);
        if (k > jj + 1) {
          double b;
          b = e[k - 2];
          rt = -sqds * b;
          e[k - 2] = b * sm;
        }
        blas::b_xrot(Vf, 10 * (k - 1) + 1, 10 * (m + 1) + 1, sm, sqds);
      }
    } break;
    case 2: {
      rt = e[jj - 1];
      e[jj - 1] = 0.0;
      for (int k{jj + 1}; k <= m + 2; k++) {
        double b;
        double sm;
        sm = blas::xrotg(b_s[k - 1], rt, sqds);
        b = e[k - 1];
        rt = -sqds * b;
        e[k - 1] = b * sm;
        blas::xrot(U, 36 * (k - 1) + 1, 36 * (jj - 1) + 1, sm, sqds);
      }
    } break;
    case 3: {
      double b;
      double scale;
      double sm;
      nrm = b_s[m + 1];
      scale = std::fmax(
          std::fmax(std::fmax(std::fmax(std::abs(nrm), std::abs(b_s[m])),
                              std::abs(e[m])),
                    std::abs(b_s[jj])),
          std::abs(e[jj]));
      sm = nrm / scale;
      nrm = b_s[m] / scale;
      rt = e[m] / scale;
      sqds = b_s[jj] / scale;
      b = ((nrm + sm) * (nrm - sm) + rt * rt) / 2.0;
      nrm = sm * rt;
      nrm *= nrm;
      if ((b != 0.0) || (nrm != 0.0)) {
        rt = std::sqrt(b * b + nrm);
        if (b < 0.0) {
          rt = -rt;
        }
        rt = nrm / (b + rt);
      } else {
        rt = 0.0;
      }
      rt += (sqds + sm) * (sqds - sm);
      nrm = sqds * (e[jj] / scale);
      for (int k{jj + 1}; k <= qjj; k++) {
        sm = blas::xrotg(rt, nrm, sqds);
        if (k > jj + 1) {
          e[k - 2] = rt;
        }
        nrm = e[k - 1];
        b = b_s[k - 1];
        e[k - 1] = sm * nrm - sqds * b;
        rt = sqds * b_s[k];
        b_s[k] *= sm;
        blas::b_xrot(Vf, 10 * (k - 1) + 1, 10 * k + 1, sm, sqds);
        b_s[k - 1] = sm * b + sqds * nrm;
        sm = blas::xrotg(b_s[k - 1], rt, sqds);
        b = e[k - 1];
        rt = sm * b + sqds * b_s[k];
        b_s[k] = -sqds * b + sm * b_s[k];
        nrm = sqds * e[k];
        e[k] *= sm;
        blas::xrot(U, 36 * (k - 1) + 1, 36 * k + 1, sm, sqds);
      }
      e[m] = rt;
      qp1++;
    } break;
    default:
      if (b_s[jj] < 0.0) {
        b_s[jj] = -b_s[jj];
        qp1q = 10 * jj;
        i = qp1q + 10;
        for (int k{qp1q + 1}; k <= i; k++) {
          Vf[k - 1] = -Vf[k - 1];
        }
      }
      qp1 = jj + 1;
      while ((jj + 1 < 10) && (b_s[jj] < b_s[qp1])) {
        rt = b_s[jj];
        b_s[jj] = b_s[qp1];
        b_s[qp1] = rt;
        blas::b_xswap(Vf, 10 * jj + 1, 10 * (jj + 1) + 1);
        blas::xswap(U, 36 * jj + 1, 36 * (jj + 1) + 1);
        jj = qp1;
        qp1++;
      }
      qp1 = 0;
      m--;
      break;
    }
  }
  for (int k{0}; k < 10; k++) {
    s[k] = b_s[k];
    std::copy(&Vf[k * 10],
              &Vf[static_cast<int>(static_cast<unsigned int>(k * 10) + 10U)],
              &V[k * 10]);
  }
}

void svd(const array<double, 1U> &A, array<double, 1U> &U, double s[7],
         double V[49])
{
  static double Vf[49];
  static double work[36];
  array<double, 1U> b_A;
  double b_s[7];
  double e[7];
  double nrm;
  double rt;
  double snorm;
  double sqds;
  int b_i;
  int i;
  int jj;
  int m;
  int qjj;
  int qp1;
  int qp1q;
  b_A.set_size(252);
  U.set_size(252);
  for (i = 0; i < 252; i++) {
    b_A[i] = A[i];
  }
  for (b_i = 0; b_i < 7; b_i++) {
    b_s[b_i] = 0.0;
    e[b_i] = 0.0;
  }
  std::memset(&work[0], 0, 36U * sizeof(double));
  for (i = 0; i < 252; i++) {
    U[i] = 0.0;
  }
  std::memset(&Vf[0], 0, 49U * sizeof(double));
  for (int q{0}; q < 7; q++) {
    boolean_T apply_transform;
    qp1 = q + 2;
    b_i = q + 36 * q;
    qp1q = b_i + 1;
    apply_transform = false;
    nrm = blas::xnrm2(36 - q, b_A, b_i + 1);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[b_i] < 0.0) {
        nrm = -nrm;
      }
      b_s[q] = nrm;
      if (std::abs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        i = (b_i - q) + 36;
        for (int k{qp1q}; k <= i; k++) {
          b_A[k - 1] = nrm * b_A[k - 1];
        }
      } else {
        i = (b_i - q) + 36;
        for (int k{qp1q}; k <= i; k++) {
          b_A[k - 1] = b_A[k - 1] / b_s[q];
        }
      }
      b_A[b_i] = b_A[b_i] + 1.0;
      b_s[q] = -b_s[q];
    } else {
      b_s[q] = 0.0;
    }
    for (jj = qp1; jj < 8; jj++) {
      qjj = q + 36 * (jj - 1);
      if (apply_transform) {
        qp1q = 36 - q;
        nrm = 0.0;
        for (int k{0}; k < qp1q; k++) {
          nrm += b_A[b_i + k] * b_A[qjj + k];
        }
        nrm = -(nrm / b_A[b_i]);
        if (!(nrm == 0.0)) {
          i = 35 - q;
          for (int k{0}; k <= i; k++) {
            qp1q = qjj + k;
            b_A[qp1q] = b_A[qp1q] + nrm * b_A[b_i + k];
          }
        }
      }
      e[jj - 1] = b_A[qjj];
    }
    for (jj = q + 1; jj < 37; jj++) {
      qp1q = (jj + 36 * q) - 1;
      U[qp1q] = b_A[qp1q];
    }
    if (q + 1 <= 5) {
      nrm = blas::b_xnrm2(6 - q, e, q + 2);
      if (nrm == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -nrm;
        } else {
          e[q] = nrm;
        }
        nrm = e[q];
        if (std::abs(e[q]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[q];
          for (int k{qp1}; k < 8; k++) {
            e[k - 1] *= nrm;
          }
        } else {
          for (int k{qp1}; k < 8; k++) {
            e[k - 1] /= nrm;
          }
        }
        e[q + 1]++;
        e[q] = -e[q];
        for (jj = qp1; jj < 37; jj++) {
          work[jj - 1] = 0.0;
        }
        for (jj = qp1; jj < 8; jj++) {
          blas::xaxpy(35 - q, e[jj - 1], b_A, (q + 36 * (jj - 1)) + 2, work,
                      q + 2);
        }
        for (jj = qp1; jj < 8; jj++) {
          blas::xaxpy(35 - q, -e[jj - 1] / e[q + 1], work, q + 2, b_A,
                      (q + 36 * (jj - 1)) + 2);
        }
      }
      for (jj = qp1; jj < 8; jj++) {
        Vf[(jj + 7 * q) - 1] = e[jj - 1];
      }
    }
  }
  m = 5;
  e[5] = b_A[221];
  e[6] = 0.0;
  for (int q{6}; q >= 0; q--) {
    qp1 = q + 2;
    b_i = q + 36 * q;
    if (b_s[q] != 0.0) {
      for (jj = qp1; jj < 8; jj++) {
        qjj = (q + 36 * (jj - 1)) + 1;
        blas::xaxpy(36 - q, -(blas::xdotc(36 - q, U, b_i + 1, U, qjj) / U[b_i]),
                    b_i + 1, U, qjj);
      }
      for (jj = q + 1; jj < 37; jj++) {
        qp1q = (jj + 36 * q) - 1;
        U[qp1q] = -U[qp1q];
      }
      U[b_i] = U[b_i] + 1.0;
      for (jj = 0; jj < q; jj++) {
        U[jj + 36 * q] = 0.0;
      }
    } else {
      for (jj = 0; jj < 36; jj++) {
        U[jj + 36 * q] = 0.0;
      }
      U[b_i] = 1.0;
    }
  }
  for (int q{6}; q >= 0; q--) {
    if ((q + 1 <= 5) && (e[q] != 0.0)) {
      qp1 = q + 2;
      qp1q = (q + 7 * q) + 2;
      for (jj = qp1; jj < 8; jj++) {
        b_i = (q + 7 * (jj - 1)) + 2;
        blas::xaxpy(6 - q,
                    -(blas::xdotc(6 - q, Vf, qp1q, Vf, b_i) / Vf[qp1q - 1]),
                    qp1q, Vf, b_i);
      }
    }
    for (jj = 0; jj < 7; jj++) {
      Vf[jj + 7 * q] = 0.0;
    }
    Vf[q + 7 * q] = 1.0;
  }
  qp1 = 0;
  snorm = 0.0;
  for (int q{0}; q < 7; q++) {
    nrm = b_s[q];
    if (nrm != 0.0) {
      rt = std::abs(nrm);
      nrm /= rt;
      b_s[q] = rt;
      if (q + 1 < 7) {
        e[q] /= nrm;
      }
      qp1q = 36 * q;
      i = qp1q + 36;
      for (int k{qp1q + 1}; k <= i; k++) {
        U[k - 1] = nrm * U[k - 1];
      }
    }
    if (q + 1 < 7) {
      nrm = e[q];
      if (nrm != 0.0) {
        rt = std::abs(nrm);
        nrm = rt / nrm;
        e[q] = rt;
        b_s[q + 1] *= nrm;
        qp1q = 7 * (q + 1);
        i = qp1q + 7;
        for (int k{qp1q + 1}; k <= i; k++) {
          Vf[k - 1] *= nrm;
        }
      }
    }
    snorm = std::fmax(snorm, std::fmax(std::abs(b_s[q]), std::abs(e[q])));
  }
  while ((m + 2 > 0) && (qp1 < 75)) {
    boolean_T exitg1;
    qjj = m + 1;
    jj = m + 1;
    exitg1 = false;
    while (!(exitg1 || (jj == 0))) {
      nrm = std::abs(e[jj - 1]);
      if ((nrm <= 2.2204460492503131E-16 *
                      (std::abs(b_s[jj - 1]) + std::abs(b_s[jj]))) ||
          (nrm <= 1.0020841800044864E-292) ||
          ((qp1 > 20) && (nrm <= 2.2204460492503131E-16 * snorm))) {
        e[jj - 1] = 0.0;
        exitg1 = true;
      } else {
        jj--;
      }
    }
    if (jj == m + 1) {
      qp1q = 4;
    } else {
      b_i = m + 2;
      qp1q = m + 2;
      exitg1 = false;
      while ((!exitg1) && (qp1q >= jj)) {
        b_i = qp1q;
        if (qp1q == jj) {
          exitg1 = true;
        } else {
          nrm = 0.0;
          if (qp1q < m + 2) {
            nrm = std::abs(e[qp1q - 1]);
          }
          if (qp1q > jj + 1) {
            nrm += std::abs(e[qp1q - 2]);
          }
          rt = std::abs(b_s[qp1q - 1]);
          if ((rt <= 2.2204460492503131E-16 * nrm) ||
              (rt <= 1.0020841800044864E-292)) {
            b_s[qp1q - 1] = 0.0;
            exitg1 = true;
          } else {
            qp1q--;
          }
        }
      }
      if (b_i == jj) {
        qp1q = 3;
      } else if (b_i == m + 2) {
        qp1q = 1;
      } else {
        qp1q = 2;
        jj = b_i;
      }
    }
    switch (qp1q) {
    case 1: {
      rt = e[m];
      e[m] = 0.0;
      for (int k{qjj}; k >= jj + 1; k--) {
        double sm;
        sm = blas::xrotg(b_s[k - 1], rt, sqds);
        if (k > jj + 1) {
          double b;
          b = e[k - 2];
          rt = -sqds * b;
          e[k - 2] = b * sm;
        }
        blas::xrot(Vf, 7 * (k - 1) + 1, 7 * (m + 1) + 1, sm, sqds);
      }
    } break;
    case 2: {
      rt = e[jj - 1];
      e[jj - 1] = 0.0;
      for (int k{jj + 1}; k <= m + 2; k++) {
        double b;
        double sm;
        sm = blas::xrotg(b_s[k - 1], rt, sqds);
        b = e[k - 1];
        rt = -sqds * b;
        e[k - 1] = b * sm;
        blas::xrot(U, 36 * (k - 1) + 1, 36 * (jj - 1) + 1, sm, sqds);
      }
    } break;
    case 3: {
      double b;
      double scale;
      double sm;
      nrm = b_s[m + 1];
      scale = std::fmax(
          std::fmax(std::fmax(std::fmax(std::abs(nrm), std::abs(b_s[m])),
                              std::abs(e[m])),
                    std::abs(b_s[jj])),
          std::abs(e[jj]));
      sm = nrm / scale;
      nrm = b_s[m] / scale;
      rt = e[m] / scale;
      sqds = b_s[jj] / scale;
      b = ((nrm + sm) * (nrm - sm) + rt * rt) / 2.0;
      nrm = sm * rt;
      nrm *= nrm;
      if ((b != 0.0) || (nrm != 0.0)) {
        rt = std::sqrt(b * b + nrm);
        if (b < 0.0) {
          rt = -rt;
        }
        rt = nrm / (b + rt);
      } else {
        rt = 0.0;
      }
      rt += (sqds + sm) * (sqds - sm);
      nrm = sqds * (e[jj] / scale);
      for (int k{jj + 1}; k <= qjj; k++) {
        sm = blas::xrotg(rt, nrm, sqds);
        if (k > jj + 1) {
          e[k - 2] = rt;
        }
        nrm = e[k - 1];
        b = b_s[k - 1];
        e[k - 1] = sm * nrm - sqds * b;
        rt = sqds * b_s[k];
        b_s[k] *= sm;
        blas::xrot(Vf, 7 * (k - 1) + 1, 7 * k + 1, sm, sqds);
        b_s[k - 1] = sm * b + sqds * nrm;
        sm = blas::xrotg(b_s[k - 1], rt, sqds);
        b = e[k - 1];
        rt = sm * b + sqds * b_s[k];
        b_s[k] = -sqds * b + sm * b_s[k];
        nrm = sqds * e[k];
        e[k] *= sm;
        blas::xrot(U, 36 * (k - 1) + 1, 36 * k + 1, sm, sqds);
      }
      e[m] = rt;
      qp1++;
    } break;
    default:
      if (b_s[jj] < 0.0) {
        b_s[jj] = -b_s[jj];
        qp1q = 7 * jj;
        i = qp1q + 7;
        for (int k{qp1q + 1}; k <= i; k++) {
          Vf[k - 1] = -Vf[k - 1];
        }
      }
      qp1 = jj + 1;
      while ((jj + 1 < 7) && (b_s[jj] < b_s[qp1])) {
        rt = b_s[jj];
        b_s[jj] = b_s[qp1];
        b_s[qp1] = rt;
        blas::xswap(Vf, 7 * jj + 1, 7 * (jj + 1) + 1);
        blas::xswap(U, 36 * jj + 1, 36 * (jj + 1) + 1);
        jj = qp1;
        qp1++;
      }
      qp1 = 0;
      m--;
      break;
    }
  }
  for (int k{0}; k < 7; k++) {
    s[k] = b_s[k];
    for (b_i = 0; b_i < 7; b_i++) {
      qp1q = b_i + 7 * k;
      V[qp1q] = Vf[qp1q];
    }
  }
}

} // namespace internal
} // namespace coder

// End of code generation (svd.cpp)
