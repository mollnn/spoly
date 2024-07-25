#include <cuda_runtime.h>
#include <chrono>
#include <vector>
#include <tuple>

const int N_BVP = 16;
const int N_BVP2 = 10;
const int N_BVPA = 136;
const int N_BVPB = 55;
const int N_BVPU = 15;
const int N_BVPK = 10;
const int N_BEZOUT_ITEM = 24;
const int N_BEZOUT_TOTAL = 1213;

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
    int maxIterationDichotomy);

std::vector<std::vector<std::tuple<double, double, double, double>>> solve_cuda(
    int chain_type, int N,
    double *bezMat_, int bezMat_deg_, int bezMat_sz_,
    double *Cxzs_, int Cxz_deg_,
    double *u2hat_, double *v2hat_, double *kappa2_,
    int cutoff_resultant, float cutoff_eps_resultant, int maxIterationDichotomy);

std::vector<std::vector<std::tuple<double, double, double, double>>> solve_11RR_newton(double3 pD, double3 pL, const std::vector<double3> &p10, const std::vector<double3> &p11, const std::vector<double3> &p12,
                                                                                       const std::vector<double3> &p20, const std::vector<double3> &p21, const std::vector<double3> &p22, const std::vector<double3> &n10, const std::vector<double3> &n11,
                                                                                       const std::vector<double3> &n12, const std::vector<double3> &n20, const std::vector<double3> &n21, const std::vector<double3> &n22);