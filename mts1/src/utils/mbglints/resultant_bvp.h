#pragma once

#include "resultant_common.h"
#include "resultant_uvp.h"

namespace Resultant
{
    class BivariatePolynomial
    {
    public:
        BivariatePolynomial(const std::vector<std::vector<double>> &c) : size(c.size()) // what if size of columns bigger than size of rows
        {
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    coeffs[i][j] = c[i][j];
        }

        explicit BivariatePolynomial(int sz) : size(sz)
        {
        }

        BivariatePolynomial(int sz, double f) : size(sz)
        {
            coeffs[0][0] = f;
        }

        BivariatePolynomial() : size(0)
        {
        }

        std::string toScientificNotationWithPrecision(double value, int precision) const
        {
            std::ostringstream oss;
            oss << std::scientific << std::setprecision(precision) << value;
            return oss.str();
        }

        std::string toString() const
        {
            std::string result;
            for (size_t i = 0; i < size; ++i)
                for (size_t j = 0; j < size; ++j)
                {
                    double coeff = coeffs[i][j];
                    if (coeff != 0)
                    {
                        result += toScientificNotationWithPrecision(coeff, 8);
                        if (i)
                            result += "*u**" + std::to_string(i);
                        if (j)
                            result += "*v**" + std::to_string(j);
                        result += " + ";
                    }
                }
            if (!result.empty())
            {
                result.pop_back();
                result.pop_back();
                result.pop_back();
            }
            return result;
        }

        void printCoefficientsMatrix() const
        {
            size_t rows = size;
            size_t cols = size;

            std::cout << "Coefficients Matrix:" << std::endl;

            std::cout << "+";
            for (size_t j = 0; j < cols; ++j)
                std::cout << std::setw(12) << "+";
            std::cout << std::endl;

            for (size_t i = 0; i < rows; ++i)
            {
                std::cout << "|";
                for (size_t j = 0; j < cols; ++j)
                    std::cout << std::setw(12) << coeffs[i][j];
                std::cout << "|" << std::endl;
            }

            std::cout << "+";
            for (size_t j = 0; j < cols; ++j)
                std::cout << std::setw(12) << "+";
            std::cout << std::endl;
        }

        BivariatePolynomial operator+(const BivariatePolynomial &other) const
        {
            BivariatePolynomial sum(std::max(size, other.size));
            for (size_t i = 0; i < sum.size; ++i)
                for (size_t j = 0; j < sum.size; ++j)
                    sum.coeffs[i][j] = coeffs[i][j] + other.coeffs[i][j];
            return sum;
        }

        BivariatePolynomial operator*(const BivariatePolynomial &other) const
        {
            // ! we assume it is an upper triangle
            BivariatePolynomial result(std::min(global_mat_cutoff, size + other.size - 1));
            for (size_t i = 0; i < size; ++i)
            {
                for (size_t k = 0; k < other.size && i + k < global_mat_cutoff; ++k)
                {
                    for (size_t j = 0; i + j < size; ++j)
                    {
                        for (size_t l = 0; k + l < other.size && j + l < global_mat_cutoff; ++l)
                        {
                            result.coeffs[i + k][j + l] += coeffs[i][j] * other.coeffs[k][l];
                        }
                    }
                }
            }
            return result;
        }

        BivariatePolynomial scalarMul(double other) const
        {
            BivariatePolynomial result(std::max(size, 1));
            for (size_t i = 0; i < size; ++i)
                for (size_t j = 0; j < size; ++j)
                    result.coeffs[i][j] = coeffs[i][j] * other;
            return result;
        }

        // todo: optimize
        BivariatePolynomial operator-(const BivariatePolynomial &other) const
        {
            return *this + (other.scalarMul(-1));
        }

        BivariatePolynomial operator-(double other) const
        {
            return *this + (BivariatePolynomial(1, other).scalarMul(-1));
        }

        void resize(size_t max_rows, size_t max_cols)
        {
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    if (i >= max_rows || j >= max_rows)
                        coeffs[i][j] = 0;
            size = max_rows;
        }

