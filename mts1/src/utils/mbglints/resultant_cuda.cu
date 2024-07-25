// author: hao zhang, zhimin fan
#include "chrono_def.h"
#include "resultant_cuda.cuh"
#include <iostream>
#include <algorithm>
#include "polynomials.cuh"
#include "cyPolynomial.h"
#include "newton_cuda.cuh"

__constant__ double3 pD;
__constant__ double3 pL;

__constant__ int bezMat_deg;
__constant__ int bezMat_sz;

double get_bezout_matrix_time;
double eval_bezout_matrix_time;
double pick_section_time;
double bisection_solver_time;
double from_bezout_to_gamma_time;
double solve_back_time;

const int Cxz_deg = 10;

const int u2hat_deg = 5;
const int v2hat_deg = 5;
const int kappa2_deg = 4;

// #define BVP3_ALL_INIT() int i = blockIdx.x * blockDim.x + threadIdx.x;\
//                         BVP3<1> _pD = BVP3_init(pD);\
//                         BVP3<1> _pL = BVP3_init(pL);\
//                         BVP3<1> _p10 = BVP3_init(p10[i]);\
//                         BVP3<1> _n10 = BVP3_init(n10[i]);\
//                         BVP3<1> _p11 = BVP3_init(p11[i]);\
//                         BVP3<1> _n11 = BVP3_init(n11[i]);\
//                         BVP3<1> _p12 = BVP3_init(p12[i]);\
//                         BVP3<1> _n12 = BVP3_init(n12[i]);\
//                         BVP<2> u1, v1;\
//                         u1.a[0] = 0; u1.a[1] = 0; u1.a[2] = 1; u1.a[3] = 0;\
//                         v1.a[0] = 0; v1.a[1] = 1; v1.a[2] = 0; v1.a[3] = 0;\
//                         BVP3<2> t01 = BVP3_mul<1, 2, 2>(_p11, u1), t02 = BVP3_mul<1, 2, 2>(_p12, v1);\
//                         BVP3<2> t03 = BVP3_add<2, 2, 2>(t01, t02);\
//                         BVP3<2> x1 = BVP3_add<1, 2, 2>(_p10, t03);\
//                         BVP3<2> t04 = BVP3_mul<1, 2, 2>(_n11, u1), t05 = BVP3_mul<1, 2, 2>(_n12, v1);\
//                         BVP3<2> t06 = BVP3_add<2, 2, 2>(t04, t05);\
//                         BVP3<2> n1hat = BVP3_add<1, 2, 2>(_n10, t06);

// #define GET_BEZOUT(Dzy, Dxz)    divideByMax(Czy_); divideByMax(Cxz_); BVP<Cxz_deg> Czy = resize<Dzy, Cxz_deg>(Czy_); BVP<Cxz_deg> Cxz = resize<Dxz, Cxz_deg>(Cxz_);\
//                                 bezoutMatrix(Cxz, Czy, bezMats + i * (N_BEZOUT_TOTAL));\
//                                 for (int k = 0; k < Cxz_deg; k++)\
//                                     for (int j = 0; j < Cxz_deg; j++)\
//                                         Cxzs[i * MAXN * MAXN + k * Cxz_deg + j] = Cxz.a[k * Cxz_deg + j];

// __global__ void solve_one_1R(double3* __restrict__ p10, double3* __restrict__ n10,
//                             double3* __restrict__ p11, double3* __restrict__ n11,
//                             double3* __restrict__ p12, double3* __restrict__ n12,
//                             double* __restrict__ bezMats, double* __restrict__ Cxzs)
// {
//     BVP3_ALL_INIT()

//     BVP3<2> d0 = BVP3_sub<2, 1, 2>(x1, _pD);
//     BVP3<2> d1 = BVP3_sub<1, 2, 2>(_pL, x1);

//     // // 5 degree form
//     // // BVP d0_norm2 = BVP3_dot(d0, d0);
//     // // BVP d1_norm2 = BVP3_dot(d1, d1);
//     // // BVP3 c0 = BVP3_cross(d0, n1hat);
//     // // BVP3 c1 = BVP3_cross(d1, n1hat);
//     // // BVP3 c = BVP3_sub(BVP3_mul(BVP3_mul(c0, c0), d1_norm2), BVP3_mul(BVP3_mul(c1, c1), d0_norm2));

//     // // 4 degree form
//     BVP<3> d0_dot_n1hat = BVP3_dot<2, 2, 3>(d0, n1hat);
//     BVP<3> d1_dot_n1hat = BVP3_dot<2, 2, 3>(d1, n1hat);
//     BVP3<2> t1hat1 = BVP3_cross<2, 1, 2>(n1hat, _p11);
//     BVP3<2> t1hat2 = BVP3_cross<2, 1, 2>(n1hat, _p12);
//     BVP<3> d0_dot_t1hat2 = BVP3_dot<2, 2, 3>(d0, t1hat2);
//     BVP<3> d1_dot_t1hat2 = BVP3_dot<2, 2, 3>(d1, t1hat2);

//     BVP<5> Czy_; BVP<5> t1, t2;
//     bpm(d0_dot_n1hat, d1_dot_t1hat2, t1);
//     bpm(d0_dot_t1hat2, d1_dot_n1hat, t2);
//     bpa(t1, t2, Czy_);

//     BVP3<1> s = BVP3_sub<1, 1, 1>(_pL, _pD);
//     BVP3<3> cop = BVP3_cross<2, 2, 3>(BVP3_cross<2, 1, 2>(d0, s), BVP3_cross<2, 1, 2>(n1hat, s));
//     BVP<3> Cxz_, t3; bpa(cop.bvp[0], cop.bvp[1], t3); bpa(t3, cop.bvp[2], Cxz_);

//     GET_BEZOUT(5, 3)
// }

