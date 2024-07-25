//
#pragma once
#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <iomanip>
#include <complex>
#include <fstream>
#include <sstream>
#include <limits>
#include <array>
#include <fftw3.h>
#include <Eigen/Eigenvalues>
#include "cyPolynomial.h"
#pragma comment(linker, "/STACK:999999999") // avoid stack overflow

#include "resultant_common.h"
#include "resultant_uvp.h"
#include "resultant_bvp.h"
#include "resultant_det.h"
#include "resultant_qz.h"
#include "resultant_elimination.h"

namespace Resultant
{

    std::vector<std::tuple<double, double, double, double>> solveImpl(
        int chain_type, // 1R, 2T, 11RR, ...
        const std::vector<double> &pD_,
        const std::vector<double> &pL_,
        const std::vector<double> &p10_,
        const std::vector<double> &n10_,
        const std::vector<double> &p11_,
        const std::vector<double> &n11_,
        const std::vector<double> &p12_,
        const std::vector<double> &n12_,
        const std::vector<double> &p20_,
        const std::vector<double> &n20_,
        const std::vector<double> &p21_,
        const std::vector<double> &n21_,
        const std::vector<double> &p22_,
        const std::vector<double> &n22_,
        bool use_fft,
        int cutoff_matrix,
        int cutoff_resultant,
        float cutoff_eps_resultant,
        int methodMask,
        int maxIterationDichotomy,
        int pieceIdx,
        double vmin,
        double vmax)
    {
        // ! WARN: pi = pi0 + u pi1 + v pi2    (pi1/2 is ei1/2 in the paper)

        global_poly_cutoff_eps = cutoff_eps_resultant;
        global_poly_cutoff = cutoff_resultant;
        global_method_mask = methodMask;
        max_iteration_dichotomy = maxIterationDichotomy;

        auto ___time_begin = CHRONO_NOW;

        typedef BivariatePolynomial BVP;

        BVP3 pD = {BVP(1, pD_[0]), BVP(1, pD_[1]), BVP(1, pD_[2])};
        BVP3 pL = {BVP(1, pL_[0]), BVP(1, pL_[1]), BVP(1, pL_[2])};

        BVP3 p10 = {BVP(1, p10_[0]), BVP(1, p10_[1]), BVP(1, p10_[2])};
        BVP3 p11 = {BVP(1, p11_[0]), BVP(1, p11_[1]), BVP(1, p11_[2])};
        BVP3 p12 = {BVP(1, p12_[0]), BVP(1, p12_[1]), BVP(1, p12_[2])};
        BVP3 n10 = {BVP(1, n10_[0]), BVP(1, n10_[1]), BVP(1, n10_[2])};
        BVP3 n11 = {BVP(1, n11_[0]), BVP(1, n11_[1]), BVP(1, n11_[2])};
        BVP3 n12 = {BVP(1, n12_[0]), BVP(1, n12_[1]), BVP(1, n12_[2])};

        BVP3 p20 = {BVP(1, p20_[0]), BVP(1, p20_[1]), BVP(1, p20_[2])};
        BVP3 p21 = {BVP(1, p21_[0]), BVP(1, p21_[1]), BVP(1, p21_[2])};
        BVP3 p22 = {BVP(1, p22_[0]), BVP(1, p22_[1]), BVP(1, p22_[2])};
        BVP3 n20 = {BVP(1, n20_[0]), BVP(1, n20_[1]), BVP(1, n20_[2])};
        BVP3 n21 = {BVP(1, n21_[0]), BVP(1, n21_[1]), BVP(1, n21_[2])};
        BVP3 n22 = {BVP(1, n22_[0]), BVP(1, n22_[1]), BVP(1, n22_[2])};

        BVP u1({{0, 0}, {1, 0}});
        BVP v1({{0, 1}, {0, 0}});

        BVP3 xD = pD;
        BVP3 xL = pL;
        BVP3 x1 = p10 + p11 * u1 + p12 * v1;
        BVP3 n1hat = n10 + n11 * u1 + n12 * v1;

        BVP Czy;
        BVP Cxz;
        BVP u2hat;
        BVP v2hat;
        BVP kappa2;

        double valid_v_min = 1;
        double valid_v_max = 0;

        global_mat_cutoff = std::min(N_MAT, cutoff_matrix + 1);

        // ! hat means unnormalized in the code, which is opposite to the paper
        if (chain_type == 1)
        {
            BVP3 d0 = x1 - xD;
            BVP3 d1 = xL - x1;

            // 4 degree form
            BVP d0_dot_n1hat = d0.dot(n1hat);
            BVP d1_dot_n1hat = d1.dot(n1hat);
            BVP3 t1hat1 = n1hat.cross(p11);
            BVP3 t1hat2 = n1hat.cross(p12);
            BVP d0_dot_t1hat2 = d0.dot(t1hat2);
            BVP d1_dot_t1hat2 = d1.dot(t1hat2);
            Czy = d0_dot_n1hat * d1_dot_t1hat2 + d0_dot_t1hat2 * d1_dot_n1hat;

            BVP3 s = xL - xD;
            BVP3 cop = (d0.cross(s)).cross(n1hat.cross(s));
            Cxz = cop.bvp[0]; // projection to only one axis may fail in some cases

            valid_v_min = vmin;
            valid_v_max = vmax;
        }
        else if (chain_type == 2)
        {
            // 6 degree form
            double eta = 1.5041833;
            BVP3 d0 = x1 - xD;
            BVP3 d1 = xL - x1;
            BVP d0_norm2 = d0.dot(d0);
            BVP d1_norm2 = d1.dot(d1);
            BVP3 c0 = d0.cross(n1hat);
            BVP3 c1 = d1.cross(n1hat);
            BVP3 c = c0 * c0 * d1_norm2 * BVP(1, eta * eta) - c1 * c1 * d0_norm2;
            Czy = c.bvp[0];

            BVP3 s = xL - xD;
            BVP3 cop = (d0.cross(s)).cross(n1hat.cross(s));
            Cxz = cop.bvp[0];

            valid_v_min = vmin;
            valid_v_max = vmax;
        }
        else if (chain_type == 11)
        {
            // // * bounce = 2, RR, degree = 15
            BVP3 d0 = x1 - xD;
            BVP3 omega1hat = d0 * (n1hat.dot(n1hat)) - n1hat * (n1hat.dot(d0)) * BVP(1, 2);

            u2hat = omega1hat.cross(p22).dot(x1 - p20);
            v2hat = (x1 - p20).cross(p21).dot(omega1hat);
            kappa2 = omega1hat.cross(p22).dot(p21);

            BVP3 x2hat = p20 * kappa2 + p21 * u2hat + p22 * v2hat;
            BVP3 d2hat = xL * kappa2 - x2hat;
            BVP3 n2hat = n20 * kappa2 + n21 * u2hat + n22 * v2hat;

            valid_v_min = vmin;
            valid_v_max = vmax;

            BVP3 t21hat = n2hat.cross(p21);
            BVP3 t22hat = n2hat.cross(p22);

            BVP omega1hat_dot_n2hat = omega1hat.dot(n2hat);
            BVP d2hat_dot_n2hat = d2hat.dot(n2hat);

            Czy = omega1hat_dot_n2hat * (d2hat.dot(t22hat)) + d2hat_dot_n2hat * (omega1hat.dot(t22hat));

            BVP3 s = xL - x1;
            Cxz = (d2hat.cross(s)).dot(n2hat);
        }
        else if (chain_type == 22)
        {
            double eta = 1.5041833;
            BVP3 d0 = x1 - xD;
            BVP3 p0 = p10, p1 = p10 + p11, p2 = p12 + p10;
            BVP norm1 = (p0 - xD).dot(p0 - xD), norm2 = (p1 - xD).dot(p1 - xD), norm3 = (p2 - xD).dot(p2 - xD);
            const double mu1 = std::max(std::max(norm1.coeffs[0][0], norm2.coeffs[0][0]), norm3.coeffs[0][0]);
            valid_v_min = vmin;
            valid_v_max = vmax;

            BVP beta1 = n1hat.dot(n1hat) * d0.dot(d0) - (n1hat.dot(n1hat) * d0.dot(d0) - d0.dot(n1hat) * d0.dot(n1hat)) * BVP(1, 1 / (eta * eta));
            beta1 = beta1 * BVP(1, 1 / mu1);
            BVP3 first_term = (d0 * n1hat.dot(n1hat) - n1hat * d0.dot(n1hat)) * BVP(1, 1 / eta);
            BVP numerator;
            BVP denominator;
            if (pieceIdx == 6)
            {
                // 2 degree rational approximant :
                const double a_0 = 5.88428458e-04, a_1 = 7.61441386e-01, a_2 = 3.40458305e+00,
                             b_0 = 7.50718012e-02, b_1 = 2.55906806e+00, b_2 = 1.54868566e+00;
                numerator = BVP(1, a_0) + BVP(1, a_1) * beta1 + BVP(1, a_2) * beta1 * beta1;
                denominator = BVP(1, b_0) + BVP(1, b_1) * beta1 + BVP(1, b_2) * beta1 * beta1;
            }
            else if (pieceIdx == 7)
            {
                // 3 degree rational approximant :
                const double a_0 = 4.64579103e-05, a_1 = 2.78083875e+01, a_2 = 7.49056119e+02, a_3 = 1.16778434e+03,
                             b_0 = 1.32404066e+00, b_1 = 2.10703627e+02, b_2 = 1.34168102e+03, b_3 = 3.91642093e+02;
                numerator = BVP(1, a_0) + BVP(1, a_1) * beta1 + BVP(1, a_2) * beta1 * beta1 + BVP(1, a_3) * beta1 * beta1 * beta1;
                denominator = BVP(1, b_0) + BVP(1, b_1) * beta1 + BVP(1, b_2) * beta1 * beta1 + BVP(1, b_3) * beta1 * beta1 * beta1;
            }
            else
            {
                // piecewise rational approximant:
                const double a_0list[6] = {2.67348464e+00, 1.26026334, 785.90082722, 0.37606781, 0.04569061, 0.93887338};
                const double a_1list[6] = {3.12209378e+03, 374.80397103, 58559.841858, 8.89488513, 0.43232208, 4.10143067};
                const double b_0list[6] = {1.61215679e+02, 38.43473291, 12000.86283901, 3.19627254, 0.24561921, 3.4129053};
                const double b_1list[6] = {1.94853114e+04, 1174.42253488, 91776.72858574, 8.11321508, 0.2494023, 1.62996014};
                const double vminlist[6] = {0.000, 0.005, 0.02, 0.08, 0.2, 0.5};
                const double vmaxlist[6] = {0.005, 0.02, 0.08, 0.2, 0.5, 1.0};
                double a_0 = a_0list[pieceIdx];
                double a_1 = a_1list[pieceIdx];
                double b_0 = b_0list[pieceIdx];
                double b_1 = b_1list[pieceIdx];
                numerator = BVP(1, a_0) + BVP(1, a_1) * beta1;
                denominator = BVP(1, b_0) + BVP(1, b_1) * beta1;
            }

            BVP3 omega1hat = first_term * denominator * BVP(1, 1 / std::sqrt(mu1)) - n1hat * numerator;
            u2hat = omega1hat.cross(p22).dot(x1 - p20);
            v2hat = (x1 - p20).cross(p21).dot(omega1hat);
            kappa2 = omega1hat.cross(p22).dot(p21);
            BVP3 x2hat = p20 * kappa2 + p21 * u2hat + p22 * v2hat;
            BVP3 d1hat = x2hat - x1 * kappa2;
            BVP3 d2hat = xL * kappa2 - x2hat;
            BVP3 n2hat = n20 * kappa2 + n21 * u2hat + n22 * v2hat;
            BVP d1_norm2 = d1hat.dot(d1hat);
            BVP d2_norm2 = d2hat.dot(d2hat);
            BVP3 c1 = d1hat.cross(n2hat);
            BVP3 c2 = d2hat.cross(n2hat);
            BVP3 c = c1 * c1 * d2_norm2 - c2 * c2 * d1_norm2 * BVP(1, eta * eta);
            Czy = c.bvp[0] * BVP(1, rand()) + c.bvp[1] * BVP(1, rand()) + c.bvp[2] * BVP(1, rand());
            BVP3 s = xL - x1;
            BVP3 cop = ((x2hat - x1 * kappa2).cross(s)).cross(n2hat.cross(s));
            Cxz = cop.bvp[0] * BVP(1, rand()) + cop.bvp[1] * BVP(1, rand()) + cop.bvp[2] * BVP(1, rand());
        }
        else
        {
            std::cout << "unsupported chain type" << std::endl;
        }

        valid_v_min = 0;
        valid_v_max = 1;

        int local_cutoff_matrix = std::min(N_MAT, cutoff_matrix + 1);

        Czy.resize(local_cutoff_matrix, local_cutoff_matrix);
        Cxz.resize(local_cutoff_matrix, local_cutoff_matrix);

        Czy.divideByMax();
        Cxz.divideByMax();

        auto ___time_end = CHRONO_NOW;
        ___perf_time_coefficient += CHRONO_DIFF(___time_end - ___time_begin) * 1e-3;

#ifndef QZ_SOLVER
        UnivariatePolynomial poly_u(0);
        poly_u = resultant_elimination<false>(Czy, Cxz, cutoff_matrix, cutoff_resultant);
        auto ans = solve_equ(poly_u, Cxz, u2hat, v2hat, kappa2, chain_type);

        return ans;
#else
        UnivariatePolynomial poly_u(0);
        if (methodMask & METHODMASK_LINEARIZATION_QZ)
        {
            std::vector<double> result_u = resultant_elimination_qz<false>(Czy, Cxz, cutoff_matrix, cutoff_resultant);
            return solve_equ_qz(result_u, Cxz, u2hat, v2hat, kappa2, chain_type);
        }
        else
        {
            auto poly_bezoutMatrix = resultant_elimination<false>(Czy, Cxz, cutoff_matrix, cutoff_resultant, valid_v_min, valid_v_max);
            auto ans = solve_equ(poly_bezoutMatrix.first, poly_bezoutMatrix.second, Cxz, u2hat, v2hat, kappa2, chain_type, valid_v_min, valid_v_max);

            return ans;
        }
#endif
    }