        UnivariatePolynomial evaluateAtU(double value) const
        {
            std::vector<double> univariate_coeffs(size, 0);
            double pw = 1; // = value^i
            for (size_t i = 0; i < size; ++i)
            {
                for (size_t j = 0; j < size; ++j)
                    univariate_coeffs[j] += coeffs[i][j] * pw;
                pw *= value;
            }
            return UnivariatePolynomial(univariate_coeffs);
        }

        UnivariatePolynomial evaluateAtV(double value) const
        {
            std::vector<double> univariate_coeffs(size, 0);
            for (size_t i = 0; i < size; ++i)
            {
                double pw = 1;
                for (size_t j = 0; j < size; ++j)
                {
                    univariate_coeffs[i] += coeffs[i][j] * pw;
                    pw *= value;
                }
            }
            return UnivariatePolynomial(univariate_coeffs);
        }

        std::vector<UnivariatePolynomial> toUnivariatePolynomials() const
        {
            // u is eliminated
            // ! assume it is an upper triangle
            std::vector<UnivariatePolynomial> univariatePolys;
            int n = size;
            for (int i = 0; i < n; ++i)
            {
                std::vector<double> coefficients(n - i);
                for (int j = 0; j < n - i; ++j)
                    coefficients[j] = coeffs[i][j];
                univariatePolys.push_back(UnivariatePolynomial(coefficients));
            }
            return univariatePolys;
        }

        double findMax()
        {
            double maxVal = coeffs[0][0];
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    if (coeffs[i][j] > maxVal)
                    {
                        maxVal = coeffs[i][j];
                    }
                }
            }
            return maxVal;
        }

        void divideByMax()
        {
            double maxVal = findMax() * 1e-6;
            if (maxVal != 0)
            {
                for (int i = 0; i < size; ++i)
                {
                    for (int j = 0; j < size; ++j)
                    {
                        coeffs[i][j] /= maxVal;
                    }
                }
            }
        }

    public:
        double coeffs[N_MAT + 1][N_MAT + 1] = {};
        int size; // size = length = maxdeg + 1
    };

    struct BVP3
    {
        BivariatePolynomial bvp[3];

        BVP3(const BivariatePolynomial &x, const BivariatePolynomial &y, const BivariatePolynomial &z) : bvp{x, y, z}
        {
        }

        BVP3 operator+(const BVP3 &rhs) const
        {
            return {bvp[0] + rhs.bvp[0], bvp[1] + rhs.bvp[1], bvp[2] + rhs.bvp[2]};
        }

        BVP3 operator-(const BVP3 &rhs) const
        {
            return {bvp[0] - rhs.bvp[0], bvp[1] - rhs.bvp[1], bvp[2] - rhs.bvp[2]};
        }

        BVP3 operator*(const BVP3 &rhs) const
        { // element-wise product
            return {bvp[0] * rhs.bvp[0], bvp[1] * rhs.bvp[1], bvp[2] * rhs.bvp[2]};
        }

        BVP3 operator+(const BivariatePolynomial &rhs) const
        {
            return {bvp[0] + rhs, bvp[1] + rhs, bvp[2] + rhs};
        }

        BVP3 operator-(const BivariatePolynomial &rhs) const
        {
            return {bvp[0] - rhs, bvp[1] - rhs, bvp[2] - rhs};
        }

        BVP3 operator*(const BivariatePolynomial &rhs) const
        {
            return {bvp[0] * rhs, bvp[1] * rhs, bvp[2] * rhs};
        }

        BivariatePolynomial dot(const BVP3 &rhs) const
        { // dot product
            return bvp[0] * rhs.bvp[0] + bvp[1] * rhs.bvp[1] + bvp[2] * rhs.bvp[2];
        }

        BVP3 cross(const BVP3 &rhs) const
        { // cross product
            return {bvp[1] * rhs.bvp[2] - bvp[2] * rhs.bvp[1], bvp[2] * rhs.bvp[0] - bvp[0] * rhs.bvp[2], bvp[0] * rhs.bvp[1] - bvp[1] * rhs.bvp[0]};
        }
    };

}