// __global__ void solve_one_2T(double3* p10, double3* n10,
//     double3* p11, double3* n11,
//     double3* p12, double3* n12,
//     double* bezMats, double* Cxzs)
// {
//     BVP3_ALL_INIT()
//     double eta = 1.5041833;

//     BVP3<2> d0 = BVP3_sub<2, 1, 2>(x1, _pD);
//     BVP3<2> d1 = BVP3_sub<1, 2, 2>(_pL, x1);
//     BVP<3> d0_norm2 = BVP3_dot<2, 2, 3>(d0, d0);
//     BVP<3> d1_norm2 = BVP3_dot<2, 2, 3>(d1, d1);
//     BVP3<3> c0 = BVP3_cross<2, 2, 3>(d0, n1hat);
//     BVP3<3> c1 = BVP3_cross<2, 2, 3>(d1, n1hat);
//     BVP<1> eeta; eeta.a[0] = eta * eta;
//     BVP3<7> c = BVP3_sub<7, 7, 7>(BVP3_mul<7, 1, 7>(BVP3_mul<5, 3, 7>(BVP3_mul<3, 3, 5>(c0, c0), d1_norm2), eeta), BVP3_mul<5, 3, 7>(BVP3_mul<3, 3, 5>(c1, c1), d0_norm2));
//     BVP<7> Czy_ = c.bvp[0];

//     BVP3<1> s = BVP3_sub<1, 1, 1>(_pL, _pD);
//     BVP3<3> cop = BVP3_cross<2, 2, 3>(BVP3_cross<2, 1, 2>(d0, s), BVP3_cross<2, 1, 2>(n1hat, s));
//     BVP<3> t1;
//     BVP<3> Cxz_; bpa(cop.bvp[0], cop.bvp[1], t1); bpa(t1, cop.bvp[2], Cxz_);

//     GET_BEZOUT(7, 3)
// }

__device__ void bezout_matrix(double *a, double *b, double *f)
{
    const int n = N_BVP - 1;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i; j < n; ++j)
        {
            // a[i] * b[j+1] - a[j+1] * b[i]
            int addrai = (2 * N_BVP - i + 1) * (i) / 2;
            int addrbj1 = (2 * N_BVP2 - j) * (j + 1) / 2;
            int addraj1 = (2 * N_BVP - j) * (j + 1) / 2;
            int addrbi = (2 * N_BVP2 - i + 1) * (i) / 2;
            upm(a + addrai, b + addrbj1, f + bezout_addr(i, j), (N_BVP - i), (N_BVP2 - j - 1));
            upms(a + addraj1, b + addrbi, f + bezout_addr(i, j), (N_BVP - j - 1), (N_BVP2 - i));
        }
    }

    for (size_t i = 1; i < n - 1; ++i)
        for (size_t j = i; j < n - 1; ++j)
            upa(f + bezout_addr(i, j), f + bezout_addr(i - 1, j + 1), f + bezout_addr(i, j), N_BEZOUT_ITEM - i - j);
}

__global__ void solve(double3 xD, double3 xL,
                      double3 *p10, double3 *n10,
                      double3 *p11, double3 *n11,
                      double3 *p12, double3 *n12,
                      double3 *p20, double3 *n20,
                      double3 *p21, double3 *n21,
                      double3 *p22, double3 *n22,
                      double *bvpa, double *bvpb, double *bezout)
{
}