    std::vector<std::tuple<double, double, double, double>> solve(
        int chain_type, // 1R, 2T, 11RR, ...
        const std::vector<double> &pD_,
        const std::vector<double> &pL_,
        const std::vector<double> &p10_,
        const std::vector<double> &n10_,
        const std::vector<double> &p11_,
        const std::vector<double> &n11_,
        const std::vector<double> &p12_,
        const std::vector<double> &n12_,
        const std::vector<double> &p20_,
        const std::vector<double> &n20_,
        const std::vector<double> &p21_,
        const std::vector<double> &n21_,
        const std::vector<double> &p22_,
        const std::vector<double> &n22_,
        bool use_fft,
        int cutoff_matrix,
        int cutoff_resultant,
        float cutoff_eps_resultant,
        int methodMask,
        int maxIterationDichotomy)
    {
        int n = chain_type == 22 ? 6 : 1;

        std::vector<std::tuple<double, double, double, double>> ans;
        auto pD = pD_, pL = pL_;
        auto p10 = p10_, n10 = n10_;
        auto p11 = p10_, n11 = n10_;
        auto p12 = p10_, n12 = n10_;
        auto p20 = p10_, n20 = n10_;
        auto p21 = p10_, n21 = n10_;
        auto p22 = p10_, n22 = n10_;
        for (int dlswap = 0; dlswap < (chain_type == 11 ? 1 : 1); dlswap++)
        {
            const int NSEG = 1;
            const int n_seg = (chain_type == 22 ? NSEG : 1);
            for (int j = 0; j < n_seg; j++)
            {
                double lb = j * 1.0 / n_seg;
                double rb = (j + 1) * 1.0 / n_seg;
                double len = rb - lb;
                for (int i = 0; i < n; i++)
                {
                    auto tmp = solveImpl(chain_type, pD,
                                         pL,
                                         p10_,
                                         n10_,
                                         p11_,
                                         n11_,
                                         p12_,
                                         n12_,
                                         p20_,
                                         n20_,
                                         p21_,
                                         n21_,
                                         p22_,
                                         n22_,
                                         use_fft,
                                         cutoff_matrix,
                                         cutoff_resultant,
                                         cutoff_eps_resultant,
                                         methodMask,
                                         maxIterationDichotomy,
                                         i, lb, rb);
                    if (dlswap == 1)
                    {
                        for (auto &[a, b, c, d] : tmp)
                        {
                            swap(a, c);
                            swap(b, d);
                        }
                    }
                    ans.insert(ans.end(), tmp.begin(), tmp.end());
                }
            }
            swap(pD, pL);
        }
        return ans;
    }

