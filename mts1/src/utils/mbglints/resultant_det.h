#pragma once
#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <iomanip>
#include <complex>
#include <fstream>
#include <sstream> // to print some info
#include <limits>
#include <array>
#include "resultant_bvp.h"

namespace Resultant
{

    using namespace std;

    UnivariatePolynomialMatrix bezout_matrix(const std::vector<UnivariatePolynomial> &a, const std::vector<UnivariatePolynomial> &b)
    {
        size_t n = a.size() - 1;
        UnivariatePolynomialMatrix f(n, std::vector<UnivariatePolynomial>(n, UnivariatePolynomial({0})));
        for (size_t i = 0; i < n; ++i)
            for (size_t j = i; j < n; ++j)
                f[i][j] = a[i] * b[j + 1] - b[i] * a[j + 1];
        for (size_t i = 1; i < n - 1; ++i)
            for (size_t j = i; j < n - 1; ++j)
                f[i][j] = f[i][j] + f[i - 1][j + 1];
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < i; ++j)
                f[i][j] = f[j][i];

        // modify f
        int m = -1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                if (!f[i][j].equalToZero())
                    m = std::max(m, std::max(i, j));
            }
        }
        for (int k = m + 1; k < n; k++)
        {
            f[k][k] = UnivariatePolynomial(1, 1);
        }

        // // normalize
        // double sum = 0;
        // for(int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         for (int k = 0; k < f[i][j].size; k++)
        //             sum += std::abs(f[i][j].coeffs[k]);
        //     }
        // }
        // sum /= 1e10;
        // for(int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         for (int k = 0; k < f[i][j].size; k++)
        //             f[i][j].coeffs[k] /= sum;
        //     }
        // }

        return f;
    }

    UnivariatePolynomialMatrix getMinorMatrix(const UnivariatePolynomialMatrix &matrix, size_t row, size_t col)
    {
        UnivariatePolynomialMatrix minor(matrix.size() - 1, std::vector<UnivariatePolynomial>(matrix[0].size() - 1, UnivariatePolynomial(0)));

        size_t minor_i = 0;
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            if (i == row)
                continue;
            size_t minor_j = 0;
            for (size_t j = 0; j < matrix[i].size(); ++j)
            {
                if (j == col)
                    continue;
                minor[minor_i][minor_j] = matrix[i][j];
                ++minor_j;
            }
            ++minor_i;
        }

        return minor;
    }

    std::vector<pair<UnivariatePolynomial, pair<double, double>>> determinant(const UnivariatePolynomialMatrix &matrix)
    {
        size_t n = matrix.size();
        std::vector<pair<UnivariatePolynomial, pair<double, double>>> res;

        if (n == 1)
        {
            UnivariatePolynomial temp = matrix[0][0];
            res.push_back(make_pair(temp, make_pair(0.0, 1.0)));
            return res;
        }
        // ! the code below causes crush
        else if (n == 2)
        {
            UnivariatePolynomial temp = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
            res.push_back(make_pair(temp, make_pair(0.0, 1.0)));
            return res;
        }
        else if (n == 3)
        {
            UnivariatePolynomial temp = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) * matrix[2][2] +
                                        (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) * matrix[2][0] +
                                        (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) * matrix[2][1];
            res.push_back(make_pair(temp, make_pair(0.0, 1.0)));
            return res;
        }
        else if (n == 4)
        {
            auto &a = matrix[0], &b = matrix[1], &c = matrix[2], &d = matrix[3];
            UnivariatePolynomial temp = (a[0] * b[1] - a[1] * b[0]) * (c[2] * d[3] - c[3] * d[2]) - (a[0] * b[2] - a[2] * b[0]) * (c[1] * d[3] - c[3] * d[1]) + (a[0] * b[3] - a[3] * b[0]) * (c[1] * d[2] - c[2] * d[1]) + (a[1] * b[2] - a[2] * b[1]) * (c[0] * d[3] - c[3] * d[0]) - (a[1] * b[3] - a[3] * b[1]) * (c[0] * d[2] - c[2] * d[0]) + (a[2] * b[3] - a[3] * b[2]) * (c[0] * d[1] - c[1] * d[0]);
            res.push_back(make_pair(temp, make_pair(0.0, 1.0)));
            return res;
        }
        else if (n == 5)
        {
            auto &a = matrix[0], &b = matrix[1], &c = matrix[2], &d = matrix[3], &e = matrix[4];
            UnivariatePolynomial temp = (a[0] * b[1] - a[1] * b[0]) * (c[2] * (d[3] * e[4] - d[4] * e[3]) - c[3] * (d[2] * e[4] - d[4] * e[2]) + c[4] * (d[2] * e[3] - d[3] * e[2])) - (a[0] * b[2] - a[2] * b[0]) * (c[1] * (d[3] * e[4] - d[4] * e[3]) - c[3] * (d[1] * e[4] - d[4] * e[1]) + c[4] * (d[1] * e[3] - d[3] * e[1])) + (a[0] * b[3] - a[3] * b[0]) * (c[1] * (d[2] * e[4] - d[4] * e[2]) - c[2] * (d[1] * e[4] - d[4] * e[1]) + c[4] * (d[1] * e[2] - d[2] * e[1])) - (a[0] * b[4] - a[4] * b[0]) * (c[1] * (d[2] * e[3] - d[3] * e[2]) - c[2] * (d[1] * e[3] - d[3] * e[1]) + c[3] * (d[1] * e[2] - d[2] * e[1])) + (a[1] * b[2] - a[2] * b[1]) * (c[0] * (d[3] * e[4] - d[4] * e[3]) - c[3] * (d[0] * e[4] - d[4] * e[0]) + c[4] * (d[0] * e[3] - d[3] * e[0])) - (a[1] * b[3] - a[3] * b[1]) * (c[0] * (d[2] * e[4] - d[4] * e[2]) - c[2] * (d[0] * e[4] - d[4] * e[0]) + c[4] * (d[0] * e[2] - d[2] * e[0])) + (a[1] * b[4] - a[4] * b[1]) * (c[0] * (d[2] * e[3] - d[3] * e[2]) - c[2] * (d[0] * e[3] - d[3] * e[0]) + c[3] * (d[0] * e[2] - d[2] * e[0])) + (a[2] * b[3] - a[3] * b[2]) * (c[0] * (d[1] * e[4] - d[4] * e[1]) - c[1] * (d[0] * e[4] - d[4] * e[0]) + c[4] * (d[0] * e[1] - d[1] * e[0])) - (a[2] * b[4] - a[4] * b[2]) * (c[0] * (d[1] * e[3] - d[3] * e[1]) - c[1] * (d[0] * e[3] - d[3] * e[0]) + c[3] * (d[0] * e[1] - d[1] * e[0])) + (a[3] * b[4] - a[4] * b[3]) * (c[0] * (d[1] * e[2] - d[2] * e[1]) - c[1] * (d[0] * e[2] - d[2] * e[0]) + c[2] * (d[0] * e[1] - d[1] * e[0]));
            res.push_back(make_pair(temp, make_pair(0.0, 1.0)));
            return res;
        }

        UnivariatePolynomial det = UnivariatePolynomial({0});

        int sign = 1;

        // todo: check the code below
        for (size_t i = 0; i < n; ++i)
        {
            UnivariatePolynomial element = matrix[0][i];
            UnivariatePolynomialMatrix minor = getMinorMatrix(matrix, 0, i);
            UnivariatePolynomial minorDet = determinant(minor)[0].first;
            det = det + (element * sign * minorDet);
            sign = -sign;
        }

        res.push_back(make_pair(det, make_pair(0.0, 1.0)));
        return res;
    }

    typedef std::vector<std::vector<double>> Matrix;

    double determinantByGaussianElimination(const Matrix &mat)
    {
        //     auto time_begin = CHRONO_NOW;

        //     int rows = mat.size();
        //     int cols = mat[0].size();
        //     // Convert std::vector<std::vector<double>> to Eigen::MatrixXd
        //     Eigen::MatrixXd e(rows, cols);
        //     for (int i = 0; i < rows; ++i)
        //     {
        //         for (int j = 0; j < cols; ++j)
        //         {
        //             e(i, j) = mat[i][j];
        //         }
        //     }

        //     Eigen::LDLT<Eigen::MatrixXd> ldlt(e);
        //     auto time_1 = CHRONO_NOW;
        //     static double time_total = 0;
        //     static int count_total = 0;
        //     time_total += CHRONO_DIFF(time_1 - time_begin) * 1e-3;
        //     count_total += 1;

        //     // if (rand() % 10000 == 0) {
        //     //     std::cout << "ldlt time " << time_total / count_total << std::endl;
        //     // }
        //     if (ldlt.info() == Eigen::Success) {
        //         double x = ldlt.vectorD().prod();
        // #ifdef RESULTANT_WARN
        //         // if (abs(x) < 1e-233) {
        //         //     if (rand() % 10000 == 0) cout << "RESULTANT_WARN abs(det) < 1e-233" << endl;
        //         // }
        //         if (abs(x) > 1e+233) {
        //             cout << "RESULTANT_WARN abs(det) > 1e+233" << endl;
        //             return 1e233;
        //         }
        // #endif
        //         return x;
        //     }

        //    return std::pow(std::abs(x), 1) * y;

        int n = mat.size();
        double det = 1.0;

        Matrix A = mat;

        for (int i = 0; i < n; ++i)
        {
            int maxRow = i;
            for (int k = i + 1; k < n; ++k)
            {
                if (std::abs(A[k][i]) > std::abs(A[maxRow][i]))
                {
                    maxRow = k;
                }
            }

            if (A[maxRow][i] == 0.0)
                return 0.0;

            if (maxRow != i)
            {
                std::swap(A[i], A[maxRow]);
                det *= -1.0;
            }

            for (int k = i + 1; k < n; ++k)
            {
                double factor = A[k][i] / A[i][i];
                for (int j = i; j < n; ++j)
                {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }

        for (int i = 0; i < n; ++i)
        {
            double x = A[i][i] > 0 ? 1 : -1;
            double y = abs(A[i][i]);
            if (n > 6)
                for (int j = 0; j < 2; j++) // modify the const here
                    y = sqrt(y);
            det *= x * y;
        }

        return det;
    }

    std::vector<std::vector<double>> evaluateMatrixAtU(const UnivariatePolynomialMatrix &matrix, double x)
    {
        // assume a symmetric matrix
        // auto normalization
        auto time_begin = CHRONO_NOW;

        std::vector<std::vector<double>> result(matrix.size(), std::vector<double>(matrix[0].size(), 0.0));

        for (size_t i = 0; i < matrix.size(); ++i)
        {
            for (size_t j = 0; j < i; j++)
                result[i][j] = result[j][i];
            for (size_t j = i; j < matrix[i].size(); ++j)
                result[i][j] = matrix[i][j].evaluateAtU(x);
        }

        auto time_1 = CHRONO_NOW;
        static double time_total = 0;
        static int count_total = 0;
        time_total += CHRONO_DIFF(time_1 - time_begin) * 1e-3;
        count_total += 1;

        return result;
    }

    double evalMatrixPolynomialDeterminant(const UnivariatePolynomialMatrix &matrix, double u)
    {
        auto mat = evaluateMatrixAtU(matrix, u);
        return determinantByGaussianElimination(mat);
    }

    std::vector<double> expand_to_poly_coef(const std::vector<double> &x_values, int exc = -1)
    {
        int n = x_values.size();
        double coefficients[N_POLY];
        memset(coefficients, 0, sizeof(coefficients));
        auto x = x_values.data();

        coefficients[0] = 1.0;

        for (int i = 0; i < n; ++i)
        {
            if (i == exc)
            {
                continue;
            }
            double new_coefficients[N_POLY];
            memset(new_coefficients, 0, sizeof(new_coefficients));
            for (int j = 0; j <= i; ++j)
            {
                new_coefficients[j + 1] += coefficients[j];
                new_coefficients[j] -= x[i] * coefficients[j];
            }
            memcpy(coefficients, new_coefficients, sizeof(new_coefficients));
        }

        std::vector<double> ans(n);
        for (int i = 0; i < n; i++)
            ans[i] = coefficients[i];
        return ans;
    }

    std::vector<double> lagrange(const std::vector<double> &x, const std::vector<double> &y)
    {
        int n = x.size();
        std::vector<double> ans(n, 0.0);
        for (int i = 0; i < n; ++i)
        {
            double denom = 1.0;
            for (int j = 0; j < n; ++j)
            {
                if (i != j)
                {
                    denom *= (x[i] - x[j]);
                }
            }
            std::vector<double> numer = expand_to_poly_coef(x, i);
            double invdenom = 1.0 / denom;
            for (int k = 0; k < n; ++k)
            {
                ans[k] += numer[k] * invdenom * y[i];
            }
        }
        return ans;
    }

    std::vector<double> determinantLagrangeImpl(const UnivariatePolynomialMatrix &matrix, double valid_v_min, double valid_v_max)
    {
        int n = global_poly_cutoff + 1;
        std::vector<double> x(n);
        for (int i = 0; i < n; i++)
            // x[i] = 1.0 - std::pow(i * 1.0f / (n - 1), 2.0);
            if (valid_v_max > valid_v_min)
                x[i] = i * 1.0f / (n - 1) * (valid_v_max - valid_v_min) + valid_v_min;
            else
                x[i] = i * 1.0f / (n - 1);
        std::vector<double> y(n);
        for (int i = 0; i < n; i++)
            y[i] = evalMatrixPolynomialDeterminant(matrix, x[i]);
        return lagrange(x, y);
    }

    std::vector<pair<UnivariatePolynomial, pair<double, double>>> determinantLagrange(const UnivariatePolynomialMatrix &matrix, double valid_v_min, double valid_v_max)
    {
        std::vector<pair<UnivariatePolynomial, pair<double, double>>> res;
        res.push_back(make_pair(UnivariatePolynomial(determinantLagrangeImpl(matrix, valid_v_min, valid_v_max)), make_pair(0, 1)));
        return res;
    }

    std::vector<pair<UnivariatePolynomial, pair<double, double>>> cubicSplineInterpolator(const UnivariatePolynomialMatrix &matrix, double valid_v_min, double valid_v_max)
    {
        int n = global_poly_cutoff + 1;
        std::vector<double> x(n);
        for (int i = 0; i < n; i++)
            // x[i] = 1.0 - std::pow(i * 1.0f / (n - 1), 2.0);
            // x[i] = i * 1.0f / (n - 1);
            x[i] = i * 1.0f / (n - 1) * (valid_v_max - valid_v_min) + valid_v_min;
        std::vector<double> y(n);
        for (int i = 0; i < n; i++)
            y[i] = evalMatrixPolynomialDeterminant(matrix, x[i]);

        std::vector<double> a(n - 1);
        std::vector<double> b(n - 1);
        std::vector<double> c(n - 1);
        std::vector<double> d(n - 1);

        std::vector<pair<UnivariatePolynomial, pair<double, double>>> res;

        vector<double> h(n - 1);
        for (int i = 0; i < n - 1; ++i)
        {
            h[i] = x[i + 1] - x[i];
        }

        // Step 2: Calculate mu_i and lambda_i
        vector<double> mu(n - 1), lambda(n - 1);
        for (int i = 0; i < n - 1; ++i)
        {
            mu[i] = h[i] / (h[i] + h[i + 1]);
            lambda[i] = h[i + 1] / (h[i] + h[i + 1]);
        }

        // Step 3: Calculate delta
        vector<double> delta(n - 1);
        for (int i = 1; i < n - 1; ++i)
        {
            delta[i] = 6.0 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1]) / (h[i - 1] + h[i]);
        }

        // Step 4: Solve linear system for M
        vector<double> M(n, 0.0);
        M[0] = 6.0 / h[0] * ((y[1] - y[0]) / h[0] - y[0]);
        M[n - 1] = 6.0 / h[n - 2] * (y[n - 1] - (y[n - 1] - y[n - 2]) / h[n - 2]);
        for (int i = 1; i < n - 1; ++i)
        {
            double denom = 2.0 * (mu[i] + lambda[i]);
            M[i] = (delta[i] - lambda[i] * M[i - 1]) / denom;
        }

        // Step 5: Back-substitution
        for (int i = n - 2; i > 0; --i)
        {
            M[i] = M[i] - lambda[i] * M[i + 1];
        }

        // Step 6: Calculate coefficients for each interval
        for (int i = 0; i < n - 1; ++i)
        {
            a[i] = y[i];
            b[i] = (y[i + 1] - y[i]) / h[i] - h[i] * (2.0 * M[i] + M[i + 1]) / 6.0;
            c[i] = M[i] / 2.0;
            d[i] = (M[i + 1] - M[i]) / (6.0 * h[i]);
        }

        for (int i = 0; i < n - 1; i++)
        {
            std::vector<double> base = {-x[i], 1};
            UnivariatePolynomial basePoly(base);
            UnivariatePolynomial triPoly = UnivariatePolynomial(1, a[i]) + basePoly * b[i] + basePoly * basePoly * c[i] + basePoly * basePoly * basePoly * d[i];
            res.push_back(make_pair(triPoly, make_pair(x[i], x[i + 1])));
        }

        return res;
    }

}