__global__ void solve_one_11RR(double3 *p10, double3 *n10,
                               double3 *p11, double3 *n11,
                               double3 *p12, double3 *n12,
                               double3 *p20, double3 *n20,
                               double3 *p21, double3 *n21,
                               double3 *p22, double3 *n22,
                               double *bezMats, double *Cxzs,
                               double *u2hats, double *v2hats, double *kappa2s)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    double const1[1] = {1};
    double u1[3] = {0, 0, 1};
    double v1[3] = {0, 1, 0};
    double xD_x[1] = {pD.x};
    double xD_y[1] = {pD.y};
    double xD_z[1] = {pD.z};
    double xL_x[1] = {pL.x};
    double xL_y[1] = {pL.y};
    double xL_z[1] = {pL.z};
    double p10_x[1] = {p10[idx].x};
    double p10_y[1] = {p10[idx].y};
    double p10_z[1] = {p10[idx].z};
    double p11_x[1] = {p11[idx].x};
    double p11_y[1] = {p11[idx].y};
    double p11_z[1] = {p11[idx].z};
    double p12_x[1] = {p12[idx].x};
    double p12_y[1] = {p12[idx].y};
    double p12_z[1] = {p12[idx].z};
    double n10_x[1] = {n10[idx].x};
    double n10_y[1] = {n10[idx].y};
    double n10_z[1] = {n10[idx].z};
    double n11_x[1] = {n11[idx].x};
    double n11_y[1] = {n11[idx].y};
    double n11_z[1] = {n11[idx].z};
    double n12_x[1] = {n12[idx].x};
    double n12_y[1] = {n12[idx].y};
    double n12_z[1] = {n12[idx].z};
    double p20_x[1] = {p20[idx].x};
    double p20_y[1] = {p20[idx].y};
    double p20_z[1] = {p20[idx].z};
    double p21_x[1] = {p21[idx].x};
    double p21_y[1] = {p21[idx].y};
    double p21_z[1] = {p21[idx].z};
    double p22_x[1] = {p22[idx].x};
    double p22_y[1] = {p22[idx].y};
    double p22_z[1] = {p22[idx].z};
    double n20_x[1] = {n20[idx].x};
    double n20_y[1] = {n20[idx].y};
    double n20_z[1] = {n20[idx].z};
    double n21_x[1] = {n21[idx].x};
    double n21_y[1] = {n21[idx].y};
    double n21_z[1] = {n21[idx].z};
    double n22_x[1] = {n22[idx].x};
    double n22_y[1] = {n22[idx].y};
    double n22_z[1] = {n22[idx].z};
    double t1_x[3] = {0};
    bpm(u1, p11_x, t1_x, 2, 1, 2);
    double t1_y[3] = {0};
    bpm(u1, p11_y, t1_y, 2, 1, 2);
    double t1_z[3] = {0};
    bpm(u1, p11_z, t1_z, 2, 1, 2);
    bpma(v1, p12_x, t1_x, 1, 2, 1, 2);
    bpma(v1, p12_y, t1_y, 1, 2, 1, 2);
    bpma(v1, p12_z, t1_z, 1, 2, 1, 2);
    bpma(const1, p10_x, t1_x, 1, 1, 1, 2);
    bpma(const1, p10_y, t1_y, 1, 1, 1, 2);
    bpma(const1, p10_z, t1_z, 1, 1, 1, 2);
    double t2_x[3] = {0};
    bpm(u1, n11_x, t2_x, 2, 1, 2);
    double t2_y[3] = {0};
    bpm(u1, n11_y, t2_y, 2, 1, 2);
    double t2_z[3] = {0};
    bpm(u1, n11_z, t2_z, 2, 1, 2);
    bpma(v1, n12_x, t2_x, 1, 2, 1, 2);
    bpma(v1, n12_y, t2_y, 1, 2, 1, 2);
    bpma(v1, n12_z, t2_z, 1, 2, 1, 2);
    bpma(const1, n10_x, t2_x, 1, 1, 1, 2);
    bpma(const1, n10_y, t2_y, 1, 1, 1, 2);
    bpma(const1, n10_z, t2_z, 1, 1, 1, 2);
    double t4[1] = {-1.000000};
    double t3_x[1] = {0};
    bpm(t4, xD_x, t3_x, 1, 1, 1);
    double t3_y[1] = {0};
    bpm(t4, xD_y, t3_y, 1, 1, 1);
    double t3_z[1] = {0};
    bpm(t4, xD_z, t3_z, 1, 1, 1);
    double t5_x[3] = {0};
    bpa(t1_x, t3_x, t5_x, 2, 1, 2);
    double t5_y[3] = {0};
    bpa(t1_y, t3_y, t5_y, 2, 1, 2);
    double t5_z[3] = {0};
    bpa(t1_z, t3_z, t5_z, 2, 1, 2);
    double t6[6] = {0};
    bpm(t2_x, t2_x, t6, 2, 2, 3);
    bpma(t2_y, t2_y, t6, 1, 2, 2, 3);
    bpma(t2_z, t2_z, t6, 1, 2, 2, 3);
    double t7_x[10] = {0};
    bpm(t6, t5_x, t7_x, 3, 2, 4);
    double t7_y[10] = {0};
    bpm(t6, t5_y, t7_y, 3, 2, 4);
    double t7_z[10] = {0};
    bpm(t6, t5_z, t7_z, 3, 2, 4);
    double t8[6] = {0};
    bpm(t2_x, t5_x, t8, 2, 2, 3);
    bpma(t2_y, t5_y, t8, 1, 2, 2, 3);
    bpma(t2_z, t5_z, t8, 1, 2, 2, 3);
    bpma(t8, t2_x, t7_x, -2, 3, 2, 4);
    bpma(t8, t2_y, t7_y, -2, 3, 2, 4);
    bpma(t8, t2_z, t7_z, -2, 3, 2, 4);
    double t10[1] = {-1.000000};
    double t9_x[1] = {0};
    bpm(t10, p20_x, t9_x, 1, 1, 1);
    double t9_y[1] = {0};
    bpm(t10, p20_y, t9_y, 1, 1, 1);
    double t9_z[1] = {0};
    bpm(t10, p20_z, t9_z, 1, 1, 1);
    double t11_x[3] = {0};
    bpa(t1_x, t9_x, t11_x, 2, 1, 2);
    double t11_y[3] = {0};
    bpa(t1_y, t9_y, t11_y, 2, 1, 2);
    double t11_z[3] = {0};
    bpa(t1_z, t9_z, t11_z, 2, 1, 2);
    double t12_x[10] = {0};
    bpm(t7_y, p22_z, t12_x, 4, 1, 4);
    bpma(t7_z, p22_y, t12_x, -1, 4, 1, 4);
    double t12_y[10] = {0};
    bpm(t7_z, p22_x, t12_y, 4, 1, 4);
    bpma(t7_x, p22_z, t12_y, -1, 4, 1, 4);
    double t12_z[10] = {0};
    bpm(t7_x, p22_y, t12_z, 4, 1, 4);
    bpma(t7_y, p22_x, t12_z, -1, 4, 1, 4);
    double t13[15] = {0};
    bpm(t12_x, t11_x, t13, 4, 2, 5);
    bpma(t12_y, t11_y, t13, 1, 4, 2, 5);
    bpma(t12_z, t11_z, t13, 1, 4, 2, 5);
    double t14_x[3] = {0};
    bpm(t11_y, p21_z, t14_x, 2, 1, 2);
    bpma(t11_z, p21_y, t14_x, -1, 2, 1, 2);
    double t14_y[3] = {0};
    bpm(t11_z, p21_x, t14_y, 2, 1, 2);
    bpma(t11_x, p21_z, t14_y, -1, 2, 1, 2);
    double t14_z[3] = {0};
    bpm(t11_x, p21_y, t14_z, 2, 1, 2);
    bpma(t11_y, p21_x, t14_z, -1, 2, 1, 2);
    double t15[15] = {0};
    bpm(t14_x, t7_x, t15, 2, 4, 5);
    bpma(t14_y, t7_y, t15, 1, 2, 4, 5);
    bpma(t14_z, t7_z, t15, 1, 2, 4, 5);
    double t16_x[10] = {0};
    bpm(t7_y, p22_z, t16_x, 4, 1, 4);
    bpma(t7_z, p22_y, t16_x, -1, 4, 1, 4);
    double t16_y[10] = {0};
    bpm(t7_z, p22_x, t16_y, 4, 1, 4);
    bpma(t7_x, p22_z, t16_y, -1, 4, 1, 4);
    double t16_z[10] = {0};
    bpm(t7_x, p22_y, t16_z, 4, 1, 4);
    bpma(t7_y, p22_x, t16_z, -1, 4, 1, 4);
    double t17[10] = {0};
    bpm(t16_x, p21_x, t17, 4, 1, 4);
    bpma(t16_y, p21_y, t17, 1, 4, 1, 4);
    bpma(t16_z, p21_z, t17, 1, 4, 1, 4);
    double t18_x[15] = {0};
    bpm(t13, p21_x, t18_x, 5, 1, 5);
    double t18_y[15] = {0};
    bpm(t13, p21_y, t18_y, 5, 1, 5);
    double t18_z[15] = {0};
    bpm(t13, p21_z, t18_z, 5, 1, 5);
    bpma(t15, p22_x, t18_x, 1, 5, 1, 5);
    bpma(t15, p22_y, t18_y, 1, 5, 1, 5);
    bpma(t15, p22_z, t18_z, 1, 5, 1, 5);
    bpma(t17, p20_x, t18_x, 1, 4, 1, 5);
    bpma(t17, p20_y, t18_y, 1, 4, 1, 5);
    bpma(t17, p20_z, t18_z, 1, 4, 1, 5);
    double t20[1] = {-1.000000};
    double t19_x[15] = {0};
    bpm(t20, t18_x, t19_x, 1, 5, 5);
    double t19_y[15] = {0};
    bpm(t20, t18_y, t19_y, 1, 5, 5);
    double t19_z[15] = {0};
    bpm(t20, t18_z, t19_z, 1, 5, 5);
    bpma(t17, xL_x, t19_x, 1, 4, 1, 5);
    bpma(t17, xL_y, t19_y, 1, 4, 1, 5);
    bpma(t17, xL_z, t19_z, 1, 4, 1, 5);
    double t21_x[15] = {0};
    bpm(t13, n21_x, t21_x, 5, 1, 5);
    double t21_y[15] = {0};
    bpm(t13, n21_y, t21_y, 5, 1, 5);
    double t21_z[15] = {0};
    bpm(t13, n21_z, t21_z, 5, 1, 5);
    bpma(t15, n22_x, t21_x, 1, 5, 1, 5);
    bpma(t15, n22_y, t21_y, 1, 5, 1, 5);
    bpma(t15, n22_z, t21_z, 1, 5, 1, 5);
    bpma(t17, n20_x, t21_x, 1, 4, 1, 5);
    bpma(t17, n20_y, t21_y, 1, 4, 1, 5);
    bpma(t17, n20_z, t21_z, 1, 4, 1, 5);
    double t22_x[15] = {0};
    bpm(t21_y, p21_z, t22_x, 5, 1, 5);
    bpma(t21_z, p21_y, t22_x, -1, 5, 1, 5);
    double t22_y[15] = {0};
    bpm(t21_z, p21_x, t22_y, 5, 1, 5);
    bpma(t21_x, p21_z, t22_y, -1, 5, 1, 5);
    double t22_z[15] = {0};
    bpm(t21_x, p21_y, t22_z, 5, 1, 5);
    bpma(t21_y, p21_x, t22_z, -1, 5, 1, 5);
    double t23_x[15] = {0};
    bpm(t21_y, p22_z, t23_x, 5, 1, 5);
    bpma(t21_z, p22_y, t23_x, -1, 5, 1, 5);
    double t23_y[15] = {0};
    bpm(t21_z, p22_x, t23_y, 5, 1, 5);
    bpma(t21_x, p22_z, t23_y, -1, 5, 1, 5);
    double t23_z[15] = {0};
    bpm(t21_x, p22_y, t23_z, 5, 1, 5);
    bpma(t21_y, p22_x, t23_z, -1, 5, 1, 5);
    double t24[36] = {0};
    bpm(t7_x, t21_x, t24, 4, 5, 8);
    bpma(t7_y, t21_y, t24, 1, 4, 5, 8);
    bpma(t7_z, t21_z, t24, 1, 4, 5, 8);
    double t25[45] = {0};
    bpm(t19_x, t21_x, t25, 5, 5, 9);
    bpma(t19_y, t21_y, t25, 1, 5, 5, 9);
    bpma(t19_z, t21_z, t25, 1, 5, 5, 9);
    double t26[45] = {0};
    bpm(t19_x, t23_x, t26, 5, 5, 9);
    bpma(t19_y, t23_y, t26, 1, 5, 5, 9);
    bpma(t19_z, t23_z, t26, 1, 5, 5, 9);
    double t27[136] = {0};
    bpm(t24, t26, t27, 8, 9, 16);
    double t28[36] = {0};
    bpm(t7_x, t23_x, t28, 4, 5, 8);
    bpma(t7_y, t23_y, t28, 1, 4, 5, 8);
    bpma(t7_z, t23_z, t28, 1, 4, 5, 8);
    bpma(t25, t28, t27, 1, 9, 8, 16);
    double t30[1] = {-1.000000};
    double t29_x[3] = {0};
    bpm(t30, t1_x, t29_x, 1, 2, 2);
    double t29_y[3] = {0};
    bpm(t30, t1_y, t29_y, 1, 2, 2);
    double t29_z[3] = {0};
    bpm(t30, t1_z, t29_z, 1, 2, 2);
    double t31_x[3] = {0};
    bpa(t29_x, xL_x, t31_x, 2, 1, 2);
    double t31_y[3] = {0};
    bpa(t29_y, xL_y, t31_y, 2, 1, 2);
    double t31_z[3] = {0};
    bpa(t29_z, xL_z, t31_z, 2, 1, 2);
    double t32_x[21] = {0};
    bpm(t19_y, t31_z, t32_x, 5, 2, 6);
    bpma(t19_z, t31_y, t32_x, -1, 5, 2, 6);
    double t32_y[21] = {0};
    bpm(t19_z, t31_x, t32_y, 5, 2, 6);
    bpma(t19_x, t31_z, t32_y, -1, 5, 2, 6);
    double t32_z[21] = {0};
    bpm(t19_x, t31_y, t32_z, 5, 2, 6);
    bpma(t19_y, t31_x, t32_z, -1, 5, 2, 6);
    double t33[55] = {0};
    bpm(t32_x, t21_x, t33, 6, 5, 10);
    bpma(t32_y, t21_y, t33, 1, 6, 5, 10);
    bpma(t32_z, t21_z, t33, 1, 6, 5, 10);
    // for (int i = 0; i < 136; i++)
    //     bvpa[idx * N_BVPA + i] = t27[i];
    double sum = 0;
    const double normal = 1e-16; // make this larger leads to slower but more accurate solve_cuda kernels
    for (int i = 0; i < N_BVPA; i++)
        sum += abs(t27[i]);
    sum /= normal;
    for (int i = 0; i < N_BVPA; i++)
        t27[i] /= sum;
    sum = 0;
    for (int i = 0; i < N_BVPB; i++)
        sum += abs(t33[i]);
    sum /= normal;
    for (int i = 0; i < N_BVPB; i++)
        t33[i] /= sum;

    for (int i = 0; i < N_BVPB; i++)
        Cxzs[idx * N_BVPB + i] = t33[i];
    for (int i = 0; i < N_BVPU; i++)
        u2hats[idx * N_BVPU + i] = t13[i];
    for (int i = 0; i < N_BVPU; i++)
        v2hats[idx * N_BVPU + i] = t15[i];
    for (int i = 0; i < N_BVPK; i++)
        kappa2s[idx * N_BVPK + i] = t17[i];
    bezout_matrix(t27, t33, bezMats + idx * N_BEZOUT_TOTAL);
    // ! bug: Cxzs[0][0] not consistent with CPU version
    // double* bezMats, double* Cxzs,
    // double* u2hats, double* v2hats, double* kappa2s)
}

