#pragma once

#include "resultant_common.h"

namespace Resultant
{
    class UnivariatePolynomial
    {
    public:
        UnivariatePolynomial() = default;

        UnivariatePolynomial(const std::vector<double> &c) : size(c.size())
        {
            for (int i = 0; i < c.size(); i++)
                coeffs[i] = c[i];
        }

        explicit UnivariatePolynomial(int s) : size(s)
        {
            for (int i = 0; i < s; i++)
                coeffs[i] = 0;
        }

        UnivariatePolynomial(int s, double c) : size(s)
        {
            for (int i = 0; i < s; i++)
                coeffs[i] = c;
        }

        UnivariatePolynomial(int s, double *c) : size(s)
        {
            for (int i = 0; i < s; i++)
                coeffs[i] = c[i];
        }

        std::string toScientificNotationWithPrecision(double value,
                                                      int precision) const
        {
            std::ostringstream oss;
            oss << std::scientific << std::setprecision(precision) << value;
            return oss.str();
        }

        std::string toString() const
        {
            std::string result;
            for (size_t i = 0; i < size; ++i)
            {
                double coeff = coeffs[i];
                if (coeff != 0)
                {
                    result += toScientificNotationWithPrecision(coeff, 6);
                    if (i)
                        result += " v**" + std::to_string(i);
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
            size_t cols = size;

            std::cout << "Coefficients Matrix:" << std::endl;

            std::cout << "+";
            for (size_t j = 0; j < cols; ++j)
                std::cout << std::setw(12) << "+";
            std::cout << std::endl;

            std::cout << "|";
            for (size_t j = 0; j < cols; ++j)
                std::cout << std::setw(12) << coeffs[j];
            std::cout << "|" << std::endl;

            std::cout << "+";
            for (size_t j = 0; j < cols; ++j)
                std::cout << std::setw(12) << "+";
            std::cout << std::endl;
        }

        UnivariatePolynomial operator+(const UnivariatePolynomial &other) const
        {
            size_t max_cols = std::max(size, other.size);
            double padded_coeffs_this[N_POLY];
            double padded_coeffs_other[N_POLY];

            for (size_t j = 0; j < max_cols; ++j)
                padded_coeffs_this[j] = 0, padded_coeffs_other[j] = 0;
            for (size_t j = 0; j < size; ++j)
                padded_coeffs_this[j] = coeffs[j];
            for (size_t j = 0; j < other.size; ++j)
                padded_coeffs_other[j] = other.coeffs[j];
            UnivariatePolynomial sum(max_cols);
            for (size_t j = 0; j < max_cols; ++j)
                sum.coeffs[j] = padded_coeffs_this[j] + padded_coeffs_other[j];

            return sum;
        }

        UnivariatePolynomial operator*(const UnivariatePolynomial &other) const
        {
            size_t result_size = size + other.size - 1;
            UnivariatePolynomial result(result_size);

            for (size_t i = 0; i < size; ++i)
                for (size_t j = 0; j < other.size; ++j)
                {
                    if (i + j > global_poly_cutoff || i + j >= N_POLY)
                        break;
                    result.coeffs[i + j] += coeffs[i] * other.coeffs[j];
                    cnt++;
                }

            return result;
        }

        UnivariatePolynomial operator*(double other) const
        {
            UnivariatePolynomial sum(size);
            for (size_t j = 0; j < size; ++j)
                sum.coeffs[j] = coeffs[j] * other;
            return sum;
        }

        UnivariatePolynomial &operator*=(double other)
        {
            for (size_t j = 0; j < size; j++)
                coeffs[j] *= other;
            return *this;
        }

        UnivariatePolynomial operator-(const UnivariatePolynomial &other) const
        {
            return *this + (other * UnivariatePolynomial(1, -1));
        }

        void resize(size_t max_cols)
        {
            for (int i = size; i < max_cols; i++)
                coeffs[i] = 0;
            size = max_cols;
        }

        bool equalToZero()
        {
            for (int i = 0; i < size; i++)
            {
                if (coeffs[i] != 0)
                    return false;
            }
            return true;
        }

        double evaluateAtU(double x) const
        {
            double result = 0.0;
            for (int i = size - 1; i >= 0; --i)
                result = result * x + coeffs[i];
            return result;
        }

        std::vector<double> getCoeffs() const
        {
            std::vector<double> v(size);
            for (int i = 0; i < size; i++)
                v[i] = coeffs[i];
            return v;
        }

        void normalize()
        {
            double mc = 1e-99;
            for (int i = -2 + size; i >= 1; i--)
                mc = std::max(mc, coeffs[i]);
            for (int i = -2 + size; i >= 0; i--)
                coeffs[i] /= mc;
        }

    public:
        int size = 0; // size means the length = degree + 1
        double coeffs[N_POLY] = {};
    };

    typedef std::vector<std::vector<UnivariatePolynomial>>
        UnivariatePolynomialMatrix;

    void printUnivariatePolynomial(const UnivariatePolynomial &poly)
    {
        std::cout << poly.toString() << std::endl;
    }

    void printUnivariatePolynomialMatrix(const UnivariatePolynomialMatrix &matrix)
    {
        for (const auto &row : matrix)
            for (const UnivariatePolynomial &poly : row)
                printUnivariatePolynomial(poly);
        std::cout << std::endl;
    }

} // namespace Resultant