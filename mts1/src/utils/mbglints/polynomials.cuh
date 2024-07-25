#include "cuda_common.cuh"

// // RR
const int N_DEGREE = 16;
const int N_POLY = 100;

// TT
// const int N_DEGREE = 54;
// const int N_POLY = 500;

// R
// const int N_DEGREE = 4;
// const int N_POLY = 9;

// T
// const int N_DEGREE = 6;
// const int N_POLY = 37;

__constant__ int max_iteration_dichotomy_cuda = 10;
__constant__ int global_poly_cutoff = N_POLY - 1;
const int global_mat_cutoff = 16;

const int N_MAT = N_DEGREE + 1;

// uni ploy mul
__device__ void upm(double *polyA, double *polyB, double *result, int n, int m)
{
    if (n <= 0 || m <= 0)
        return;
    for (int i = 0; i < n + m - 1; ++i)
    {
        result[i] = 0.0f;
        for (int j = 0; j <= i && j < n; ++j)
        {
            if (i - j >= m)
                continue;
            result[i] += polyA[j] * polyB[i - j];
        }
    }
}

__device__ void upms(double *polyA, double *polyB, double *result, int n, int m)
{
    if (n <= 0 || m <= 0)
        return;
    for (int i = 0; i < n + m - 1; ++i)
    {
        for (int j = 0; j <= i && j < n; ++j)
        {
            if (i - j >= m)
                continue;
            result[i] -= polyA[j] * polyB[i - j];
        }
    }
}

// uni ploy add
__device__ void upa(double *polyA, double *polyB, double *result, int n)
{
    if (n <= 0)
        return;
    for (int i = 0; i < n; ++i)
    {
        result[i] = polyA[i] + polyB[i];
    }
}

// uni ploy sub
__device__ void ups(double *polyA, double *polyB, double *result, int n)
{
    if (n <= 0)
        return;
    for (int i = 0; i < n; ++i)
    {
        result[i] = polyA[i] - polyB[i];
    }
}

// bi ploy add
__device__ void bpa(double *polyA, double *polyB, double *result, int n, int m, int r)
{
    for (int i = 0; i < (r + 1) * r / 2; ++i)
    {
        result[i] = 0.0;
    }
    int addr_lhs = 0;
    int addr_res_0 = 0;
    for (int i = 0; i < n; ++i)
    {
        int addr_res = addr_res_0;
        for (int j = 0; i + j < n; ++j)
        {
            result[addr_res + j] += polyA[addr_lhs + j];
        }
        addr_lhs += n - i;
        addr_res_0 += r - i;
    }
    addr_lhs = 0;
    addr_res_0 = 0;
    for (int i = 0; i < m; ++i)
    {
        int addr_res = addr_res_0;
        for (int j = 0; i + j < m; ++j)
        {
            result[addr_res + j] += polyB[addr_lhs + j];
        }
        addr_lhs += m - i;
        addr_res_0 += r - i;
    }
}

// bi ploy mul
__device__ void bpm(double *polyA, double *polyB, double *result, int n, int m, int r)
{
    for (int i = 0; i < (r + 1) * r / 2; ++i)
    {
        result[i] = 0.0;
    }
    int addr_lhs = 0;
    int addr_res_0 = 0;
    for (int i = 0; i < n; ++i)
    {
        int addr_rhs = 0;
        int addr_res = addr_res_0;
        for (int k = 0; k < m; ++k)
        {
            for (int j = 0; i + j < n; ++j)
            {
                for (int l = 0; k + l < m; ++l)
                {
                    result[addr_res + j + l] += polyA[addr_lhs + j] * polyB[addr_rhs + l];
                }
            }
            addr_rhs += m - k;
            addr_res += r - i - k;
        }
        addr_lhs += n - i;
        addr_res_0 += r - i;
    }
}

// bi ploy mul
__device__ void bpma(double *polyA, double *polyB, double *result, double f, int n, int m, int r)
{
    int addr_lhs = 0;
    int addr_res_0 = 0;
    for (int i = 0; i < n; ++i)
    {
        int addr_rhs = 0;
        int addr_res = addr_res_0;
        for (int k = 0; k < m; ++k)
        {
            for (int j = 0; i + j < n; ++j)
            {
                for (int l = 0; k + l < m; ++l)
                {
                    result[addr_res + j + l] += f * polyA[addr_lhs + j] * polyB[addr_rhs + l];
                }
            }
            addr_rhs += m - k;
            addr_res += r - i - k;
        }
        addr_lhs += n - i;
        addr_res_0 += r - i;
    }
}

__device__ double determinantByGaussianElimination(double *g, int _n)
{
    int det = 1.0;

    const int n = 15;

    float f[225];
    for (int i = 0; i < 225; i++)
        f[i] = g[i];

    for (int i = 0; i < 14; ++i)
    {
        int maxRow = i;
        for (int k = i + 1; k < 15; ++k)
        {
            float factor = f[k * 15 + i] / f[i * 15 + i];
            for (int j = i + 1; j < 15; ++j)
            {
                f[k * 15 + j] -= factor * f[i * 15 + j];
            }
        }
    }

    for (int i = 0; i < 15; ++i)
    {
        int x = f[i * 15 + i] > 0 ? 1 : -1;
        det *= x;
    }

    return det;
}

__device__ int bezout_addr(int i, int j)
{
    const int a[] = {0, 255, 472, 654, 804, 925, 1020, 1092, 1144, 1179, 1200, 1210, 1213, 1213, 1213, 1213};
    return a[i] + (N_BEZOUT_ITEM - i - i + N_BEZOUT_ITEM - i - j + 1) * (j - i) / 2;
}

__device__ double evalMatrixPolynomialDeterminantTex(cudaTextureObject_t tex, int n, int m, int ind, double x)
{
    double g[256];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
            g[i * n + j] = g[j * n + i];
        for (int j = i; j < n; ++j)
        {
            g[i * n + j] = 0.0;
            int addr = bezout_addr(i, j) + ind * N_BEZOUT_TOTAL;
            int len = N_BEZOUT_ITEM - i - j;
            for (int k = len - 1; k >= 0; --k)
            {
                int2 val = tex1Dfetch<int2>(tex, addr + k);
                double r = __hiloint2double(val.y, val.x);
                g[i * n + j] = g[i * n + j] * x + r;
            }
        }
    }

    return determinantByGaussianElimination(g, n);
}