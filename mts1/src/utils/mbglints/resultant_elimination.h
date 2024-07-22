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
#include "resultant_qz.h"
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
// #include <Python.h>
// #include <numpy/arrayobject.h>
#include "cyPolynomial.h"
#pragma comment(linker, "/STACK:999999999") // avoid stack overflow
using namespace Eigen;

namespace Resultant
{
	template <bool use_unit_root = false>
	inline std::pair<std::vector<std::pair<UnivariatePolynomial, std::pair<double, double>>>, UnivariatePolynomialMatrix> resultant_elimination(const BivariatePolynomial &poly1, const BivariatePolynomial &poly2, int cutoff_matrix, int cutoff_resultant, double valid_v_min, double valid_v_max)
	{
		auto ___time_begin = CHRONO_NOW;

		auto poly2_ = poly1 * BivariatePolynomial(1, 0) + poly2; // d(poly1) >= d(poly2)

		std::vector<UnivariatePolynomial> poly1Mat = poly1.toUnivariatePolynomials();
		std::vector<UnivariatePolynomial> poly2Mat = poly2_.toUnivariatePolynomials();

		UnivariatePolynomialMatrix bezoutMat = bezout_matrix(poly1Mat, poly2Mat);

		std::pair<std::vector<pair<UnivariatePolynomial, pair<double, double>>>, UnivariatePolynomialMatrix> res;
		res.second = bezoutMat;
		// print values of bezout matrix (only when log is enabled)
		if (global_method_mask & METHODMASK_SPLINE_GAUSSIAN_WITH_LOG || global_method_mask & METHODMASK_DICHOTOMY_GAUSSIAN_WITH_LOG)
		{
			int num_samples = 1001;
			std::vector<double> x(num_samples, 0);
			std::vector<double> y(num_samples, 0);
			y[0] = evalMatrixPolynomialDeterminant(bezoutMat, 0);
			int signal = (y[0] > 0) ? 1 : (y[0] < 0 ? -1 : 0);
			bool has_roots = false;
			for (int i = 1; i < num_samples; i++)
			{
				x[i] = static_cast<double>(i) / (num_samples - 1);
				y[i] = evalMatrixPolynomialDeterminant(bezoutMat, x[i]);
				if (signal * y[i] <= 0)
					has_roots = true;
			}
			if (has_roots)
			{
				for (int i = 0; i < num_samples; i++)
				{
					ss << x[i] << " " << y[i] << " ";
				}
			}
		}

		auto ___time_end = CHRONO_NOW;
		___perf_time_bezout += CHRONO_DIFF(___time_end - ___time_begin) * 1e-3;
		___time_begin = ___time_end;

		auto det = (global_method_mask & METHODMASK_LAGRANGE_GAUSSIAN) ? determinantLagrange(bezoutMat, valid_v_min, valid_v_max) : (global_method_mask & METHODMASK_DICHOTOMY_GAUSSIAN || (global_method_mask & METHODMASK_DICHOTOMY_GAUSSIAN_WITH_LOG)) ? std::vector<std::pair<UnivariatePolynomial, std::pair<double, double>>>()
																																: ((global_method_mask & METHODMASK_SPLINE_GAUSSIAN) || (global_method_mask & METHODMASK_SPLINE_GAUSSIAN_WITH_LOG))		  ? cubicSplineInterpolator(bezoutMat, valid_v_min, valid_v_max)
																																																														  : determinant(bezoutMat);
		// det.resize(cutoff_resultant + 1);
		// det.normalize();
		res.first = det;

		___time_end = CHRONO_NOW;
		___perf_time_determinant += CHRONO_DIFF(___time_end - ___time_begin) * 1e-3;
		___time_begin = ___time_end;

		return res;
	}

#ifdef QZ_SOLVER
	template <bool use_unit_root = false>
	inline std::vector<double> resultant_elimination_qz(const BivariatePolynomial &poly1, const BivariatePolynomial &poly2, int cutoff_matrix, int cutoff_resultant)
	{
		std::vector<double> result_u;
		auto ___time_begin = CHRONO_NOW;

		std::vector<UnivariatePolynomial> poly1Mat = poly1.toUnivariatePolynomials();
		std::vector<UnivariatePolynomial> poly2Mat = poly2.toUnivariatePolynomials();

		UnivariatePolynomialMatrix bezoutMat = bezout_matrix(poly1Mat, poly2Mat);

		auto ___time_end = CHRONO_NOW;
		___perf_time_bezout += CHRONO_DIFF(___time_end - ___time_begin) * 1e-3;
		___time_begin = ___time_end;

		result_u = eigen_solver.eval_eigen(bezoutMat);
		___time_end = CHRONO_NOW;
		___perf_time_bezout += CHRONO_DIFF(___time_end - ___time_begin) * 1e-3;
		___time_begin = ___time_end;
		return result_u;
	}
#endif