__global__ void eval_bezout_matrix(cudaTextureObject_t bezMatsTex, double *__restrict__ values)
{
    int ind = blockIdx.x * blockDim.x + threadIdx.x;
    int i = ind / (global_poly_cutoff + 1), j = ind % (global_poly_cutoff + 1);
    double pos = j * 1.0 / global_poly_cutoff;
    values[ind] = evalMatrixPolynomialDeterminantTex(bezMatsTex, bezMat_sz, bezMat_deg, i, pos);
}

__global__ void bisection_solver(cudaTextureObject_t bezMatsTex, int *__restrict__ segments, double *__restrict__ f, double *__restrict__ res)
{
    int ind = blockIdx.x * blockDim.x + threadIdx.x;
    int x = segments[ind];
    int i = x / (global_poly_cutoff + 1), j = x % (global_poly_cutoff + 1);
    double l = j * 1.0 / global_poly_cutoff, r = (j + 1) * 1.0 / global_poly_cutoff;
    double mid = (l + r) / 2;
    for (int _ = 1; _ < max_iteration_dichotomy_cuda; _++)
    {
        double fm = evalMatrixPolynomialDeterminantTex(bezMatsTex, bezMat_sz, bezMat_deg, i, mid);
        if (fm * f[ind] > 0)
            r = mid;
        else
            l = mid;
        mid = (l + r) / 2;
    }
    res[ind] = mid;
}

