////
#pragma once
#include <array>
#include <chrono>
#include <cmath>
#include <complex>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream> // to print some info
#include <vector>

int global_method_mask = 0;
int max_iteration_dichotomy = 10;

std::stringstream ss;
static bool isFirstCall = true; // to avoid delete the file manually

#define METHODMASK_LAPLACE_CYPOLY 0               // for single bounce
#define METHODMASK_LAGRANGE_GAUSSIAN 1            // test
#define METHODMASK_LINEARIZATION_QZ 2             // for multiple bounce
#define METHODMASK_LAPLACE_QR 4                   // for single bounce
#define METHODMASK_SPLINE_GAUSSIAN 8              // for cubic spline interpolation
#define METHODMASK_DICHOTOMY_GAUSSIAN 16          // for dichotomy
#define METHODMASK_DICHOTOMY_GAUSSIAN_WITH_LOG 32 // for dichotomy with log
#define METHODMASK_SPLINE_GAUSSIAN_WITH_LOG \
  512 // for cubic spline interpolation with log
#define METHODMASK_CUDA 1024

// Manually switch:
#define RESULTANT_SIMD
#define RESULTANT_WARN

namespace Resultant
{
  std::stringstream rss;

  // // RR
  // const int N_DEGREE = 16;
  // const int N_POLY = 100;

  // TT
  // const int N_DEGREE = 54;
  // const int N_POLY = 500;

  // R
  const int N_DEGREE = 4;
  const int N_POLY = 9;

  // T
  // const int N_DEGREE = 6;
  // const int N_POLY = 37;

  const int N_MAT = N_DEGREE + 1;

  double ___perf_time_coefficient = 0;
  double ___perf_time_bezout = 0;
  double ___perf_time_determinant = 0;
  double ___perf_time_fft = 0;
  double ___perf_time_solver1 = 0;
  double ___perf_time_solver2 = 0;
  int __perf_total_1d_sols = 0;
  int perf_count = 0;

  int global_poly_cutoff = N_POLY - 1;
  double global_poly_cutoff_eps = 1e-999;
  int global_mat_cutoff = N_DEGREE;

  // for eigensolver(QZ)

  int cnt = 0;
} // namespace Resultant