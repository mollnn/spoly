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
#include "resultant_det.h"
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
using namespace Eigen;

namespace Resultant
{

#define QZ_SOLVER

#ifdef QZ_SOLVER
    class GeneralizeEigenSolver
    {
    public:
        GeneralizeEigenSolver()
        {
        }

        ~GeneralizeEigenSolver()
        {
        }

        std::vector<double> eval_eigen(const UnivariatePolynomialMatrix &bezoutMat)
        {
            const int N = bezoutMat[0].size();
            const int Mmax = bezoutMat[0][0].size;
            // int M = 0;
            // for (int i = 0; i < Mmax; i ++) {
            //   if (bezoutMat[0][0].coeffs[i] != 0) {
            //     M = i;
            //   }
            // }
            // std::cout << N << " " << M << std::endl;
            const int M = N;

            MatrixXd matA = MatrixXd::Zero(N * M, N * M);
            MatrixXd matB = MatrixXd::Zero(N * M, N * M);
            for (int i = 0; i < (M - 1) * N; i++)
            {
                matB(i, i) = 1.f;
            }
            for (int i = (M - 1) * N; i < M * N; i++)
            {
                for (int j = (M - 1) * N; j < M * N; j++)
                {
                    matB(i, j) = bezoutMat[i - (M - 1) * N][j - (M - 1) * N].coeffs[M];
                }
            }
            for (int i = 0; i < M; i++)
            {
                auto rowStart = i * N;
                auto coeffColStart = (M - 1) * N;
                auto identColStart = (i - 1) * N;
                for (int j = rowStart; j < rowStart + N; j++)
                {
                    for (int k = coeffColStart; k < coeffColStart + N; k++)
                    {
                        matA(j, k) = -bezoutMat[j - rowStart][k - coeffColStart].coeffs[i];
                    }
                }
            }
            for (int i = 0; i < N; i++)
            {
                auto rowStart = i * N;
                auto identColStart = (i - 1) * N;
                for (int k = identColStart; k >= 0 && k < identColStart + N; k++, rowStart++)
                {
                    matA(rowStart, k) = 1.f;
                }
            }

            if (resultant_cnt == 100)
            {
                ofstream out("matrix_temp.txt");
                out << matA << endl
                    << endl;
                out << matB << endl
                    << endl;
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        out << bezoutMat[i][j].toString();
                        out << endl;
                    }
                    out << endl;
                }
            }

            std::vector<double> result_u;
            RealQZ<MatrixXd> qz;
            qz.setMaxIterations(100);
            qz.compute(matA, matB);
            auto matS = qz.matrixS(), matT = qz.matrixT();
            for (int i = 0; i < N * M; i++)
            {
                if (matT(i, i) != 0)
                {
                    auto r = matS(i, i) / matT(i, i);
                    if (r >= 0.0 && r <= 1.0)
                        result_u.push_back(r);
                }
            }
            resultant_cnt++;
#endif
            return result_u;
        }

        int resultant_cnt = 1;

    private:
    };
    GeneralizeEigenSolver eigen_solver;

    int cnt_SPEC = 1;

}