int get_bvp_idx(int i, int j, int n)
{
    return i * (n + n - i + 1) / 2 + j;
}

std::vector<std::tuple<double, double, double, double>> solve_back_1(std::vector<double> &result, double *Cxzs, int Cxz_deg, double global_poly_cutoff_eps)
{
    std::vector<std::tuple<double, double, double, double>> sols;
    double roots2[9 * (N_POLY - 1)];
    double doubleervalMin = 0;
    double doubleervalMax = 1;
    double errorThreshold = 1e-9;
    double x_tolerance = 0;
    for (double gamma : result)
    {
        double uniploy[N_DEGREE] = {0};
        for (int i = 0; i < Cxz_deg; i++)
        {
            uniploy[i] = 0;
            for (int j = Cxz_deg - 1 - i; j >= 0; j--)
                uniploy[i] = uniploy[i] * gamma + Cxzs[get_bvp_idx(i, j, Cxz_deg)];
        }

        double prefix_max[N_DEGREE] = {0}, suffix_max[N_DEGREE];
        for (int i = 0; i < N_DEGREE; i++)
            prefix_max[i] = suffix_max[i] = uniploy[i];
        for (int i = 1; i < N_DEGREE; i++)
            prefix_max[i] = max(prefix_max[i], prefix_max[i - 1]);
        for (int i = N_DEGREE - 1; i >= 0; i--)
            suffix_max[i] = max(suffix_max[i], suffix_max[i + 1]);

        int truncate_degree = 9;
        for (int i = 3; i < N_DEGREE - 1; i++)
        {
            if (suffix_max[i + 1] * 1e-9 < prefix_max[i])
            {
                truncate_degree = i;
                break;
            }
        }

        int numRoot2 = 0;
        if (truncate_degree <= 4)
        {
            const int const_deg = 4;
            cy::Polynomial<double, const_deg> poly2;
            for (int k = 0; k <= const_deg; k++)
                poly2.coef[k] = uniploy[k];
            numRoot2 = poly2.Roots(roots2, doubleervalMin, doubleervalMax, errorThreshold);
        }
        else if (truncate_degree <= 5)
        {
            const int const_deg = 5;
            cy::Polynomial<double, const_deg> poly2;
            for (int k = 0; k <= const_deg; k++)
                poly2.coef[k] = uniploy[k];
            numRoot2 = poly2.Roots(roots2, doubleervalMin, doubleervalMax, errorThreshold);
        }
        else if (truncate_degree <= 6)
        {
            const int const_deg = 6;
            cy::Polynomial<double, const_deg> poly2;
            for (int k = 0; k <= const_deg; k++)
                poly2.coef[k] = uniploy[k];
            numRoot2 = poly2.Roots(roots2, doubleervalMin, doubleervalMax, errorThreshold);
        }
        else if (truncate_degree <= 7)
        {
            const int const_deg = 7;
            cy::Polynomial<double, const_deg> poly2;
            for (int k = 0; k <= const_deg; k++)
                poly2.coef[k] = uniploy[k];
            numRoot2 = poly2.Roots(roots2, doubleervalMin, doubleervalMax, errorThreshold);
        }
        else if (truncate_degree <= 8)
        {
            const int const_deg = 8;
            cy::Polynomial<double, const_deg> poly2;
            for (int k = 0; k <= const_deg; k++)
                poly2.coef[k] = uniploy[k];
            numRoot2 = poly2.Roots(roots2, doubleervalMin, doubleervalMax, errorThreshold);
        }
        else
        {
            const int const_deg = 9;
            cy::Polynomial<double, const_deg> poly2;
            for (int k = 0; k <= const_deg; k++)
                poly2.coef[k] = uniploy[k];
            numRoot2 = poly2.Roots(roots2, doubleervalMin, doubleervalMax, errorThreshold);
        }

        for (int i = 0; i < numRoot2; i++)
        {
            double beta = roots2[i];
            if (beta < -x_tolerance || beta > 1 + x_tolerance || beta + gamma > 1 + x_tolerance)
                continue;
            double alpha = 1.0 - beta - gamma;
            sols.push_back(std::make_tuple(alpha, beta, 0.333, 0.333));
        }
    }
    return sols;
}