    void printStats(bool use_resultant_fft)
    {
        std::cout << "perf_time_coefficient: " << ___perf_time_coefficient / perf_count << " us" << std::endl;
        std::cout << "perf_time_bezout     : " << ___perf_time_bezout / perf_count << " us" << std::endl;
        std::cout << "perf_time_determinant: " << ___perf_time_determinant / perf_count << " us" << std::endl;
        std::cout << "    TOTAL1:            " << (___perf_time_coefficient + ___perf_time_bezout + ___perf_time_determinant) / perf_count << " us" << std::endl;
        std::cout << "    TOTAL1 (/4):       " << (___perf_time_coefficient + ___perf_time_bezout + ___perf_time_determinant) / perf_count / 4 << " us" << std::endl;
        std::cout << "perf_time_solver1    : " << ___perf_time_solver1 / perf_count << " us" << std::endl;
        std::cout << "perf_time_solver2    : " << ___perf_time_solver2 / perf_count << " us" << std::endl;
        std::cout << "    TOTAL2:            " << (___perf_time_solver1 + ___perf_time_solver2) / perf_count << " us" << std::endl;
        std::cout << "    TOTAL (1/4):       " << (___perf_time_coefficient + ___perf_time_bezout + ___perf_time_determinant) / perf_count / 4 + (___perf_time_solver1 + ___perf_time_solver2) / perf_count << " us" << std::endl;
        std::cout << "total_1d_solutions:    " << __perf_total_1d_sols << "" << std::endl;
    }

}