	std::vector<std::tuple<double, double, double, double>> solve_equ(const std::vector<pair<UnivariatePolynomial, pair<double, double>>> &poly_vec_u, const UnivariatePolynomialMatrix &bezout_matrix, BivariatePolynomial &Cxz,
																	  const BivariatePolynomial &u2hat, const BivariatePolynomial &v2hat, const BivariatePolynomial &kappa2, int chain_type, double valid_v_min, double valid_v_max)
	{
		perf_count++;

		// printUnivariatePolynomialMatrix(bezout_matrix);

		auto ___time_begin = CHRONO_NOW;
		auto ___time_end = ___time_begin;

		// Solver begin
		double roots[N_POLY - 1], roots2[N_POLY - 1];
		int numRoots = 0;
		double doubleervalMin = 0;
		double doubleervalMax = 1;
		double errorThreshold = 1e-8;
		double x_tolerance = 0;
		if (global_method_mask & METHODMASK_DICHOTOMY_GAUSSIAN || global_method_mask & METHODMASK_DICHOTOMY_GAUSSIAN_WITH_LOG)
		{
			int n = global_poly_cutoff + 1;

			int max_iteration = max_iteration_dichotomy;
			std::vector<double> x(n);
			std::vector<double> y(n);

			int idx = 0;

			std::vector<int> logOfBisection(n - 1, 0);
			std::vector<double> logOfBisection_sol(n - 1, 0);
			std::vector<double> logOfBisection_solval(n - 1, 0);

			for (int i = 0; i < n; i++)
			{
				x[i] = i * 1.0f / (n - 1);
				y[i] = evalMatrixPolynomialDeterminant(bezout_matrix, x[i]);
				if (y[i] == 0.0)
				{
					roots[idx++] = x[i];
					numRoots++;
				}
				if (i > 0 && y[i] * y[i - 1] <= 0.0 && y[i - 1] != 0.0 && y[i] != 0.0)
				{
					logOfBisection[i - 1] = 1;
					double lb = x[i - 1], rb = x[i];
					double mid_value = 0;
					double mid = 0;
					for (int k = 1; k <= max_iteration; k++)
					{
						mid = (lb + rb) / 2;
						mid_value = evalMatrixPolynomialDeterminant(bezout_matrix, mid);
						if (mid_value * y[i] < 0.0)
						{
							lb = mid;
						}
						else
						{
							rb = mid;
						}
					}
					roots[idx++] = mid;
					logOfBisection_sol[i - 1] = mid;
					logOfBisection_solval[i - 1] = mid_value;
					numRoots++;
				}
			}

			if (global_method_mask & METHODMASK_DICHOTOMY_GAUSSIAN_WITH_LOG && !ss.str().empty())
			{
				ofstream ofs_resultant;
				if (isFirstCall)
				{
					ofs_resultant.open("resultant_info.txt", std::ios::trunc);
					isFirstCall = false;
				}
				else
				{
					ofs_resultant.open("resultant_info.txt", std::ios::app);
				}
				if (ofs_resultant.is_open())
				{
					ofs_resultant << ss.str() << std::endl;
					ofs_resultant << n - 1 << std::endl;
					for (int i = 0; i < n - 1; i++)
					{
						ofs_resultant << logOfBisection[i] << " " << logOfBisection_sol[i] << " " << logOfBisection_solval[i] << endl;
					}
					ofs_resultant.close();
				}
			}
		}
		else
		{ // other method

			UnivariatePolynomial poly_u = poly_vec_u[0].first;

			int maxdeg = 1;
			double maxcoef = 0;
			for (int i = 1; i < N_POLY; i++)
			{
				if (abs(poly_u.coeffs[i]) > maxcoef)
				{
					maxcoef = abs(poly_u.coeffs[i]);
				}
			}
			for (int i = 1; i < N_POLY; i++)
			{
				if (abs(poly_u.coeffs[i]) > maxcoef * 1e-9)
				{
					maxdeg = i;
				}
			}

			if (maxdeg <= 2)
			{
				const int const_deg = 2; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly;
				for (int i = 0; i <= const_deg; i++)
				{
					poly.coef[i] = poly_u.coeffs[i];
				}
				numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
			}
			else if (maxdeg <= 3)
			{
				const int const_deg = 3; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly;
				for (int i = 0; i <= const_deg; i++)
				{
					poly.coef[i] = poly_u.coeffs[i];
				}
				numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
			}
			else if (maxdeg <= 4)
			{
				const int const_deg = 4; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly;
				for (int i = 0; i <= const_deg; i++)
				{
					poly.coef[i] = poly_u.coeffs[i];
				}
				numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
			}
			else if (maxdeg <= 5)
			{
				const int const_deg = 5; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly;
				for (int i = 0; i <= const_deg; i++)
				{
					poly.coef[i] = poly_u.coeffs[i];
				}
				numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
			}
			else if (maxdeg <= 6)
			{
				const int const_deg = 6; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly;
				for (int i = 0; i <= const_deg; i++)
				{
					poly.coef[i] = poly_u.coeffs[i];
				}
				numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
			} // todo: more
			else if (maxdeg <= 7)
			{
				const int const_deg = 7; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly;
				for (int i = 0; i <= const_deg; i++)
				{
					poly.coef[i] = poly_u.coeffs[i];
				}
				numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
			} // todo: more
			else if (maxdeg <= 8)
			{
				const int const_deg = 8; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly;
				for (int i = 0; i <= const_deg; i++)
				{
					poly.coef[i] = poly_u.coeffs[i];
				}
				numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
			} // todo: more
			else
			{
				const int const_deg = N_POLY - 1; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly;
				for (int i = 0; i <= const_deg; i++)
				{
					poly.coef[i] = poly_u.coeffs[i];
				}
				numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
			}
			__perf_total_1d_sols += numRoots;
		}

		___time_end = CHRONO_NOW;
		___perf_time_solver1 += CHRONO_DIFF(___time_end - ___time_begin) * 1e-3;
		___time_begin = ___time_end;

		std::vector<std::tuple<double, double, double, double>> solutions;
		// solve back
		for (int i = 0; i < numRoots; i++)
		{
			double gamma = roots[i];
			auto unipoly = Cxz.evaluateAtV(gamma);

			int numRoots2 = 0;

			{									// todo: add some if-else above
				const int const_deg = N_DEGREE; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly2;
				for (int k = 0; k <= const_deg; k++)
					poly2.coef[k] = unipoly.coeffs[k];
				numRoots2 = poly2.Roots(roots2, doubleervalMin, doubleervalMax, errorThreshold);
			}

			for (int j = 0; j < numRoots2; j++)
			{
				double beta = roots2[j];
				if (beta < -x_tolerance || beta > 1 + x_tolerance || beta + gamma > 1 + x_tolerance)
					continue;
				double alpha = 1.0 - beta - gamma;

				if (chain_type < 10)
				{
					solutions.push_back({alpha, beta, 0.333, 0.333});
					continue;
				}

				double u2hat_val = u2hat.evaluateAtV(gamma).evaluateAtU(beta);
				double v2hat_val = v2hat.evaluateAtV(gamma).evaluateAtU(beta);
				double kappa2_val = kappa2.evaluateAtV(gamma).evaluateAtU(beta);

				double beta2 = u2hat_val / kappa2_val;
				double gamma2 = v2hat_val / kappa2_val;
				if (chain_type < 10)
				{
					beta2 = 0.333;
					gamma2 = 0.333;
				}
				double alpha2 = 1 - beta2 - gamma2;

				if (chain_type > 10)
					if (alpha2 < 0 || beta2 < 0 || gamma2 < 0)
					{
						continue;
					}
				solutions.push_back({alpha, beta, alpha2, beta2});
			}
		}

		___time_end = CHRONO_NOW;
		___perf_time_solver2 += CHRONO_DIFF(___time_end - ___time_begin) * 1e-3;

		return solutions;
	}

