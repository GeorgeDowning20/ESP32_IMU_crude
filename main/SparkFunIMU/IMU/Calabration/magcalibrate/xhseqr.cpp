//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xhseqr.cpp
//
// Code generation for function 'xhseqr'
//

// Include files
#include "xhseqr.h"
#include "magcalibrate_rtwutil.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xnrm2.h"
#include <cmath>

// Function Definitions
namespace coder {
namespace internal {
namespace lapack {
int xhseqr(double h[9], double z[9])
{
  static double v[3];
  double bb;
  double d;
  double h12;
  double h22;
  double rt1r;
  double rt2r;
  double s;
  double tr;
  int i;
  int info;
  int kdefl;
  boolean_T exitg1;
  info = 0;
  h[2] = 0.0;
  kdefl = 0;
  i = 2;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    double tst;
    int b_i;
    int c_k;
    int i1;
    int its;
    int k;
    int knt;
    int nr;
    boolean_T converged;
    boolean_T exitg2;
    k = -1;
    converged = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      boolean_T exitg3;
      k = i - 1;
      exitg3 = false;
      while ((!exitg3) && (k + 2 > 1)) {
        b_i = k + 3 * k;
        d = std::abs(h[b_i + 1]);
        if (d <= 3.0062525400134592E-292) {
          exitg3 = true;
        } else {
          nr = 3 * (k + 1);
          knt = k + nr;
          h12 = h[knt + 1];
          tr = std::abs(h12);
          bb = h[b_i];
          tst = std::abs(bb) + tr;
          if (tst == 0.0) {
            if (k >= 1) {
              tst = std::abs(h[k]);
            }
            if (k + 3 <= 3) {
              tst += std::abs(h[nr + 2]);
            }
          }
          if (d <= 2.2204460492503131E-16 * tst) {
            rt2r = std::abs(h[knt]);
            h12 = std::abs(bb - h12);
            tst = std::fmax(tr, h12);
            bb = std::fmin(tr, h12);
            s = tst + bb;
            if (std::fmin(d, rt2r) * (std::fmax(d, rt2r) / s) <=
                std::fmax(3.0062525400134592E-292,
                          2.2204460492503131E-16 * (bb * (tst / s)))) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }
      if (k + 2 > 1) {
        h[(k + 3 * k) + 1] = 0.0;
      }
      if (k + 2 >= i) {
        converged = true;
        exitg2 = true;
      } else {
        int m;
        kdefl++;
        if (kdefl - kdefl / 20 * 20 == 0) {
          s = std::abs(h[i + 3 * (i - 1)]) + std::abs(h[i - 1]);
          tst = 0.75 * s + h[i + 3 * i];
          h12 = -0.4375 * s;
          bb = s;
          h22 = tst;
        } else if (kdefl - kdefl / 10 * 10 == 0) {
          s = std::abs(h[1]) + std::abs(h[5]);
          tst = 0.75 * s + h[0];
          h12 = -0.4375 * s;
          bb = s;
          h22 = tst;
        } else {
          nr = i + 3 * (i - 1);
          tst = h[nr - 1];
          bb = h[nr];
          nr = i + 3 * i;
          h12 = h[nr - 1];
          h22 = h[nr];
        }
        s = ((std::abs(tst) + std::abs(h12)) + std::abs(bb)) + std::abs(h22);
        if (s == 0.0) {
          rt1r = 0.0;
          tst = 0.0;
          rt2r = 0.0;
          bb = 0.0;
        } else {
          tst /= s;
          bb /= s;
          h12 /= s;
          h22 /= s;
          tr = (tst + h22) / 2.0;
          tst = (tst - tr) * (h22 - tr) - h12 * bb;
          bb = std::sqrt(std::abs(tst));
          if (tst >= 0.0) {
            rt1r = tr * s;
            rt2r = rt1r;
            tst = bb * s;
            bb = -tst;
          } else {
            rt1r = tr + bb;
            rt2r = tr - bb;
            if (std::abs(rt1r - h22) <= std::abs(rt2r - h22)) {
              rt1r *= s;
              rt2r = rt1r;
            } else {
              rt2r *= s;
              rt1r = rt2r;
            }
            tst = 0.0;
            bb = 0.0;
          }
        }
        m = i - 1;
        if (i - 1 >= 1) {
          h12 = h[0] - rt2r;
          s = (std::abs(h12) + std::abs(bb)) + std::abs(h[1]);
          tr = h[1] / s;
          v[0] = (tr * h[3] + (h[0] - rt1r) * (h12 / s)) - tst * (bb / s);
          v[1] = tr * (((h[0] + h[4]) - rt1r) - rt2r);
          v[2] = tr * h[5];
          s = (std::abs(v[0]) + std::abs(v[1])) + std::abs(v[2]);
          v[0] /= s;
          v[1] /= s;
          v[2] /= s;
        }
        for (int b_k{m}; b_k <= i; b_k++) {
          nr = (i - b_k) + 2;
          if (nr >= 3) {
            nr = 3;
          }
          if (b_k > i - 1) {
            knt = ((b_k - 2) * 3 + b_k) - 1;
            for (c_k = 0; c_k < nr; c_k++) {
              v[c_k] = h[knt + c_k];
            }
          }
          h12 = v[0];
          rt2r = 0.0;
          if (nr > 0) {
            tst = blas::xnrm2(nr - 1, v);
            if (tst != 0.0) {
              bb = rt_hypotd_snf(v[0], tst);
              if (v[0] >= 0.0) {
                bb = -bb;
              }
              if (std::abs(bb) < 1.0020841800044864E-292) {
                knt = 0;
                do {
                  knt++;
                  for (c_k = 2; c_k <= nr; c_k++) {
                    v[c_k - 1] *= 9.9792015476736E+291;
                  }
                  bb *= 9.9792015476736E+291;
                  h12 *= 9.9792015476736E+291;
                } while ((std::abs(bb) < 1.0020841800044864E-292) &&
                         (knt < 20));
                bb = rt_hypotd_snf(h12, blas::xnrm2(nr - 1, v));
                if (h12 >= 0.0) {
                  bb = -bb;
                }
                rt2r = (bb - h12) / bb;
                tst = 1.0 / (h12 - bb);
                for (c_k = 2; c_k <= nr; c_k++) {
                  v[c_k - 1] *= tst;
                }
                for (c_k = 0; c_k < knt; c_k++) {
                  bb *= 1.0020841800044864E-292;
                }
                h12 = bb;
              } else {
                rt2r = (bb - v[0]) / bb;
                tst = 1.0 / (v[0] - bb);
                for (c_k = 2; c_k <= nr; c_k++) {
                  v[c_k - 1] *= tst;
                }
                h12 = bb;
              }
            }
          }
          if (b_k > i - 1) {
            h[b_k - 1] = h12;
            h[b_k] = 0.0;
            if (b_k < i) {
              h[2] = 0.0;
            }
          }
          d = v[1];
          h12 = rt2r * v[1];
          if (nr == 3) {
            s = v[2];
            tst = rt2r * v[2];
            for (nr = b_k; nr < 4; nr++) {
              c_k = 3 * (nr - 1);
              knt = b_k + c_k;
              bb = h[knt - 1];
              tr = (bb + d * h[knt]) + s * h[c_k + 2];
              h[knt - 1] = bb - tr * rt2r;
              h[knt] -= tr * h12;
              h[c_k + 2] -= tr * tst;
            }
            if (b_k + 3 <= i + 1) {
              b_i = b_k + 2;
            } else {
              b_i = i;
            }
            for (nr = 0; nr <= b_i; nr++) {
              c_k = nr + 3 * (b_k - 1);
              bb = h[c_k];
              knt = nr + 3 * b_k;
              tr = (bb + d * h[knt]) + s * h[nr + 6];
              h[c_k] = bb - tr * rt2r;
              h[knt] -= tr * h12;
              h[nr + 6] -= tr * tst;
            }
            c_k = 3 * (b_k - 1);
            bb = z[c_k];
            tr = (bb + v[1] * z[3 * b_k]) + v[2] * z[6];
            z[c_k] = bb - tr * rt2r;
            z[3 * b_k] -= tr * h12;
            z[6] -= tr * tst;
            bb = z[c_k + 1];
            knt = 3 * b_k + 1;
            tr = (bb + v[1] * z[knt]) + v[2] * z[7];
            z[c_k + 1] = bb - tr * rt2r;
            z[knt] -= tr * h12;
            z[7] -= tr * tst;
            bb = z[c_k + 2];
            knt = 3 * b_k + 2;
            tr = (bb + v[1] * z[knt]) + v[2] * z[8];
            z[c_k + 2] = bb - tr * rt2r;
            z[knt] -= tr * h12;
            z[8] -= tr * tst;
          } else if (nr == 2) {
            for (nr = b_k; nr < 4; nr++) {
              b_i = b_k + 3 * (nr - 1);
              s = h[b_i - 1];
              h22 = h[b_i];
              tr = s + d * h22;
              s -= tr * rt2r;
              h[b_i - 1] = s;
              h22 -= tr * h12;
              h[b_i] = h22;
            }
            for (nr = 0; nr <= i; nr++) {
              b_i = nr + 3 * (b_k - 1);
              s = h[b_i];
              i1 = nr + 3 * b_k;
              h22 = h[i1];
              tr = s + d * h22;
              s -= tr * rt2r;
              h[b_i] = s;
              h22 -= tr * h12;
              h[i1] = h22;
            }
            b_i = 3 * (b_k - 1);
            d = z[b_i];
            s = z[3 * b_k];
            tr = d + v[1] * s;
            d -= tr * rt2r;
            z[b_i] = d;
            s -= tr * h12;
            z[3 * b_k] = s;
            d = z[b_i + 1];
            i1 = 3 * b_k + 1;
            s = z[i1];
            tr = d + v[1] * s;
            d -= tr * rt2r;
            z[b_i + 1] = d;
            s -= tr * h12;
            z[i1] = s;
            d = z[b_i + 2];
            i1 = 3 * b_k + 2;
            s = z[i1];
            tr = d + v[1] * s;
            d -= tr * rt2r;
            z[b_i + 2] = d;
            s -= tr * h12;
            z[i1] = s;
          }
        }
        its++;
      }
    }
    if (!converged) {
      info = i + 1;
      exitg1 = true;
    } else {
      if ((k + 2 != i + 1) && (k + 2 == i)) {
        b_i = i + 3 * i;
        d = h[b_i - 1];
        i1 = 3 * (i - 1);
        nr = i + i1;
        s = h[nr];
        h22 = h[b_i];
        reflapack::xdlanv2(h[nr - 1], d, s, h22, bb, h12, tr, rt2r, rt1r);
        h[b_i - 1] = d;
        h[nr] = s;
        h[b_i] = h22;
        if (i + 1 < 3) {
          nr = (i + 1) * 3 + i;
          b_i = 1 - i;
          for (int b_k{0}; b_k <= b_i; b_k++) {
            knt = nr + b_k * 3;
            tst = h[knt];
            h12 = h[knt - 1];
            h[knt] = rt2r * tst - rt1r * h12;
            h[knt - 1] = rt2r * h12 + rt1r * tst;
          }
        }
        if (i - 1 >= 1) {
          nr = i * 3;
          b_i = static_cast<unsigned char>(i - 1);
          for (int b_k{0}; b_k < b_i; b_k++) {
            knt = nr + b_k;
            tst = h[knt];
            c_k = i1 + b_k;
            h12 = h[c_k];
            h[knt] = rt2r * tst - rt1r * h12;
            h[c_k] = rt2r * h12 + rt1r * tst;
          }
        }
        nr = i * 3;
        tst = rt2r * z[i1] + rt1r * z[nr];
        z[nr] = rt2r * z[nr] - rt1r * z[i1];
        z[i1] = tst;
        tst = z[nr + 1];
        h12 = z[i1 + 1];
        z[nr + 1] = rt2r * tst - rt1r * h12;
        z[i1 + 1] = rt2r * h12 + rt1r * tst;
        tst = z[nr + 2];
        h12 = z[i1 + 2];
        z[nr + 2] = rt2r * tst - rt1r * h12;
        z[i1 + 2] = rt2r * h12 + rt1r * tst;
      }
      kdefl = 0;
      i = k;
    }
  }
  h[2] = 0.0;
  return info;
}

} // namespace lapack
} // namespace internal
} // namespace coder

// End of code generation (xhseqr.cpp)