std::vector<std::tuple<double, double, double, double>> solve_back_2(std::vector<double> &result, double *Cxzs, int Cxz_deg, double *u2hat, double *v2hat, double *kappa2, double global_poly_cutoff_eps)
{
    std::vector<std::tuple<double, double, double, double>> sols = solve_back_1(result, Cxzs, Cxz_deg, global_poly_cutoff_eps), sols2;
    int sols_cnt = sols.size();
    for (int i = 0; i < sols_cnt; i++)
    {
        double uniploy[N_DEGREE] = {0};
        double alpha = std::get<0>(sols[i]), beta = std::get<1>(sols[i]);
        double gamma = 1.0 - alpha - beta;
        for (int j = 0; j < u2hat_deg; j++)
        {
            uniploy[j] = 0;
            for (int k = u2hat_deg - 1 - j; k >= 0; k--)
                uniploy[j] = uniploy[j] * gamma + u2hat[get_bvp_idx(j, k, u2hat_deg)];
        }
        double u2hat_val = 0.0;
        for (int j = u2hat_deg - 1; j >= 0; j--)
            u2hat_val = u2hat_val * beta + uniploy[j];

        for (int j = 0; j < v2hat_deg; j++)
        {
            uniploy[j] = 0;
            for (int k = v2hat_deg - 1 - j; k >= 0; k--)
                uniploy[j] = uniploy[j] * gamma + v2hat[get_bvp_idx(j, k, v2hat_deg)];
        }
        double v2hat_val = 0.0;
        for (int j = v2hat_deg - 1; j >= 0; j--)
            v2hat_val = v2hat_val * beta + uniploy[j];

        for (int j = 0; j < kappa2_deg; j++)
        {
            uniploy[j] = 0;
            for (int k = kappa2_deg - 1 - j; k >= 0; k--)
                uniploy[j] = uniploy[j] * gamma + kappa2[get_bvp_idx(j, k, kappa2_deg)];
        }
        double kappa2_val = 0.0;
        for (int j = kappa2_deg - 1; j >= 0; j--)
            kappa2_val = kappa2_val * beta + uniploy[j];

        double beta2 = u2hat_val / kappa2_val;
        double gamma2 = v2hat_val / kappa2_val;

        double alpha2 = 1 - beta2 - gamma2;

        if (alpha <= 0 || beta <= 0 || gamma <= 0)
            continue;
        if (alpha2 <= 0 || beta2 <= 0 || gamma2 <= 0)
            continue;
        sols2.push_back(std::make_tuple(alpha, beta, alpha2, beta2));
    }
    return sols2;
}