	std::vector<std::tuple<double, double, double, double>> solve_equ(const UnivariatePolynomial &poly_vec_u, BivariatePolynomial &Cxz, int chain_type)
	{
		perf_count++;

		// printUnivariatePolynomialMatrix(bezout_matrix);

		auto ___time_begin = CHRONO_NOW;
		auto ___time_end = ___time_begin;

		// Solver begin
		double roots[N_POLY - 1], roots2[N_POLY - 1];
		int numRoots = 0;
		double doubleervalMin = 0;
		double doubleervalMax = 1;
		double errorThreshold = 1e-8;
		double x_tolerance = 0;

		double valid_v_min = 0;
		double valid_v_max = 1;

		const UnivariatePolynomial &poly_u = poly_vec_u;

		int maxdeg = 1;
		double maxcoef = 0;
		for (int i = 1; i < N_POLY; i++)
		{
			if (abs(poly_u.coeffs[i]) > maxcoef)
			{
				maxcoef = abs(poly_u.coeffs[i]);
			}
		}
		for (int i = 1; i < N_POLY; i++)
		{
			if (abs(poly_u.coeffs[i]) > maxcoef * 1e-9)
			{
				maxdeg = i;
			}
		}

		if (maxdeg <= 2)
		{
			const int const_deg = 2; // ! N of cy::Polynomial is degree (= length - 1)
			cy::Polynomial<double, const_deg> poly;
			for (int i = 0; i <= const_deg; i++)
			{
				poly.coef[i] = poly_u.coeffs[i];
			}
			numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
		}
		else if (maxdeg <= 3)
		{
			const int const_deg = 3; // ! N of cy::Polynomial is degree (= length - 1)
			cy::Polynomial<double, const_deg> poly;
			for (int i = 0; i <= const_deg; i++)
			{
				poly.coef[i] = poly_u.coeffs[i];
			}
			numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
		}
		else if (maxdeg <= 4)
		{
			const int const_deg = 4; // ! N of cy::Polynomial is degree (= length - 1)
			cy::Polynomial<double, const_deg> poly;
			for (int i = 0; i <= const_deg; i++)
			{
				poly.coef[i] = poly_u.coeffs[i];
			}
			numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
		}
		else if (maxdeg <= 5)
		{
			const int const_deg = 5; // ! N of cy::Polynomial is degree (= length - 1)
			cy::Polynomial<double, const_deg> poly;
			for (int i = 0; i <= const_deg; i++)
			{
				poly.coef[i] = poly_u.coeffs[i];
			}
			numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
		}
		else if (maxdeg <= 6)
		{
			const int const_deg = 6; // ! N of cy::Polynomial is degree (= length - 1)
			cy::Polynomial<double, const_deg> poly;
			for (int i = 0; i <= const_deg; i++)
			{
				poly.coef[i] = poly_u.coeffs[i];
			}
			numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
		} // todo: more
		else if (maxdeg <= 7)
		{
			const int const_deg = 7; // ! N of cy::Polynomial is degree (= length - 1)
			cy::Polynomial<double, const_deg> poly;
			for (int i = 0; i <= const_deg; i++)
			{
				poly.coef[i] = poly_u.coeffs[i];
			}
			numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
		} // todo: more
		else if (maxdeg <= 8)
		{
			const int const_deg = 8; // ! N of cy::Polynomial is degree (= length - 1)
			cy::Polynomial<double, const_deg> poly;
			for (int i = 0; i <= const_deg; i++)
			{
				poly.coef[i] = poly_u.coeffs[i];
			}
			numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
		} // todo: more
		else
		{
			const int const_deg = N_POLY - 1; // ! N of cy::Polynomial is degree (= length - 1)
			cy::Polynomial<double, const_deg> poly;
			for (int i = 0; i <= const_deg; i++)
			{
				poly.coef[i] = poly_u.coeffs[i];
			}
			numRoots = poly.Roots(roots, valid_v_min, valid_v_max, errorThreshold);
		}
		__perf_total_1d_sols += numRoots;

		___time_end = CHRONO_NOW;
		___perf_time_solver1 += CHRONO_DIFF(___time_end - ___time_begin) * 1e-3;
		___time_begin = ___time_end;

		std::vector<std::tuple<double, double, double, double>> solutions;
		// solve back
		for (int i = 0; i < numRoots; i++)
		{
			double gamma = roots[i];
			auto unipoly = Cxz.evaluateAtV(gamma);

			int numRoots2 = 0;

			{									// todo: add some if-else above
				const int const_deg = N_DEGREE; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly2;
				for (int k = 0; k <= const_deg; k++)
					poly2.coef[k] = unipoly.coeffs[k];
				numRoots2 = poly2.Roots(roots2, 0, 1 - gamma, errorThreshold);
			}

			for (int j = 0; j < numRoots2; j++)
			{
				double beta = roots2[j];
				if (beta < -x_tolerance || beta > 1 + x_tolerance || beta + gamma > 1 + x_tolerance)
					continue;
				double alpha = 1.0 - beta - gamma;

				solutions.push_back({alpha, beta, 0.333, 0.333});
			}
		}
		___time_end = CHRONO_NOW;
		___perf_time_solver2 += CHRONO_DIFF(___time_end - ___time_begin) * 1e-3;

		return solutions;
	}

#ifdef QZ_SOLVER
	std::vector<std::tuple<double, double, double, double>> solve_equ_qz(std::vector<double> result_u, const BivariatePolynomial &Cxz,
																		 const BivariatePolynomial &u2hat, const BivariatePolynomial &v2hat, const BivariatePolynomial &kappa2, int chain_type)
	{
		auto ___time_begin = CHRONO_NOW;
		auto ___time_end = ___time_begin;
		int numRoots = result_u.size();
		double result_v[N_POLY];
		double doubleervalMin = 0;
		double doubleervalMax = 1;
		double errorThreshold = 1e-9;

		std::vector<std::tuple<double, double, double, double>> solutions;

		for (int i = 0; i < numRoots; i++)
		{
			double gamma = result_u[i];
			if (gamma < 0)
				gamma = 0;
			if (gamma > 1)
				gamma = 1;
			auto unipoly = Cxz.evaluateAtV(gamma);

			int maxdeg = 1;
			double maxcoef = 0;
			for (int i = 1; i < unipoly.size; i++)
				if (abs(unipoly.coeffs[i]) > maxcoef)
					maxcoef = abs(unipoly.coeffs[i]);
			for (int i = 1; i < unipoly.size; i++)
				if (abs(unipoly.coeffs[i]) > maxcoef * global_poly_cutoff_eps)
					maxdeg = i;
			int numRoots2 = 0;

			{									// todo: add some if-else above
				const int const_deg = N_DEGREE; // ! N of cy::Polynomial is degree (= length - 1)
				cy::Polynomial<double, const_deg> poly2;
				for (int k = 0; k <= const_deg; k++)
					poly2.coef[k] = unipoly.coeffs[k];
				numRoots2 = poly2.Roots(result_v, doubleervalMin, doubleervalMax, errorThreshold);
			}

			for (int j = 0; j < numRoots2; j++)
			{
				double beta = result_v[j];
				if (beta < 0)
					beta = 0;
				if (beta > 1)
					beta = 1;
				if (beta > 1 - gamma)
					beta = 1 - gamma;
				if (beta + gamma <= 1.0)
				{
					double alpha = 1.0 - beta - gamma;

					double u2hat_val = u2hat.evaluateAtV(gamma).evaluateAtU(beta);
					double v2hat_val = v2hat.evaluateAtV(gamma).evaluateAtU(beta);
					double kappa2_val = kappa2.evaluateAtV(gamma).evaluateAtU(beta);

					double beta2 = u2hat_val / kappa2_val;
					double gamma2 = v2hat_val / kappa2_val;
					if (chain_type < 10)
					{
						beta2 = 0.333;
						gamma2 = 0.333;
					}
					double alpha2 = 1 - beta2 - gamma2;

					if (chain_type > 10)
						if (alpha2 < 0 || beta2 < 0 || gamma2 < 0)
						{
							continue;
						}

					solutions.push_back({alpha, beta, alpha2, beta2});
				}
			}
		}

		___time_end = CHRONO_NOW;
		___perf_time_solver2 += CHRONO_DIFF(___time_end - ___time_begin) * 1e-3;

		return solutions;
	}
#endif

}