std::vector<std::vector<std::tuple<double, double, double, double>>> solve_cuda(
    int chain_type, int N,
    double *bezMat_, int bezMat_deg_, int bezMat_sz_,
    double *Cxzs_, int Cxz_deg_,
    double *u2hat_, double *v2hat_, double *kappa2_,
    int cutoff_resultant, float cutoff_eps_resultant, int maxIterationDichotomy)
{
    double *bezMats;
    cudaMalloc((void **)&bezMats, N * (N_BEZOUT_TOTAL) * sizeof(double));
    cudaMemcpy(bezMats, bezMat_, N * (N_BEZOUT_TOTAL) * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpyToSymbol(global_poly_cutoff, &cutoff_resultant, sizeof(int));
    cudaMemcpyToSymbol(bezMat_deg, &bezMat_deg_, sizeof(int));
    cudaMemcpyToSymbol(bezMat_sz, &bezMat_sz_, sizeof(int));
    cudaMemcpyToSymbol(max_iteration_dichotomy_cuda, &maxIterationDichotomy, sizeof(int));
    int threadsPerBlock = 32;

    cudaResourceDesc bezMatsResDesc;
    memset(&bezMatsResDesc, 0, sizeof(bezMatsResDesc));
    bezMatsResDesc.resType = cudaResourceTypeLinear;
    bezMatsResDesc.res.linear.devPtr = bezMats;
    bezMatsResDesc.res.linear.desc.f = cudaChannelFormatKindSigned;
    bezMatsResDesc.res.linear.desc.x = 32;
    bezMatsResDesc.res.linear.desc.y = 32;
    bezMatsResDesc.res.linear.sizeInBytes = N * (N_BEZOUT_TOTAL) * sizeof(double);

    cudaTextureDesc bezMatsTexDesc;
    memset(&bezMatsTexDesc, 0, sizeof(bezMatsTexDesc));
    bezMatsTexDesc.readMode = cudaReadModeElementType;

    cudaTextureObject_t bezMatsTex;
    cudaCreateTextureObject(&bezMatsTex, &bezMatsResDesc, &bezMatsTexDesc, NULL);

    double *values;
    cudaMalloc((void **)&values, N * (cutoff_resultant + 1) * sizeof(double));
    int blocksPerGrid = (N * (cutoff_resultant + 1) - 1) / threadsPerBlock + 1;
    auto start = CHRONO_NOW;
    auto start_ = start;
    eval_bezout_matrix<<<blocksPerGrid, threadsPerBlock>>>(bezMatsTex, values);
    // this kernel uses float precision for efficiency
    // it will be better to recheck the chosen intervals using double precision
    cudaDeviceSynchronize();
    auto end = CHRONO_NOW;
    eval_bezout_matrix_time = CHRONO_DIFF(end - start) * 1e-3;

    double *v = new double[N * (cutoff_resultant + 1)];
    cudaMemcpy(v, values, N * (cutoff_resultant + 1) * sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(values);

    std::vector<int> segments_;
    std::vector<double> f_;
    std::vector<std::vector<double>> results;
    results.resize(N);

    start = CHRONO_NOW;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < cutoff_resultant; j++)
        {
            int ind = i * (cutoff_resultant + 1) + j;
            if (v[ind] == 0)
            {
                results[i].push_back(v[ind]);
                continue;
            }
            if (v[ind] * v[ind + 1] <= 0 && v[ind] != 0 && v[ind + 1] != 0)
            {
                segments_.push_back(ind);
                f_.push_back(v[ind] < 0 ? 1 : -1);
            }
        }
        if (v[i * (cutoff_resultant + 1) + cutoff_resultant] == 0)
        {
            results[i].push_back(v[i * (cutoff_resultant + 1) + cutoff_resultant]);
        }
    }
    end = CHRONO_NOW;
    pick_section_time = CHRONO_DIFF(end - start) * 1e-3;

    std::vector<std::vector<std::tuple<double, double, double, double>>> sols;
    sols.resize(N);
    if (segments_.empty())
    {
        cudaFree(bezMats);
        cudaDestroyTextureObject(bezMatsTex);
        return sols;
    }

    int *segments;
    double *res, *f;
    cudaMalloc((void **)&segments, segments_.size() * sizeof(int));
    cudaMalloc((void **)&res, segments_.size() * sizeof(double));
    cudaMalloc((void **)&f, segments_.size() * sizeof(double));
    cudaMemcpy(segments, segments_.data(), segments_.size() * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(f, f_.data(), f_.size() * sizeof(double), cudaMemcpyHostToDevice);
    blocksPerGrid = (segments_.size() - 1) / threadsPerBlock + 1;

    start = CHRONO_NOW;
    bisection_solver<<<blocksPerGrid, threadsPerBlock>>>(bezMatsTex, segments, f, res);
    cudaDeviceSynchronize();
    end = CHRONO_NOW;
    bisection_solver_time = CHRONO_DIFF(end - start) * 1e-3;
    from_bezout_to_gamma_time = CHRONO_DIFF(end - start_) * 1e-3;

    double *res_ = new double[segments_.size()];
    cudaMemcpy(res_, res, segments_.size() * sizeof(double), cudaMemcpyDeviceToHost);

    for (int i = 0; i < segments_.size(); i++)
        results[segments_[i] / (cutoff_resultant + 1)].push_back(res_[i]);

    cudaFree(bezMats);
    cudaFree(segments);
    cudaFree(res);
    cudaDestroyTextureObject(bezMatsTex);

    start = CHRONO_NOW;
    int cnt = 0;
    for (std::vector<double> &v : results)
    {
        if (chain_type < 10)
            sols[cnt] = (solve_back_1(v, Cxzs_ + cnt * N_BVPB, Cxz_deg_, cutoff_eps_resultant));
        else
            sols[cnt] = (solve_back_2(v, Cxzs_ + cnt * N_BVPB, Cxz_deg_, u2hat_ + cnt * N_BVPU, v2hat_ + cnt * N_BVPU, kappa2_ + cnt * N_BVPK, cutoff_eps_resultant));
        cnt++;
    }
    end = CHRONO_NOW;
    solve_back_time = CHRONO_DIFF(end - start) * 1e-3;

    return sols;
}

std::vector<std::vector<std::tuple<double, double, double, double>>> solve_cuda(
    int chain_type, // 1R, 2T, 11RR, ...
    double3 &pD_,
    double3 &pL_,
    const std::vector<double3> &p10_,
    const std::vector<double3> &n10_,
    const std::vector<double3> &p11_,
    const std::vector<double3> &n11_,
    const std::vector<double3> &p12_,
    const std::vector<double3> &n12_,
    const std::vector<double3> &p20_,
    const std::vector<double3> &n20_,
    const std::vector<double3> &p21_,
    const std::vector<double3> &n21_,
    const std::vector<double3> &p22_,
    const std::vector<double3> &n22_,
    int cutoff_matrix,
    int cutoff_resultant,
    float cutoff_eps_resultant,
    int maxIterationDichotomy)
{
    int N = p10_.size();
    int threadsPerBlock = 64;
    int blocksPerGrid = (N - 1) / threadsPerBlock + 1;

    cudaMemcpyToSymbol(pD, &pD_, sizeof(double3));
    cudaMemcpyToSymbol(pL, &pL_, sizeof(double3));

    cudaMemcpyToSymbol(global_poly_cutoff, &cutoff_resultant, sizeof(int));
    cutoff_matrix++;
    if (N_MAT < cutoff_matrix)
        cutoff_matrix = N_MAT;
    // cudaMemcpyToSymbol(global_mat_cutoff, &cutoff_matrix, sizeof(int)); DO NOT SUPPORT
    cudaMemcpyToSymbol(max_iteration_dichotomy_cuda, &maxIterationDichotomy, sizeof(int));

    if (cutoff_matrix != global_mat_cutoff)
        std::cout << "Warning: parameter cutoff_matrix is not equal to the builtin global_mat_cutoff !!!" << std::endl;

    double3 *p10, *n10, *p11, *n11, *p12, *n12, *p20, *n20, *p21, *n21, *p22, *n22;
    cudaMalloc((void **)&p10, N * sizeof(double3));
    cudaMemcpy(p10, p10_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);
    cudaMalloc((void **)&n10, N * sizeof(double3));
    cudaMemcpy(n10, n10_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);
    cudaMalloc((void **)&p11, N * sizeof(double3));
    cudaMemcpy(p11, p11_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);
    cudaMalloc((void **)&n11, N * sizeof(double3));
    cudaMemcpy(n11, n11_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);
    cudaMalloc((void **)&p12, N * sizeof(double3));
    cudaMemcpy(p12, p12_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);
    cudaMalloc((void **)&n12, N * sizeof(double3));
    cudaMemcpy(n12, n12_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);

    double *bezMats;
    cudaMalloc((void **)&bezMats, N * (N_BEZOUT_TOTAL) * sizeof(double));
    int bezMat_deg_ = 24, bezMat_sz_ = 15;
    cudaMemcpyToSymbol(bezMat_deg, &bezMat_deg_, sizeof(int));
    cudaMemcpyToSymbol(bezMat_sz, &bezMat_sz_, sizeof(int));

    double *Cxzs;
    cudaMalloc((void **)&Cxzs, N * N_BVPB * sizeof(double));

    double *u2hat, *v2hat, *kappa2;

    auto start = CHRONO_NOW;

    // if (chain_type == 1) {
    //     solve_one_1R<<<blocksPerGrid, threadsPerBlock>>>(p10, n10, p11, n11, p12, n12, bezMats, Cxzs);
    //     cudaDeviceSynchronize();
    // }
    // if (chain_type == 2) {
    //     solve_one_2T<<<blocksPerGrid, threadsPerBlock>>>(p10, n10, p11, n11, p12, n12, bezMats, Cxzs);
    //     cudaDeviceSynchronize();
    // }
    if (chain_type == 11)
    {
        cudaMalloc((void **)&u2hat, N * N_BVPU * sizeof(double));
        cudaMalloc((void **)&v2hat, N * N_BVPU * sizeof(double));
        cudaMalloc((void **)&kappa2, N * N_BVPK * sizeof(double));
        cudaMalloc((void **)&p20, N * sizeof(double3));
        cudaMemcpy(p20, p20_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);
        cudaMalloc((void **)&n20, N * sizeof(double3));
        cudaMemcpy(n20, n20_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);
        cudaMalloc((void **)&p21, N * sizeof(double3));
        cudaMemcpy(p21, p21_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);
        cudaMalloc((void **)&n21, N * sizeof(double3));
        cudaMemcpy(n21, n21_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);
        cudaMalloc((void **)&p22, N * sizeof(double3));
        cudaMemcpy(p22, p22_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);
        cudaMalloc((void **)&n22, N * sizeof(double3));
        cudaMemcpy(n22, n22_.data(), N * sizeof(double3), cudaMemcpyHostToDevice);

        solve_one_11RR<<<blocksPerGrid, threadsPerBlock>>>(p10, n10, p11, n11, p12, n12, p20, n20, p21, n21, p22, n22, bezMats, Cxzs, u2hat, v2hat, kappa2);
        cudaDeviceSynchronize();
        cudaFree(p20);
        cudaFree(n20);
        cudaFree(p21);
        cudaFree(n21);
        cudaFree(p22);
        cudaFree(n22);
    }
    // TODO: 22TT
    auto end = CHRONO_NOW;
    get_bezout_matrix_time = CHRONO_DIFF(end - start) * 1e-3;

    cudaFree(p10);
    cudaFree(n10);
    cudaFree(p11);
    cudaFree(n11);
    cudaFree(p12);
    cudaFree(n12);

    double *u2hat_, *v2hat_, *kappa2_;

    if (chain_type > 10)
    {
        u2hat_ = new double[N * N_BVPU];
        v2hat_ = new double[N * N_BVPU];
        kappa2_ = new double[N * N_BVPK];
        cudaMemcpy(u2hat_, u2hat, N * N_BVPU * sizeof(double), cudaMemcpyDeviceToHost);
        cudaMemcpy(v2hat_, v2hat, N * N_BVPU * sizeof(double), cudaMemcpyDeviceToHost);
        cudaMemcpy(kappa2_, kappa2, N * N_BVPK * sizeof(double), cudaMemcpyDeviceToHost);
        cudaFree(u2hat);
        cudaFree(v2hat);
        cudaFree(kappa2);
    }

    double *Cxzs_ = new double[N * N_BVPB];
    cudaMemcpy(Cxzs_, Cxzs, N * N_BVPB * sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(Cxzs);

    double *bezMats_ = new double[N * (N_BEZOUT_TOTAL)];
    cudaMemcpy(bezMats_, bezMats, N * (N_BEZOUT_TOTAL) * sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(bezMats);

    return solve_cuda(chain_type, N, bezMats_, bezMat_deg_, bezMat_sz_, Cxzs_, Cxz_deg, u2hat_, v2hat_, kappa2_, cutoff_resultant, cutoff_eps_resultant, maxIterationDichotomy);
}
