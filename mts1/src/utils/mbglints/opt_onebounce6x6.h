#include <immintrin.h>
#include <iostream>

namespace opt_onebounce_6x6
{

    template <int l1, int l2, int l3, int r1, int r2, int r3>
    void det3_mul_det3_add_on(const __m256d matrix[6][6][8], __m256d *res_poly)
    {
        // No general implementation
        printf("No general implementation\n");
    }

    inline void init_256d(int n, __m256d *array)
    {
        for (int i = 0; i < n; ++i)
            array[i] = _mm256_setzero_pd();
    }

    template <>
    inline void
    det3_mul_det3_add_on<0, 1, 5, 2, 3, 4>(const __m256d matrix[6][6][8],
                                           __m256d *res_poly)
    {
        __m256d det_l[13];
        init_256d(13, det_l);
        {
            {
                __m256d n_2_temp[8];
                init_256d(8, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][1][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][5], matrix[1][5][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][6], matrix[1][5][0]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][6], matrix[1][5][1]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][4]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][5]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][4]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][5]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][4]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][5]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][0][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][0][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][0], n_2_temp[7]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][0][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][1], n_2_temp[6]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][1], n_2_temp[7]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][2], n_2_temp[5]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][2], n_2_temp[6]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][0][2], n_2_temp[7]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][3], n_2_temp[4]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][3], n_2_temp[5]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][0][3], n_2_temp[6]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][0][3], n_2_temp[7]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][4], n_2_temp[0]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][4], n_2_temp[1]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][4], n_2_temp[2]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][4], n_2_temp[3]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][4], n_2_temp[4]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][0][4], n_2_temp[5]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][0][4], n_2_temp[6]));
                det_l[11] =
                    _mm256_add_pd(det_l[11], _mm256_mul_pd(matrix[2][0][4], n_2_temp[7]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][5], n_2_temp[0]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][5], n_2_temp[1]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][5], n_2_temp[2]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][5], n_2_temp[3]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][0][5], n_2_temp[4]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][0][5], n_2_temp[5]));
                det_l[11] =
                    _mm256_add_pd(det_l[11], _mm256_mul_pd(matrix[2][0][5], n_2_temp[6]));
                det_l[12] =
                    _mm256_add_pd(det_l[12], _mm256_mul_pd(matrix[2][0][5], n_2_temp[7]));
            }
            {
                __m256d n_2_temp[9];
                init_256d(9, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][4]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][5]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][6]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][4]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][5]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][6]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][4]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][5]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][6]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][0][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][5], matrix[1][5][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][6], matrix[1][5][0]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][6], matrix[1][5][1]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][7], matrix[1][5][0]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][7], matrix[1][5][1]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][1][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][1][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][0], n_2_temp[8]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][1][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][1], n_2_temp[6]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][1], n_2_temp[7]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][1][1], n_2_temp[8]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][2], n_2_temp[5]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][2], n_2_temp[6]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][1][2], n_2_temp[7]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][1][2], n_2_temp[8]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][3], n_2_temp[4]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][3], n_2_temp[5]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][1][3], n_2_temp[6]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][1][3], n_2_temp[7]));
                det_l[11] =
                    _mm256_add_pd(det_l[11], _mm256_mul_pd(matrix[2][1][3], n_2_temp[8]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][4], n_2_temp[0]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][4], n_2_temp[1]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][4], n_2_temp[2]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][4], n_2_temp[3]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][4], n_2_temp[4]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][1][4], n_2_temp[5]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][1][4], n_2_temp[6]));
                det_l[11] =
                    _mm256_add_pd(det_l[11], _mm256_mul_pd(matrix[2][1][4], n_2_temp[7]));
                det_l[12] =
                    _mm256_add_pd(det_l[12], _mm256_mul_pd(matrix[2][1][4], n_2_temp[8]));
            }
            {
                __m256d n_2_temp[13];
                init_256d(13, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][0][0], matrix[1][1][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][0], matrix[1][1][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][0], matrix[1][1][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][0], matrix[1][1][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][0], matrix[1][1][4]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][0], matrix[1][1][5]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][1], matrix[1][1][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][1], matrix[1][1][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][1], matrix[1][1][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][1], matrix[1][1][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][1], matrix[1][1][4]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][1], matrix[1][1][5]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][2], matrix[1][1][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][2], matrix[1][1][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][2], matrix[1][1][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][2], matrix[1][1][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][2], matrix[1][1][4]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][2], matrix[1][1][5]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][3], matrix[1][1][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][3], matrix[1][1][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][3], matrix[1][1][2]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][3], matrix[1][1][3]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][3], matrix[1][1][4]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][3], matrix[1][1][5]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][4], matrix[1][1][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][4], matrix[1][1][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][4], matrix[1][1][2]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][4], matrix[1][1][3]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][4], matrix[1][1][4]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][0][4], matrix[1][1][5]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][5], matrix[1][1][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][5], matrix[1][1][1]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][5], matrix[1][1][2]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][5], matrix[1][1][3]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][0][5], matrix[1][1][4]));
                n_2_temp[10] = _mm256_add_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][0][5], matrix[1][1][5]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][6], matrix[1][1][0]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][6], matrix[1][1][1]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][6], matrix[1][1][2]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][0][6], matrix[1][1][3]));
                n_2_temp[10] = _mm256_add_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][0][6], matrix[1][1][4]));
                n_2_temp[11] = _mm256_add_pd(
                    n_2_temp[11], _mm256_mul_pd(matrix[0][0][6], matrix[1][1][5]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][7], matrix[1][1][0]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][7], matrix[1][1][1]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][0][7], matrix[1][1][2]));
                n_2_temp[10] = _mm256_add_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][0][7], matrix[1][1][3]));
                n_2_temp[11] = _mm256_add_pd(
                    n_2_temp[11], _mm256_mul_pd(matrix[0][0][7], matrix[1][1][4]));
                n_2_temp[12] = _mm256_add_pd(
                    n_2_temp[12], _mm256_mul_pd(matrix[0][0][7], matrix[1][1][5]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][1][0], matrix[1][0][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][0], matrix[1][0][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][0], matrix[1][0][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][0], matrix[1][0][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][0], matrix[1][0][4]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][0], matrix[1][0][5]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][0], matrix[1][0][6]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][1], matrix[1][0][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][1], matrix[1][0][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][1], matrix[1][0][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][1], matrix[1][0][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][1], matrix[1][0][4]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][1], matrix[1][0][5]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][1], matrix[1][0][6]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][2], matrix[1][0][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][2], matrix[1][0][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][2], matrix[1][0][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][2], matrix[1][0][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][2], matrix[1][0][4]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][2], matrix[1][0][5]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][2], matrix[1][0][6]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][3], matrix[1][0][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][3], matrix[1][0][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][3], matrix[1][0][2]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][3], matrix[1][0][3]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][3], matrix[1][0][4]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][3], matrix[1][0][5]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][1][3], matrix[1][0][6]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][4], matrix[1][0][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][4], matrix[1][0][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][4], matrix[1][0][2]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][4], matrix[1][0][3]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][4], matrix[1][0][4]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][1][4], matrix[1][0][5]));
                n_2_temp[10] = _mm256_sub_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][1][4], matrix[1][0][6]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][5], matrix[1][0][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][5], matrix[1][0][1]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][5], matrix[1][0][2]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][5], matrix[1][0][3]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][1][5], matrix[1][0][4]));
                n_2_temp[10] = _mm256_sub_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][1][5], matrix[1][0][5]));
                n_2_temp[11] = _mm256_sub_pd(
                    n_2_temp[11], _mm256_mul_pd(matrix[0][1][5], matrix[1][0][6]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][6], matrix[1][0][0]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][6], matrix[1][0][1]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][6], matrix[1][0][2]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][1][6], matrix[1][0][3]));
                n_2_temp[10] = _mm256_sub_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][1][6], matrix[1][0][4]));
                n_2_temp[11] = _mm256_sub_pd(
                    n_2_temp[11], _mm256_mul_pd(matrix[0][1][6], matrix[1][0][5]));
                n_2_temp[12] = _mm256_sub_pd(
                    n_2_temp[12], _mm256_mul_pd(matrix[0][1][6], matrix[1][0][6]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][5][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][5][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][5][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][5][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][5][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][5][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][5][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][5][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][5][0], n_2_temp[8]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][5][0], n_2_temp[9]));
                det_l[10] = _mm256_add_pd(det_l[10],
                                          _mm256_mul_pd(matrix[2][5][0], n_2_temp[10]));
                det_l[11] = _mm256_add_pd(det_l[11],
                                          _mm256_mul_pd(matrix[2][5][0], n_2_temp[11]));
                det_l[12] = _mm256_add_pd(det_l[12],
                                          _mm256_mul_pd(matrix[2][5][0], n_2_temp[12]));
            }
        }
        __m256d det_r[1];
        init_256d(1, det_r);
        {
            __m256d n_2_temp[1];
            init_256d(1, n_2_temp);
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][4][0], matrix[4][3][0]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][2][0], n_2_temp[0]));
        }
        {
            res_poly[0] = _mm256_sub_pd(res_poly[0], _mm256_mul_pd(det_l[0], det_r[0]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[1], det_r[0]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[2], det_r[0]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[3], det_r[0]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[4], det_r[0]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[5], det_r[0]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[6], det_r[0]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[7], det_r[0]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[8], det_r[0]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[9], det_r[0]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[10], det_r[0]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[11], det_r[0]));
            res_poly[12] =
                _mm256_sub_pd(res_poly[12], _mm256_mul_pd(det_l[12], det_r[0]));
        }
    }

    template <>
    inline void
    det3_mul_det3_add_on<0, 2, 5, 1, 3, 4>(const __m256d matrix[6][6][8],
                                           __m256d *res_poly)
    {
        __m256d det_l[12];
        init_256d(12, det_l);
        {
            {
                __m256d n_2_temp[7];
                init_256d(7, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][2][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][5], matrix[1][5][1]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][4]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][4]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][4]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][0][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][0][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][0], n_2_temp[6]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][0][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][1], n_2_temp[6]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][2], n_2_temp[5]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][2], n_2_temp[6]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][3], n_2_temp[4]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][3], n_2_temp[5]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][0][3], n_2_temp[6]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][4], n_2_temp[0]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][4], n_2_temp[1]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][4], n_2_temp[2]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][4], n_2_temp[3]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][4], n_2_temp[4]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][0][4], n_2_temp[5]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][0][4], n_2_temp[6]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][5], n_2_temp[0]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][5], n_2_temp[1]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][5], n_2_temp[2]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][5], n_2_temp[3]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][0][5], n_2_temp[4]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][0][5], n_2_temp[5]));
                det_l[11] =
                    _mm256_add_pd(det_l[11], _mm256_mul_pd(matrix[2][0][5], n_2_temp[6]));
            }
            {
                __m256d n_2_temp[9];
                init_256d(9, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][4]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][5]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][6]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][4]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][5]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][6]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][4]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][5]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][6]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][0][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][5], matrix[1][5][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][6], matrix[1][5][0]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][6], matrix[1][5][1]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][7], matrix[1][5][0]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][7], matrix[1][5][1]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][2][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][2][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][2][0], n_2_temp[8]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][2][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][1], n_2_temp[6]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][2][1], n_2_temp[7]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][2][1], n_2_temp[8]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][2], n_2_temp[5]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][2][2], n_2_temp[6]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][2][2], n_2_temp[7]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][2][2], n_2_temp[8]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][3], n_2_temp[4]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][2][3], n_2_temp[5]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][2][3], n_2_temp[6]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][2][3], n_2_temp[7]));
                det_l[11] =
                    _mm256_add_pd(det_l[11], _mm256_mul_pd(matrix[2][2][3], n_2_temp[8]));
            }
            {
                __m256d n_2_temp[12];
                init_256d(12, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][0][0], matrix[1][2][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][0], matrix[1][2][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][0], matrix[1][2][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][0], matrix[1][2][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][0], matrix[1][2][4]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][1], matrix[1][2][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][1], matrix[1][2][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][1], matrix[1][2][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][1], matrix[1][2][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][1], matrix[1][2][4]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][2], matrix[1][2][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][2], matrix[1][2][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][2], matrix[1][2][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][2], matrix[1][2][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][2], matrix[1][2][4]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][3], matrix[1][2][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][3], matrix[1][2][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][3], matrix[1][2][2]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][3], matrix[1][2][3]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][3], matrix[1][2][4]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][4], matrix[1][2][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][4], matrix[1][2][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][4], matrix[1][2][2]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][4], matrix[1][2][3]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][4], matrix[1][2][4]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][5], matrix[1][2][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][5], matrix[1][2][1]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][5], matrix[1][2][2]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][5], matrix[1][2][3]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][0][5], matrix[1][2][4]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][6], matrix[1][2][0]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][6], matrix[1][2][1]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][6], matrix[1][2][2]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][0][6], matrix[1][2][3]));
                n_2_temp[10] = _mm256_add_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][0][6], matrix[1][2][4]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][7], matrix[1][2][0]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][7], matrix[1][2][1]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][0][7], matrix[1][2][2]));
                n_2_temp[10] = _mm256_add_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][0][7], matrix[1][2][3]));
                n_2_temp[11] = _mm256_add_pd(
                    n_2_temp[11], _mm256_mul_pd(matrix[0][0][7], matrix[1][2][4]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][2][0], matrix[1][0][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][0], matrix[1][0][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][0], matrix[1][0][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][0], matrix[1][0][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][0], matrix[1][0][4]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][0], matrix[1][0][5]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][0], matrix[1][0][6]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][1], matrix[1][0][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][1], matrix[1][0][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][1], matrix[1][0][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][1], matrix[1][0][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][1], matrix[1][0][4]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][1], matrix[1][0][5]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][1], matrix[1][0][6]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][2], matrix[1][0][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][2], matrix[1][0][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][2], matrix[1][0][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][2], matrix[1][0][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][2], matrix[1][0][4]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][2], matrix[1][0][5]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][2][2], matrix[1][0][6]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][3], matrix[1][0][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][3], matrix[1][0][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][3], matrix[1][0][2]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][3], matrix[1][0][3]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][3], matrix[1][0][4]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][2][3], matrix[1][0][5]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][2][3], matrix[1][0][6]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][4], matrix[1][0][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][4], matrix[1][0][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][4], matrix[1][0][2]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][4], matrix[1][0][3]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][2][4], matrix[1][0][4]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][2][4], matrix[1][0][5]));
                n_2_temp[10] = _mm256_sub_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][2][4], matrix[1][0][6]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][5], matrix[1][0][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][5], matrix[1][0][1]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][5], matrix[1][0][2]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][2][5], matrix[1][0][3]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][2][5], matrix[1][0][4]));
                n_2_temp[10] = _mm256_sub_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][2][5], matrix[1][0][5]));
                n_2_temp[11] = _mm256_sub_pd(
                    n_2_temp[11], _mm256_mul_pd(matrix[0][2][5], matrix[1][0][6]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][5][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][5][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][5][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][5][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][5][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][5][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][5][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][5][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][5][0], n_2_temp[8]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][5][0], n_2_temp[9]));
                det_l[10] = _mm256_add_pd(det_l[10],
                                          _mm256_mul_pd(matrix[2][5][0], n_2_temp[10]));
                det_l[11] = _mm256_add_pd(det_l[11],
                                          _mm256_mul_pd(matrix[2][5][0], n_2_temp[11]));
            }
        }
        __m256d det_r[2];
        init_256d(2, det_r);
        {
            __m256d n_2_temp[1];
            init_256d(1, n_2_temp);
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][4][0], matrix[4][3][0]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][1][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][1], n_2_temp[0]));
        }
        {
            res_poly[0] = _mm256_add_pd(res_poly[0], _mm256_mul_pd(det_l[0], det_r[0]));
            res_poly[1] = _mm256_add_pd(res_poly[1], _mm256_mul_pd(det_l[0], det_r[1]));
            res_poly[1] = _mm256_add_pd(res_poly[1], _mm256_mul_pd(det_l[1], det_r[0]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[1], det_r[1]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[2], det_r[0]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[2], det_r[1]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[3], det_r[0]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[3], det_r[1]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[4], det_r[0]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[4], det_r[1]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[5], det_r[0]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[5], det_r[1]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[6], det_r[0]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[6], det_r[1]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[7], det_r[0]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[7], det_r[1]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[8], det_r[0]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[8], det_r[1]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[9], det_r[0]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[9], det_r[1]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[10], det_r[0]));
            res_poly[11] =
                _mm256_add_pd(res_poly[11], _mm256_mul_pd(det_l[10], det_r[1]));
            res_poly[11] =
                _mm256_add_pd(res_poly[11], _mm256_mul_pd(det_l[11], det_r[0]));
            res_poly[12] =
                _mm256_add_pd(res_poly[12], _mm256_mul_pd(det_l[11], det_r[1]));
        }
    }

    template <>
    inline void
    det3_mul_det3_add_on<0, 3, 5, 1, 2, 4>(const __m256d matrix[6][6][8],
                                           __m256d *res_poly)
    {
        __m256d det_l[11];
        init_256d(11, det_l);
        {
            {
                __m256d n_2_temp[6];
                init_256d(6, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][3][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][4], matrix[1][5][1]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][3]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][3]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][3]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][0][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][0][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][0], n_2_temp[5]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][0][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][1], n_2_temp[5]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][2], n_2_temp[5]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][3], n_2_temp[4]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][3], n_2_temp[5]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][4], n_2_temp[0]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][4], n_2_temp[1]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][4], n_2_temp[2]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][4], n_2_temp[3]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][4], n_2_temp[4]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][0][4], n_2_temp[5]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][5], n_2_temp[0]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][5], n_2_temp[1]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][5], n_2_temp[2]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][5], n_2_temp[3]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][0][5], n_2_temp[4]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][0][5], n_2_temp[5]));
            }
            {
                __m256d n_2_temp[9];
                init_256d(9, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][4]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][5]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][6]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][4]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][5]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][6]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][4]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][5]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][6]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][0][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][5], matrix[1][5][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][6], matrix[1][5][0]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][6], matrix[1][5][1]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][7], matrix[1][5][0]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][7], matrix[1][5][1]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][3][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][3][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][3][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][3][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][3][0], n_2_temp[8]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][3][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][3][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][3][1], n_2_temp[6]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][3][1], n_2_temp[7]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][3][1], n_2_temp[8]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][3][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][3][2], n_2_temp[5]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][3][2], n_2_temp[6]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][3][2], n_2_temp[7]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][3][2], n_2_temp[8]));
            }
            {
                __m256d n_2_temp[11];
                init_256d(11, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][0][0], matrix[1][3][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][0], matrix[1][3][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][0], matrix[1][3][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][0], matrix[1][3][3]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][1], matrix[1][3][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][1], matrix[1][3][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][1], matrix[1][3][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][1], matrix[1][3][3]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][2], matrix[1][3][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][2], matrix[1][3][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][2], matrix[1][3][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][2], matrix[1][3][3]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][3], matrix[1][3][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][3], matrix[1][3][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][3], matrix[1][3][2]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][3], matrix[1][3][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][4], matrix[1][3][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][4], matrix[1][3][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][4], matrix[1][3][2]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][4], matrix[1][3][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][5], matrix[1][3][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][5], matrix[1][3][1]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][5], matrix[1][3][2]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][5], matrix[1][3][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][6], matrix[1][3][0]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][6], matrix[1][3][1]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][6], matrix[1][3][2]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][0][6], matrix[1][3][3]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][7], matrix[1][3][0]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][7], matrix[1][3][1]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][0][7], matrix[1][3][2]));
                n_2_temp[10] = _mm256_add_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][0][7], matrix[1][3][3]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][3][0], matrix[1][0][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][0], matrix[1][0][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][0], matrix[1][0][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][0], matrix[1][0][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][0], matrix[1][0][4]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][0], matrix[1][0][5]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][0], matrix[1][0][6]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][1], matrix[1][0][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][1], matrix[1][0][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][1], matrix[1][0][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][1], matrix[1][0][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][1], matrix[1][0][4]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][1], matrix[1][0][5]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][3][1], matrix[1][0][6]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][2], matrix[1][0][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][2], matrix[1][0][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][2], matrix[1][0][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][2], matrix[1][0][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][2], matrix[1][0][4]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][3][2], matrix[1][0][5]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][3][2], matrix[1][0][6]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][3], matrix[1][0][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][3], matrix[1][0][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][3], matrix[1][0][2]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][3], matrix[1][0][3]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][3][3], matrix[1][0][4]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][3][3], matrix[1][0][5]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][3][3], matrix[1][0][6]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][4], matrix[1][0][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][4], matrix[1][0][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][4], matrix[1][0][2]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][3][4], matrix[1][0][3]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][3][4], matrix[1][0][4]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][3][4], matrix[1][0][5]));
                n_2_temp[10] = _mm256_sub_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][3][4], matrix[1][0][6]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][5][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][5][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][5][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][5][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][5][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][5][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][5][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][5][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][5][0], n_2_temp[8]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][5][0], n_2_temp[9]));
                det_l[10] = _mm256_add_pd(det_l[10],
                                          _mm256_mul_pd(matrix[2][5][0], n_2_temp[10]));
            }
        }
        __m256d det_r[3];
        init_256d(3, det_r);
        {
            __m256d n_2_temp[2];
            init_256d(2, n_2_temp);
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][4][0], matrix[4][2][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][4][0], matrix[4][2][1]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][1][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][0], n_2_temp[1]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][1][1], n_2_temp[1]));
        }
        {
            __m256d n_2_temp[3];
            init_256d(3, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][4][0], matrix[4][1][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][4][0], matrix[4][1][1]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][4][0], matrix[4][1][2]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][2][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][2][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][2][0], n_2_temp[2]));
        }
        {
            res_poly[0] = _mm256_sub_pd(res_poly[0], _mm256_mul_pd(det_l[0], det_r[0]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[0], det_r[1]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[0], det_r[2]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[1], det_r[0]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[1], det_r[1]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[1], det_r[2]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[2], det_r[0]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[2], det_r[1]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[2], det_r[2]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[3], det_r[0]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[3], det_r[1]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[3], det_r[2]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[4], det_r[0]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[4], det_r[1]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[4], det_r[2]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[5], det_r[0]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[5], det_r[1]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[5], det_r[2]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[6], det_r[0]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[6], det_r[1]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[6], det_r[2]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[7], det_r[0]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[7], det_r[1]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[7], det_r[2]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[8], det_r[0]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[8], det_r[1]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[8], det_r[2]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[9], det_r[0]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[9], det_r[1]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[9], det_r[2]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[10], det_r[0]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[10], det_r[1]));
            res_poly[12] =
                _mm256_sub_pd(res_poly[12], _mm256_mul_pd(det_l[10], det_r[2]));
        }
    }
    template <>
    inline void
    det3_mul_det3_add_on<0, 4, 5, 1, 2, 3>(const __m256d matrix[6][6][8],
                                           __m256d *res_poly)
    {
        __m256d det_l[10];
        init_256d(10, det_l);
        {
            {
                __m256d n_2_temp[5];
                init_256d(5, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][4][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][3], matrix[1][5][1]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][2]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][2]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][2]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][0][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][0][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][0], n_2_temp[4]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][0][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][1], n_2_temp[4]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][0][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][2], n_2_temp[4]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][0][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][3], n_2_temp[4]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][0][4], n_2_temp[0]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][4], n_2_temp[1]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][4], n_2_temp[2]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][4], n_2_temp[3]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][4], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][0][5], n_2_temp[0]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][0][5], n_2_temp[1]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][0][5], n_2_temp[2]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][0][5], n_2_temp[3]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][0][5], n_2_temp[4]));
            }
            {
                __m256d n_2_temp[9];
                init_256d(9, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][4]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][5]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][0], matrix[1][0][6]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][4]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][5]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][1], matrix[1][0][6]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][4]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][5]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][5][2], matrix[1][0][6]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][0][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][5], matrix[1][5][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][6], matrix[1][5][0]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][6], matrix[1][5][1]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][7], matrix[1][5][0]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][7], matrix[1][5][1]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][4][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][4][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][4][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][4][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][4][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][4][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][4][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][4][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][4][0], n_2_temp[8]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][4][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][4][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][4][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][4][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][4][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][4][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][4][1], n_2_temp[6]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][4][1], n_2_temp[7]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][4][1], n_2_temp[8]));
            }
            {
                __m256d n_2_temp[10];
                init_256d(10, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][0][0], matrix[1][4][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][0], matrix[1][4][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][0], matrix[1][4][2]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][0][1], matrix[1][4][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][1], matrix[1][4][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][1], matrix[1][4][2]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][0][2], matrix[1][4][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][2], matrix[1][4][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][2], matrix[1][4][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][0][3], matrix[1][4][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][3], matrix[1][4][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][3], matrix[1][4][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][0][4], matrix[1][4][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][4], matrix[1][4][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][4], matrix[1][4][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][0][5], matrix[1][4][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][5], matrix[1][4][1]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][5], matrix[1][4][2]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][0][6], matrix[1][4][0]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][6], matrix[1][4][1]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][6], matrix[1][4][2]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][0][7], matrix[1][4][0]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][0][7], matrix[1][4][1]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][0][7], matrix[1][4][2]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][4][0], matrix[1][0][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][0], matrix[1][0][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][0], matrix[1][0][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][0], matrix[1][0][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][0], matrix[1][0][4]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][0], matrix[1][0][5]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][4][0], matrix[1][0][6]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][1], matrix[1][0][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][1], matrix[1][0][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][1], matrix[1][0][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][1], matrix[1][0][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][1], matrix[1][0][4]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][4][1], matrix[1][0][5]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][4][1], matrix[1][0][6]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][2], matrix[1][0][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][2], matrix[1][0][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][2], matrix[1][0][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][2], matrix[1][0][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][4][2], matrix[1][0][4]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][4][2], matrix[1][0][5]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][4][2], matrix[1][0][6]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][3], matrix[1][0][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][3], matrix[1][0][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][3], matrix[1][0][2]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][4][3], matrix[1][0][3]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][4][3], matrix[1][0][4]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][4][3], matrix[1][0][5]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][4][3], matrix[1][0][6]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][5][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][5][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][5][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][5][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][5][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][5][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][5][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][5][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][5][0], n_2_temp[8]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][5][0], n_2_temp[9]));
            }
        }
        __m256d det_r[4];
        init_256d(4, det_r);
        {
            __m256d n_2_temp[3];
            init_256d(3, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][2][0], matrix[4][3][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][2][1], matrix[4][3][0]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][2][2], matrix[4][3][0]));
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][3][0], matrix[4][2][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][0], matrix[4][2][1]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][1], matrix[4][2][0]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][3][1], matrix[4][2][1]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][1][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][1][0], n_2_temp[2]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][1][1], n_2_temp[1]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][1][1], n_2_temp[2]));
        }
        {
            __m256d n_2_temp[4];
            init_256d(4, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][3][0], matrix[4][1][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][0], matrix[4][1][1]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][3][0], matrix[4][1][2]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][1], matrix[4][1][0]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][3][1], matrix[4][1][1]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][3][1], matrix[4][1][2]));
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][1][0], matrix[4][3][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][1][1], matrix[4][3][0]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][1][2], matrix[4][3][0]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][1][3], matrix[4][3][0]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][2][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][2][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][2][0], n_2_temp[2]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][2][0], n_2_temp[3]));
        }
        {
            res_poly[0] = _mm256_add_pd(res_poly[0], _mm256_mul_pd(det_l[0], det_r[0]));
            res_poly[1] = _mm256_add_pd(res_poly[1], _mm256_mul_pd(det_l[0], det_r[1]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[0], det_r[2]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[0], det_r[3]));
            res_poly[1] = _mm256_add_pd(res_poly[1], _mm256_mul_pd(det_l[1], det_r[0]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[1], det_r[1]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[1], det_r[2]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[1], det_r[3]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[2], det_r[0]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[2], det_r[1]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[2], det_r[2]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[2], det_r[3]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[3], det_r[0]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[3], det_r[1]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[3], det_r[2]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[3], det_r[3]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[4], det_r[0]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[4], det_r[1]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[4], det_r[2]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[4], det_r[3]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[5], det_r[0]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[5], det_r[1]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[5], det_r[2]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[5], det_r[3]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[6], det_r[0]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[6], det_r[1]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[6], det_r[2]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[6], det_r[3]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[7], det_r[0]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[7], det_r[1]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[7], det_r[2]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[7], det_r[3]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[8], det_r[0]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[8], det_r[1]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[8], det_r[2]));
            res_poly[11] =
                _mm256_add_pd(res_poly[11], _mm256_mul_pd(det_l[8], det_r[3]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[9], det_r[0]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[9], det_r[1]));
            res_poly[11] =
                _mm256_add_pd(res_poly[11], _mm256_mul_pd(det_l[9], det_r[2]));
            res_poly[12] =
                _mm256_add_pd(res_poly[12], _mm256_mul_pd(det_l[9], det_r[3]));
        }
    }

    template <>
    inline void
    det3_mul_det3_add_on<1, 2, 5, 0, 3, 4>(const __m256d matrix[6][6][8],
                                           __m256d *res_poly)
    {
        __m256d det_l[11];
        init_256d(11, det_l);
        {
            {
                __m256d n_2_temp[7];
                init_256d(7, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][2][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][5], matrix[1][5][1]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][4]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][4]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][4]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][1][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][1][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][0], n_2_temp[6]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][1][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][1], n_2_temp[6]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][2], n_2_temp[5]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][2], n_2_temp[6]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][3], n_2_temp[4]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][3], n_2_temp[5]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][1][3], n_2_temp[6]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][4], n_2_temp[0]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][4], n_2_temp[1]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][4], n_2_temp[2]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][4], n_2_temp[3]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][4], n_2_temp[4]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][1][4], n_2_temp[5]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][1][4], n_2_temp[6]));
            }
            {
                __m256d n_2_temp[8];
                init_256d(8, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][4]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][5]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][4]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][5]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][4]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][5]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][1][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][5], matrix[1][5][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][6], matrix[1][5][0]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][6], matrix[1][5][1]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][2][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][2][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][0], n_2_temp[7]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][2][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][1], n_2_temp[6]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][2][1], n_2_temp[7]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][2], n_2_temp[5]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][2][2], n_2_temp[6]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][2][2], n_2_temp[7]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][3], n_2_temp[4]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][2][3], n_2_temp[5]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][2][3], n_2_temp[6]));
                det_l[10] =
                    _mm256_add_pd(det_l[10], _mm256_mul_pd(matrix[2][2][3], n_2_temp[7]));
            }
            {
                __m256d n_2_temp[11];
                init_256d(11, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][1][0], matrix[1][2][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][0], matrix[1][2][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][0], matrix[1][2][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][0], matrix[1][2][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][0], matrix[1][2][4]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][1], matrix[1][2][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][1], matrix[1][2][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][1], matrix[1][2][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][1], matrix[1][2][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][1], matrix[1][2][4]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][2], matrix[1][2][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][2], matrix[1][2][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][2], matrix[1][2][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][2], matrix[1][2][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][2], matrix[1][2][4]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][3], matrix[1][2][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][3], matrix[1][2][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][3], matrix[1][2][2]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][3], matrix[1][2][3]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][3], matrix[1][2][4]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][4], matrix[1][2][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][4], matrix[1][2][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][4], matrix[1][2][2]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][4], matrix[1][2][3]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][4], matrix[1][2][4]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][5], matrix[1][2][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][5], matrix[1][2][1]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][5], matrix[1][2][2]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][5], matrix[1][2][3]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][1][5], matrix[1][2][4]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][6], matrix[1][2][0]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][6], matrix[1][2][1]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][6], matrix[1][2][2]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][1][6], matrix[1][2][3]));
                n_2_temp[10] = _mm256_add_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][1][6], matrix[1][2][4]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][2][0], matrix[1][1][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][0], matrix[1][1][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][0], matrix[1][1][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][0], matrix[1][1][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][0], matrix[1][1][4]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][0], matrix[1][1][5]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][1], matrix[1][1][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][1], matrix[1][1][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][1], matrix[1][1][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][1], matrix[1][1][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][1], matrix[1][1][4]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][1], matrix[1][1][5]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][2], matrix[1][1][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][2], matrix[1][1][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][2], matrix[1][1][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][2], matrix[1][1][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][2], matrix[1][1][4]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][2], matrix[1][1][5]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][3], matrix[1][1][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][3], matrix[1][1][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][3], matrix[1][1][2]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][3], matrix[1][1][3]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][3], matrix[1][1][4]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][2][3], matrix[1][1][5]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][4], matrix[1][1][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][4], matrix[1][1][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][4], matrix[1][1][2]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][4], matrix[1][1][3]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][2][4], matrix[1][1][4]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][2][4], matrix[1][1][5]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][5], matrix[1][1][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][5], matrix[1][1][1]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][5], matrix[1][1][2]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][2][5], matrix[1][1][3]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][2][5], matrix[1][1][4]));
                n_2_temp[10] = _mm256_sub_pd(
                    n_2_temp[10], _mm256_mul_pd(matrix[0][2][5], matrix[1][1][5]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][5][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][5][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][5][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][5][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][5][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][5][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][5][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][5][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][5][0], n_2_temp[8]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][5][0], n_2_temp[9]));
                det_l[10] = _mm256_add_pd(det_l[10],
                                          _mm256_mul_pd(matrix[2][5][0], n_2_temp[10]));
            }
        }
        __m256d det_r[3];
        init_256d(3, det_r);
        {
            __m256d n_2_temp[1];
            init_256d(1, n_2_temp);
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][4][0], matrix[4][3][0]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][0][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][2], n_2_temp[0]));
        }
        {
            res_poly[0] = _mm256_sub_pd(res_poly[0], _mm256_mul_pd(det_l[0], det_r[0]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[0], det_r[1]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[0], det_r[2]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[1], det_r[0]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[1], det_r[1]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[1], det_r[2]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[2], det_r[0]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[2], det_r[1]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[2], det_r[2]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[3], det_r[0]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[3], det_r[1]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[3], det_r[2]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[4], det_r[0]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[4], det_r[1]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[4], det_r[2]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[5], det_r[0]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[5], det_r[1]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[5], det_r[2]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[6], det_r[0]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[6], det_r[1]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[6], det_r[2]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[7], det_r[0]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[7], det_r[1]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[7], det_r[2]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[8], det_r[0]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[8], det_r[1]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[8], det_r[2]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[9], det_r[0]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[9], det_r[1]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[9], det_r[2]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[10], det_r[0]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[10], det_r[1]));
            res_poly[12] =
                _mm256_sub_pd(res_poly[12], _mm256_mul_pd(det_l[10], det_r[2]));
        }
    }

    template <>
    inline void
    det3_mul_det3_add_on<1, 3, 5, 0, 2, 4>(const __m256d matrix[6][6][8],
                                           __m256d *res_poly)
    {
        __m256d det_l[10];
        init_256d(10, det_l);
        {
            {
                __m256d n_2_temp[6];
                init_256d(6, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][3][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][4], matrix[1][5][1]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][3]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][3]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][3]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][1][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][1][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][0], n_2_temp[5]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][1][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][1], n_2_temp[5]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][2], n_2_temp[5]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][3], n_2_temp[4]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][3], n_2_temp[5]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][4], n_2_temp[0]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][4], n_2_temp[1]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][4], n_2_temp[2]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][4], n_2_temp[3]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][4], n_2_temp[4]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][1][4], n_2_temp[5]));
            }
            {
                __m256d n_2_temp[8];
                init_256d(8, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][4]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][5]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][4]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][5]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][4]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][5]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][1][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][5], matrix[1][5][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][6], matrix[1][5][0]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][6], matrix[1][5][1]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][3][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][3][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][3][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][3][0], n_2_temp[7]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][3][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][3][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][3][1], n_2_temp[6]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][3][1], n_2_temp[7]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][3][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][3][2], n_2_temp[5]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][3][2], n_2_temp[6]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][3][2], n_2_temp[7]));
            }
            {
                __m256d n_2_temp[10];
                init_256d(10, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][1][0], matrix[1][3][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][0], matrix[1][3][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][0], matrix[1][3][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][0], matrix[1][3][3]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][1], matrix[1][3][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][1], matrix[1][3][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][1], matrix[1][3][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][1], matrix[1][3][3]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][2], matrix[1][3][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][2], matrix[1][3][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][2], matrix[1][3][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][2], matrix[1][3][3]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][3], matrix[1][3][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][3], matrix[1][3][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][3], matrix[1][3][2]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][3], matrix[1][3][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][4], matrix[1][3][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][4], matrix[1][3][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][4], matrix[1][3][2]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][4], matrix[1][3][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][5], matrix[1][3][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][5], matrix[1][3][1]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][5], matrix[1][3][2]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][5], matrix[1][3][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][6], matrix[1][3][0]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][6], matrix[1][3][1]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][6], matrix[1][3][2]));
                n_2_temp[9] = _mm256_add_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][1][6], matrix[1][3][3]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][3][0], matrix[1][1][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][0], matrix[1][1][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][0], matrix[1][1][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][0], matrix[1][1][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][0], matrix[1][1][4]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][0], matrix[1][1][5]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][1], matrix[1][1][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][1], matrix[1][1][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][1], matrix[1][1][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][1], matrix[1][1][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][1], matrix[1][1][4]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][1], matrix[1][1][5]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][2], matrix[1][1][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][2], matrix[1][1][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][2], matrix[1][1][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][2], matrix[1][1][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][2], matrix[1][1][4]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][3][2], matrix[1][1][5]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][3], matrix[1][1][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][3], matrix[1][1][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][3], matrix[1][1][2]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][3], matrix[1][1][3]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][3][3], matrix[1][1][4]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][3][3], matrix[1][1][5]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][4], matrix[1][1][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][4], matrix[1][1][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][4], matrix[1][1][2]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][3][4], matrix[1][1][3]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][3][4], matrix[1][1][4]));
                n_2_temp[9] = _mm256_sub_pd(
                    n_2_temp[9], _mm256_mul_pd(matrix[0][3][4], matrix[1][1][5]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][5][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][5][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][5][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][5][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][5][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][5][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][5][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][5][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][5][0], n_2_temp[8]));
                det_l[9] =
                    _mm256_add_pd(det_l[9], _mm256_mul_pd(matrix[2][5][0], n_2_temp[9]));
            }
        }
        __m256d det_r[4];
        init_256d(4, det_r);
        {
            __m256d n_2_temp[2];
            init_256d(2, n_2_temp);
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][4][0], matrix[4][2][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][4][0], matrix[4][2][1]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][0][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][0], n_2_temp[1]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][1], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][2], n_2_temp[0]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][2], n_2_temp[1]));
        }
        {
            __m256d n_2_temp[4];
            init_256d(4, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][4][0], matrix[4][0][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][4][0], matrix[4][0][1]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][4][0], matrix[4][0][2]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][4][0], matrix[4][0][3]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][2][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][2][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][2][0], n_2_temp[2]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][2][0], n_2_temp[3]));
        }
        {
            res_poly[0] = _mm256_add_pd(res_poly[0], _mm256_mul_pd(det_l[0], det_r[0]));
            res_poly[1] = _mm256_add_pd(res_poly[1], _mm256_mul_pd(det_l[0], det_r[1]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[0], det_r[2]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[0], det_r[3]));
            res_poly[1] = _mm256_add_pd(res_poly[1], _mm256_mul_pd(det_l[1], det_r[0]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[1], det_r[1]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[1], det_r[2]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[1], det_r[3]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[2], det_r[0]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[2], det_r[1]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[2], det_r[2]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[2], det_r[3]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[3], det_r[0]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[3], det_r[1]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[3], det_r[2]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[3], det_r[3]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[4], det_r[0]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[4], det_r[1]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[4], det_r[2]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[4], det_r[3]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[5], det_r[0]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[5], det_r[1]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[5], det_r[2]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[5], det_r[3]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[6], det_r[0]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[6], det_r[1]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[6], det_r[2]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[6], det_r[3]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[7], det_r[0]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[7], det_r[1]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[7], det_r[2]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[7], det_r[3]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[8], det_r[0]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[8], det_r[1]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[8], det_r[2]));
            res_poly[11] =
                _mm256_add_pd(res_poly[11], _mm256_mul_pd(det_l[8], det_r[3]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[9], det_r[0]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[9], det_r[1]));
            res_poly[11] =
                _mm256_add_pd(res_poly[11], _mm256_mul_pd(det_l[9], det_r[2]));
            res_poly[12] =
                _mm256_add_pd(res_poly[12], _mm256_mul_pd(det_l[9], det_r[3]));
        }
    }
    template <>
    inline void
    det3_mul_det3_add_on<1, 4, 5, 0, 2, 3>(const __m256d matrix[6][6][8],
                                           __m256d *res_poly)
    {
        __m256d det_l[9];
        init_256d(9, det_l);
        {
            {
                __m256d n_2_temp[5];
                init_256d(5, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][4][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][3], matrix[1][5][1]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][2]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][2]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][2]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][1][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][1][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][0], n_2_temp[4]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][1][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][1], n_2_temp[4]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][1][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][2], n_2_temp[4]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][1][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][3], n_2_temp[4]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][1][4], n_2_temp[0]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][1][4], n_2_temp[1]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][1][4], n_2_temp[2]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][1][4], n_2_temp[3]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][1][4], n_2_temp[4]));
            }
            {
                __m256d n_2_temp[8];
                init_256d(8, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][4]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][0], matrix[1][1][5]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][4]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][1], matrix[1][1][5]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][4]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][5][2], matrix[1][1][5]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][1][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][5], matrix[1][5][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][6], matrix[1][5][0]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][6], matrix[1][5][1]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][4][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][4][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][4][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][4][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][4][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][4][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][4][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][4][0], n_2_temp[7]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][4][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][4][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][4][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][4][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][4][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][4][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][4][1], n_2_temp[6]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][4][1], n_2_temp[7]));
            }
            {
                __m256d n_2_temp[9];
                init_256d(9, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][1][0], matrix[1][4][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][0], matrix[1][4][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][0], matrix[1][4][2]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][1][1], matrix[1][4][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][1], matrix[1][4][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][1], matrix[1][4][2]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][1][2], matrix[1][4][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][2], matrix[1][4][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][2], matrix[1][4][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][1][3], matrix[1][4][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][3], matrix[1][4][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][3], matrix[1][4][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][1][4], matrix[1][4][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][4], matrix[1][4][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][4], matrix[1][4][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][1][5], matrix[1][4][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][5], matrix[1][4][1]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][5], matrix[1][4][2]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][1][6], matrix[1][4][0]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][1][6], matrix[1][4][1]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][1][6], matrix[1][4][2]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][4][0], matrix[1][1][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][0], matrix[1][1][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][0], matrix[1][1][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][0], matrix[1][1][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][0], matrix[1][1][4]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][0], matrix[1][1][5]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][1], matrix[1][1][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][1], matrix[1][1][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][1], matrix[1][1][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][1], matrix[1][1][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][1], matrix[1][1][4]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][4][1], matrix[1][1][5]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][2], matrix[1][1][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][2], matrix[1][1][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][2], matrix[1][1][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][2], matrix[1][1][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][4][2], matrix[1][1][4]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][4][2], matrix[1][1][5]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][3], matrix[1][1][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][3], matrix[1][1][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][3], matrix[1][1][2]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][4][3], matrix[1][1][3]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][4][3], matrix[1][1][4]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][4][3], matrix[1][1][5]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][5][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][5][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][5][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][5][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][5][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][5][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][5][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][5][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][5][0], n_2_temp[8]));
            }
        }
        __m256d det_r[5];
        init_256d(5, det_r);
        {
            __m256d n_2_temp[3];
            init_256d(3, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][2][0], matrix[4][3][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][2][1], matrix[4][3][0]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][2][2], matrix[4][3][0]));
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][3][0], matrix[4][2][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][0], matrix[4][2][1]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][1], matrix[4][2][0]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][3][1], matrix[4][2][1]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][0][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][0], n_2_temp[2]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][1], n_2_temp[1]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][1], n_2_temp[2]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][2], n_2_temp[0]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][2], n_2_temp[1]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][0][2], n_2_temp[2]));
        }
        {
            __m256d n_2_temp[5];
            init_256d(5, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][3][0], matrix[4][0][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][0], matrix[4][0][1]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][3][0], matrix[4][0][2]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][3][0], matrix[4][0][3]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][1], matrix[4][0][0]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][3][1], matrix[4][0][1]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][3][1], matrix[4][0][2]));
            n_2_temp[4] = _mm256_add_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][3][1], matrix[4][0][3]));
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][0][0], matrix[4][3][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][0][1], matrix[4][3][0]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][0][2], matrix[4][3][0]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][0][3], matrix[4][3][0]));
            n_2_temp[4] = _mm256_sub_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][0][4], matrix[4][3][0]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][2][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][2][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][2][0], n_2_temp[2]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][2][0], n_2_temp[3]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][2][0], n_2_temp[4]));
        }
        {
            res_poly[0] = _mm256_sub_pd(res_poly[0], _mm256_mul_pd(det_l[0], det_r[0]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[0], det_r[1]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[0], det_r[2]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[0], det_r[3]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[0], det_r[4]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[1], det_r[0]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[1], det_r[1]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[1], det_r[2]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[1], det_r[3]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[1], det_r[4]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[2], det_r[0]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[2], det_r[1]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[2], det_r[2]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[2], det_r[3]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[2], det_r[4]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[3], det_r[0]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[3], det_r[1]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[3], det_r[2]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[3], det_r[3]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[3], det_r[4]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[4], det_r[0]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[4], det_r[1]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[4], det_r[2]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[4], det_r[3]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[4], det_r[4]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[5], det_r[0]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[5], det_r[1]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[5], det_r[2]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[5], det_r[3]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[5], det_r[4]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[6], det_r[0]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[6], det_r[1]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[6], det_r[2]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[6], det_r[3]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[6], det_r[4]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[7], det_r[0]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[7], det_r[1]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[7], det_r[2]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[7], det_r[3]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[7], det_r[4]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[8], det_r[0]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[8], det_r[1]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[8], det_r[2]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[8], det_r[3]));
            res_poly[12] =
                _mm256_sub_pd(res_poly[12], _mm256_mul_pd(det_l[8], det_r[4]));
        }
    }

    template <>
    inline void
    det3_mul_det3_add_on<2, 3, 5, 0, 1, 4>(const __m256d matrix[6][6][8],
                                           __m256d *res_poly)
    {
        __m256d det_l[9];
        init_256d(9, det_l);
        {
            {
                __m256d n_2_temp[6];
                init_256d(6, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][3][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][4], matrix[1][5][1]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][3]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][3]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][3]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][2][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][2][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][0], n_2_temp[5]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][2][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][1], n_2_temp[5]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][2], n_2_temp[5]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][3], n_2_temp[4]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][2][3], n_2_temp[5]));
            }
            {
                __m256d n_2_temp[7];
                init_256d(7, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][4]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][4]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][4]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][2][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][5], matrix[1][5][1]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][3][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][3][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][3][0], n_2_temp[6]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][3][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][3][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][3][1], n_2_temp[6]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][3][2], n_2_temp[4]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][3][2], n_2_temp[5]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][3][2], n_2_temp[6]));
            }
            {
                __m256d n_2_temp[9];
                init_256d(9, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][2][0], matrix[1][3][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][0], matrix[1][3][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][0], matrix[1][3][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][0], matrix[1][3][3]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][1], matrix[1][3][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][1], matrix[1][3][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][1], matrix[1][3][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][1], matrix[1][3][3]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][2], matrix[1][3][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][2], matrix[1][3][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][2], matrix[1][3][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][2], matrix[1][3][3]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][3], matrix[1][3][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][3], matrix[1][3][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][3], matrix[1][3][2]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][3], matrix[1][3][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][4], matrix[1][3][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][4], matrix[1][3][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][4], matrix[1][3][2]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][4], matrix[1][3][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][5], matrix[1][3][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][5], matrix[1][3][1]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][5], matrix[1][3][2]));
                n_2_temp[8] = _mm256_add_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][2][5], matrix[1][3][3]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][3][0], matrix[1][2][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][0], matrix[1][2][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][0], matrix[1][2][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][0], matrix[1][2][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][0], matrix[1][2][4]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][1], matrix[1][2][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][1], matrix[1][2][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][1], matrix[1][2][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][1], matrix[1][2][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][1], matrix[1][2][4]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][2], matrix[1][2][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][2], matrix[1][2][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][2], matrix[1][2][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][2], matrix[1][2][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][2], matrix[1][2][4]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][3], matrix[1][2][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][3], matrix[1][2][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][3], matrix[1][2][2]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][3], matrix[1][2][3]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][3][3], matrix[1][2][4]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][4], matrix[1][2][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][4], matrix[1][2][1]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][4], matrix[1][2][2]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][3][4], matrix[1][2][3]));
                n_2_temp[8] = _mm256_sub_pd(
                    n_2_temp[8], _mm256_mul_pd(matrix[0][3][4], matrix[1][2][4]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][5][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][5][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][5][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][5][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][5][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][5][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][5][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][5][0], n_2_temp[7]));
                det_l[8] =
                    _mm256_add_pd(det_l[8], _mm256_mul_pd(matrix[2][5][0], n_2_temp[8]));
            }
        }
        __m256d det_r[5];
        init_256d(5, det_r);
        {
            __m256d n_2_temp[3];
            init_256d(3, n_2_temp);
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][4][0], matrix[4][1][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][4][0], matrix[4][1][1]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][4][0], matrix[4][1][2]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][0][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][0], n_2_temp[2]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][1], n_2_temp[1]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][1], n_2_temp[2]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][2], n_2_temp[0]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][2], n_2_temp[1]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][0][2], n_2_temp[2]));
        }
        {
            __m256d n_2_temp[4];
            init_256d(4, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][4][0], matrix[4][0][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][4][0], matrix[4][0][1]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][4][0], matrix[4][0][2]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][4][0], matrix[4][0][3]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][1][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][1][0], n_2_temp[2]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][1][0], n_2_temp[3]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][1][1], n_2_temp[1]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][1][1], n_2_temp[2]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][1][1], n_2_temp[3]));
        }
        {
            res_poly[0] = _mm256_sub_pd(res_poly[0], _mm256_mul_pd(det_l[0], det_r[0]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[0], det_r[1]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[0], det_r[2]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[0], det_r[3]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[0], det_r[4]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[1], det_r[0]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[1], det_r[1]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[1], det_r[2]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[1], det_r[3]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[1], det_r[4]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[2], det_r[0]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[2], det_r[1]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[2], det_r[2]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[2], det_r[3]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[2], det_r[4]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[3], det_r[0]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[3], det_r[1]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[3], det_r[2]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[3], det_r[3]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[3], det_r[4]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[4], det_r[0]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[4], det_r[1]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[4], det_r[2]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[4], det_r[3]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[4], det_r[4]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[5], det_r[0]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[5], det_r[1]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[5], det_r[2]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[5], det_r[3]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[5], det_r[4]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[6], det_r[0]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[6], det_r[1]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[6], det_r[2]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[6], det_r[3]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[6], det_r[4]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[7], det_r[0]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[7], det_r[1]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[7], det_r[2]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[7], det_r[3]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[7], det_r[4]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[8], det_r[0]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[8], det_r[1]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[8], det_r[2]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[8], det_r[3]));
            res_poly[12] =
                _mm256_sub_pd(res_poly[12], _mm256_mul_pd(det_l[8], det_r[4]));
        }
    }
    template <>
    inline void
    det3_mul_det3_add_on<2, 4, 5, 0, 1, 3>(const __m256d matrix[6][6][8],
                                           __m256d *res_poly)
    {
        __m256d det_l[8];
        init_256d(8, det_l);
        {
            {
                __m256d n_2_temp[5];
                init_256d(5, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][4][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][3], matrix[1][5][1]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][2]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][2]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][2]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][2][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][2][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][0], n_2_temp[4]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][2][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][1], n_2_temp[4]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][2][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][2], n_2_temp[4]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][2][3], n_2_temp[0]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][2][3], n_2_temp[1]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][2][3], n_2_temp[2]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][2][3], n_2_temp[3]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][2][3], n_2_temp[4]));
            }
            {
                __m256d n_2_temp[7];
                init_256d(7, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][3]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][0], matrix[1][2][4]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][3]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][1], matrix[1][2][4]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][3]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][5][2], matrix[1][2][4]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][2][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][4], matrix[1][5][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][5], matrix[1][5][0]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][5], matrix[1][5][1]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][4][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][4][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][4][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][4][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][4][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][4][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][4][0], n_2_temp[6]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][4][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][4][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][4][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][4][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][4][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][4][1], n_2_temp[5]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][4][1], n_2_temp[6]));
            }
            {
                __m256d n_2_temp[8];
                init_256d(8, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][2][0], matrix[1][4][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][0], matrix[1][4][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][0], matrix[1][4][2]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][2][1], matrix[1][4][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][1], matrix[1][4][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][1], matrix[1][4][2]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][2][2], matrix[1][4][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][2], matrix[1][4][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][2], matrix[1][4][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][2][3], matrix[1][4][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][3], matrix[1][4][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][3], matrix[1][4][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][2][4], matrix[1][4][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][4], matrix[1][4][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][4], matrix[1][4][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][2][5], matrix[1][4][0]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][2][5], matrix[1][4][1]));
                n_2_temp[7] = _mm256_add_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][2][5], matrix[1][4][2]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][4][0], matrix[1][2][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][0], matrix[1][2][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][0], matrix[1][2][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][0], matrix[1][2][3]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][0], matrix[1][2][4]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][1], matrix[1][2][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][1], matrix[1][2][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][1], matrix[1][2][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][1], matrix[1][2][3]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][1], matrix[1][2][4]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][2], matrix[1][2][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][2], matrix[1][2][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][2], matrix[1][2][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][2], matrix[1][2][3]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][4][2], matrix[1][2][4]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][3], matrix[1][2][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][3], matrix[1][2][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][3], matrix[1][2][2]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][4][3], matrix[1][2][3]));
                n_2_temp[7] = _mm256_sub_pd(
                    n_2_temp[7], _mm256_mul_pd(matrix[0][4][3], matrix[1][2][4]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][5][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][5][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][5][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][5][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][5][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][5][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][5][0], n_2_temp[6]));
                det_l[7] =
                    _mm256_add_pd(det_l[7], _mm256_mul_pd(matrix[2][5][0], n_2_temp[7]));
            }
        }
        __m256d det_r[6];
        init_256d(6, det_r);
        {
            __m256d n_2_temp[4];
            init_256d(4, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][1][0], matrix[4][3][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][1][1], matrix[4][3][0]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][1][2], matrix[4][3][0]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][1][3], matrix[4][3][0]));
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][3][0], matrix[4][1][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][0], matrix[4][1][1]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][3][0], matrix[4][1][2]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][1], matrix[4][1][0]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][3][1], matrix[4][1][1]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][3][1], matrix[4][1][2]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][0][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][0], n_2_temp[2]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][0], n_2_temp[3]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][1], n_2_temp[1]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][1], n_2_temp[2]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][0][1], n_2_temp[3]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][2], n_2_temp[0]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][2], n_2_temp[1]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][0][2], n_2_temp[2]));
            det_r[5] =
                _mm256_add_pd(det_r[5], _mm256_mul_pd(matrix[5][0][2], n_2_temp[3]));
        }
        {
            __m256d n_2_temp[5];
            init_256d(5, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][3][0], matrix[4][0][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][0], matrix[4][0][1]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][3][0], matrix[4][0][2]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][3][0], matrix[4][0][3]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][3][1], matrix[4][0][0]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][3][1], matrix[4][0][1]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][3][1], matrix[4][0][2]));
            n_2_temp[4] = _mm256_add_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][3][1], matrix[4][0][3]));
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][0][0], matrix[4][3][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][0][1], matrix[4][3][0]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][0][2], matrix[4][3][0]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][0][3], matrix[4][3][0]));
            n_2_temp[4] = _mm256_sub_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][0][4], matrix[4][3][0]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][1][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][1][0], n_2_temp[2]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][1][0], n_2_temp[3]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][1][0], n_2_temp[4]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][1][1], n_2_temp[1]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][1][1], n_2_temp[2]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][1][1], n_2_temp[3]));
            det_r[5] =
                _mm256_add_pd(det_r[5], _mm256_mul_pd(matrix[5][1][1], n_2_temp[4]));
        }
        {
            res_poly[0] = _mm256_add_pd(res_poly[0], _mm256_mul_pd(det_l[0], det_r[0]));
            res_poly[1] = _mm256_add_pd(res_poly[1], _mm256_mul_pd(det_l[0], det_r[1]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[0], det_r[2]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[0], det_r[3]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[0], det_r[4]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[0], det_r[5]));
            res_poly[1] = _mm256_add_pd(res_poly[1], _mm256_mul_pd(det_l[1], det_r[0]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[1], det_r[1]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[1], det_r[2]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[1], det_r[3]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[1], det_r[4]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[1], det_r[5]));
            res_poly[2] = _mm256_add_pd(res_poly[2], _mm256_mul_pd(det_l[2], det_r[0]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[2], det_r[1]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[2], det_r[2]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[2], det_r[3]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[2], det_r[4]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[2], det_r[5]));
            res_poly[3] = _mm256_add_pd(res_poly[3], _mm256_mul_pd(det_l[3], det_r[0]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[3], det_r[1]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[3], det_r[2]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[3], det_r[3]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[3], det_r[4]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[3], det_r[5]));
            res_poly[4] = _mm256_add_pd(res_poly[4], _mm256_mul_pd(det_l[4], det_r[0]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[4], det_r[1]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[4], det_r[2]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[4], det_r[3]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[4], det_r[4]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[4], det_r[5]));
            res_poly[5] = _mm256_add_pd(res_poly[5], _mm256_mul_pd(det_l[5], det_r[0]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[5], det_r[1]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[5], det_r[2]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[5], det_r[3]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[5], det_r[4]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[5], det_r[5]));
            res_poly[6] = _mm256_add_pd(res_poly[6], _mm256_mul_pd(det_l[6], det_r[0]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[6], det_r[1]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[6], det_r[2]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[6], det_r[3]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[6], det_r[4]));
            res_poly[11] =
                _mm256_add_pd(res_poly[11], _mm256_mul_pd(det_l[6], det_r[5]));
            res_poly[7] = _mm256_add_pd(res_poly[7], _mm256_mul_pd(det_l[7], det_r[0]));
            res_poly[8] = _mm256_add_pd(res_poly[8], _mm256_mul_pd(det_l[7], det_r[1]));
            res_poly[9] = _mm256_add_pd(res_poly[9], _mm256_mul_pd(det_l[7], det_r[2]));
            res_poly[10] =
                _mm256_add_pd(res_poly[10], _mm256_mul_pd(det_l[7], det_r[3]));
            res_poly[11] =
                _mm256_add_pd(res_poly[11], _mm256_mul_pd(det_l[7], det_r[4]));
            res_poly[12] =
                _mm256_add_pd(res_poly[12], _mm256_mul_pd(det_l[7], det_r[5]));
        }
    }
    template <>
    inline void
    det3_mul_det3_add_on<3, 4, 5, 0, 1, 2>(const __m256d matrix[6][6][8],
                                           __m256d *res_poly)
    {
        __m256d det_l[7];
        init_256d(7, det_l);
        {
            {
                __m256d n_2_temp[5];
                init_256d(5, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][4][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][3], matrix[1][5][1]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][4][2]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][4][2]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][4][2]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][3][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][3][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][0], n_2_temp[4]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][3][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][1], n_2_temp[4]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][3][2], n_2_temp[0]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][3][2], n_2_temp[1]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][3][2], n_2_temp[2]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][3][2], n_2_temp[3]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][3][2], n_2_temp[4]));
            }
            {
                __m256d n_2_temp[6];
                init_256d(6, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][0], matrix[1][3][3]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][1], matrix[1][3][3]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][2]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][5][2], matrix[1][3][3]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][3][0], matrix[1][5][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][0], matrix[1][5][1]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][1], matrix[1][5][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][1], matrix[1][5][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][2], matrix[1][5][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][2], matrix[1][5][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][3], matrix[1][5][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][3], matrix[1][5][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][4], matrix[1][5][0]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][4], matrix[1][5][1]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][4][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][4][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][4][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][4][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][4][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][4][0], n_2_temp[5]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][4][1], n_2_temp[0]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][4][1], n_2_temp[1]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][4][1], n_2_temp[2]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][4][1], n_2_temp[3]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][4][1], n_2_temp[4]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][4][1], n_2_temp[5]));
            }
            {
                __m256d n_2_temp[7];
                init_256d(7, n_2_temp);
                n_2_temp[0] = _mm256_add_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][3][0], matrix[1][4][0]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][0], matrix[1][4][1]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][0], matrix[1][4][2]));
                n_2_temp[1] = _mm256_add_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][3][1], matrix[1][4][0]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][1], matrix[1][4][1]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][1], matrix[1][4][2]));
                n_2_temp[2] = _mm256_add_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][3][2], matrix[1][4][0]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][2], matrix[1][4][1]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][2], matrix[1][4][2]));
                n_2_temp[3] = _mm256_add_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][3][3], matrix[1][4][0]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][3], matrix[1][4][1]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][3], matrix[1][4][2]));
                n_2_temp[4] = _mm256_add_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][3][4], matrix[1][4][0]));
                n_2_temp[5] = _mm256_add_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][3][4], matrix[1][4][1]));
                n_2_temp[6] = _mm256_add_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][3][4], matrix[1][4][2]));
                n_2_temp[0] = _mm256_sub_pd(
                    n_2_temp[0], _mm256_mul_pd(matrix[0][4][0], matrix[1][3][0]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][0], matrix[1][3][1]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][0], matrix[1][3][2]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][0], matrix[1][3][3]));
                n_2_temp[1] = _mm256_sub_pd(
                    n_2_temp[1], _mm256_mul_pd(matrix[0][4][1], matrix[1][3][0]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][1], matrix[1][3][1]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][1], matrix[1][3][2]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][1], matrix[1][3][3]));
                n_2_temp[2] = _mm256_sub_pd(
                    n_2_temp[2], _mm256_mul_pd(matrix[0][4][2], matrix[1][3][0]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][2], matrix[1][3][1]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][2], matrix[1][3][2]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][2], matrix[1][3][3]));
                n_2_temp[3] = _mm256_sub_pd(
                    n_2_temp[3], _mm256_mul_pd(matrix[0][4][3], matrix[1][3][0]));
                n_2_temp[4] = _mm256_sub_pd(
                    n_2_temp[4], _mm256_mul_pd(matrix[0][4][3], matrix[1][3][1]));
                n_2_temp[5] = _mm256_sub_pd(
                    n_2_temp[5], _mm256_mul_pd(matrix[0][4][3], matrix[1][3][2]));
                n_2_temp[6] = _mm256_sub_pd(
                    n_2_temp[6], _mm256_mul_pd(matrix[0][4][3], matrix[1][3][3]));
                det_l[0] =
                    _mm256_add_pd(det_l[0], _mm256_mul_pd(matrix[2][5][0], n_2_temp[0]));
                det_l[1] =
                    _mm256_add_pd(det_l[1], _mm256_mul_pd(matrix[2][5][0], n_2_temp[1]));
                det_l[2] =
                    _mm256_add_pd(det_l[2], _mm256_mul_pd(matrix[2][5][0], n_2_temp[2]));
                det_l[3] =
                    _mm256_add_pd(det_l[3], _mm256_mul_pd(matrix[2][5][0], n_2_temp[3]));
                det_l[4] =
                    _mm256_add_pd(det_l[4], _mm256_mul_pd(matrix[2][5][0], n_2_temp[4]));
                det_l[5] =
                    _mm256_add_pd(det_l[5], _mm256_mul_pd(matrix[2][5][0], n_2_temp[5]));
                det_l[6] =
                    _mm256_add_pd(det_l[6], _mm256_mul_pd(matrix[2][5][0], n_2_temp[6]));
            }
        }
        __m256d det_r[7];
        init_256d(7, det_r);
        {
            __m256d n_2_temp[5];
            init_256d(5, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][1][0], matrix[4][2][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][1][0], matrix[4][2][1]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][1][1], matrix[4][2][0]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][1][1], matrix[4][2][1]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][1][2], matrix[4][2][0]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][1][2], matrix[4][2][1]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][1][3], matrix[4][2][0]));
            n_2_temp[4] = _mm256_add_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][1][3], matrix[4][2][1]));
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][2][0], matrix[4][1][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][2][0], matrix[4][1][1]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][2][0], matrix[4][1][2]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][2][1], matrix[4][1][0]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][2][1], matrix[4][1][1]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][2][1], matrix[4][1][2]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][2][2], matrix[4][1][0]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][2][2], matrix[4][1][1]));
            n_2_temp[4] = _mm256_sub_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][2][2], matrix[4][1][2]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][0][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][0], n_2_temp[2]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][0], n_2_temp[3]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][0][0], n_2_temp[4]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][0][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][1], n_2_temp[1]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][1], n_2_temp[2]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][0][1], n_2_temp[3]));
            det_r[5] =
                _mm256_add_pd(det_r[5], _mm256_mul_pd(matrix[5][0][1], n_2_temp[4]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][0][2], n_2_temp[0]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][0][2], n_2_temp[1]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][0][2], n_2_temp[2]));
            det_r[5] =
                _mm256_add_pd(det_r[5], _mm256_mul_pd(matrix[5][0][2], n_2_temp[3]));
            det_r[6] =
                _mm256_add_pd(det_r[6], _mm256_mul_pd(matrix[5][0][2], n_2_temp[4]));
        }
        {
            __m256d n_2_temp[6];
            init_256d(6, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][2][0], matrix[4][0][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][2][0], matrix[4][0][1]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][2][0], matrix[4][0][2]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][2][0], matrix[4][0][3]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][2][1], matrix[4][0][0]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][2][1], matrix[4][0][1]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][2][1], matrix[4][0][2]));
            n_2_temp[4] = _mm256_add_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][2][1], matrix[4][0][3]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][2][2], matrix[4][0][0]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][2][2], matrix[4][0][1]));
            n_2_temp[4] = _mm256_add_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][2][2], matrix[4][0][2]));
            n_2_temp[5] = _mm256_add_pd(
                n_2_temp[5], _mm256_mul_pd(matrix[3][2][2], matrix[4][0][3]));
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][0][0], matrix[4][2][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][0][0], matrix[4][2][1]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][0][1], matrix[4][2][0]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][0][1], matrix[4][2][1]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][0][2], matrix[4][2][0]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][0][2], matrix[4][2][1]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][0][3], matrix[4][2][0]));
            n_2_temp[4] = _mm256_sub_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][0][3], matrix[4][2][1]));
            n_2_temp[4] = _mm256_sub_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][0][4], matrix[4][2][0]));
            n_2_temp[5] = _mm256_sub_pd(
                n_2_temp[5], _mm256_mul_pd(matrix[3][0][4], matrix[4][2][1]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][1][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][1][0], n_2_temp[2]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][1][0], n_2_temp[3]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][1][0], n_2_temp[4]));
            det_r[5] =
                _mm256_add_pd(det_r[5], _mm256_mul_pd(matrix[5][1][0], n_2_temp[5]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][1][1], n_2_temp[0]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][1][1], n_2_temp[1]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][1][1], n_2_temp[2]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][1][1], n_2_temp[3]));
            det_r[5] =
                _mm256_add_pd(det_r[5], _mm256_mul_pd(matrix[5][1][1], n_2_temp[4]));
            det_r[6] =
                _mm256_add_pd(det_r[6], _mm256_mul_pd(matrix[5][1][1], n_2_temp[5]));
        }
        {
            __m256d n_2_temp[7];
            init_256d(7, n_2_temp);
            n_2_temp[0] = _mm256_add_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][0][0], matrix[4][1][0]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][0][0], matrix[4][1][1]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][0][0], matrix[4][1][2]));
            n_2_temp[1] = _mm256_add_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][0][1], matrix[4][1][0]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][0][1], matrix[4][1][1]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][0][1], matrix[4][1][2]));
            n_2_temp[2] = _mm256_add_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][0][2], matrix[4][1][0]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][0][2], matrix[4][1][1]));
            n_2_temp[4] = _mm256_add_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][0][2], matrix[4][1][2]));
            n_2_temp[3] = _mm256_add_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][0][3], matrix[4][1][0]));
            n_2_temp[4] = _mm256_add_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][0][3], matrix[4][1][1]));
            n_2_temp[5] = _mm256_add_pd(
                n_2_temp[5], _mm256_mul_pd(matrix[3][0][3], matrix[4][1][2]));
            n_2_temp[4] = _mm256_add_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][0][4], matrix[4][1][0]));
            n_2_temp[5] = _mm256_add_pd(
                n_2_temp[5], _mm256_mul_pd(matrix[3][0][4], matrix[4][1][1]));
            n_2_temp[6] = _mm256_add_pd(
                n_2_temp[6], _mm256_mul_pd(matrix[3][0][4], matrix[4][1][2]));
            n_2_temp[0] = _mm256_sub_pd(
                n_2_temp[0], _mm256_mul_pd(matrix[3][1][0], matrix[4][0][0]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][1][0], matrix[4][0][1]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][1][0], matrix[4][0][2]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][1][0], matrix[4][0][3]));
            n_2_temp[1] = _mm256_sub_pd(
                n_2_temp[1], _mm256_mul_pd(matrix[3][1][1], matrix[4][0][0]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][1][1], matrix[4][0][1]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][1][1], matrix[4][0][2]));
            n_2_temp[4] = _mm256_sub_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][1][1], matrix[4][0][3]));
            n_2_temp[2] = _mm256_sub_pd(
                n_2_temp[2], _mm256_mul_pd(matrix[3][1][2], matrix[4][0][0]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][1][2], matrix[4][0][1]));
            n_2_temp[4] = _mm256_sub_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][1][2], matrix[4][0][2]));
            n_2_temp[5] = _mm256_sub_pd(
                n_2_temp[5], _mm256_mul_pd(matrix[3][1][2], matrix[4][0][3]));
            n_2_temp[3] = _mm256_sub_pd(
                n_2_temp[3], _mm256_mul_pd(matrix[3][1][3], matrix[4][0][0]));
            n_2_temp[4] = _mm256_sub_pd(
                n_2_temp[4], _mm256_mul_pd(matrix[3][1][3], matrix[4][0][1]));
            n_2_temp[5] = _mm256_sub_pd(
                n_2_temp[5], _mm256_mul_pd(matrix[3][1][3], matrix[4][0][2]));
            n_2_temp[6] = _mm256_sub_pd(
                n_2_temp[6], _mm256_mul_pd(matrix[3][1][3], matrix[4][0][3]));
            det_r[0] =
                _mm256_add_pd(det_r[0], _mm256_mul_pd(matrix[5][2][0], n_2_temp[0]));
            det_r[1] =
                _mm256_add_pd(det_r[1], _mm256_mul_pd(matrix[5][2][0], n_2_temp[1]));
            det_r[2] =
                _mm256_add_pd(det_r[2], _mm256_mul_pd(matrix[5][2][0], n_2_temp[2]));
            det_r[3] =
                _mm256_add_pd(det_r[3], _mm256_mul_pd(matrix[5][2][0], n_2_temp[3]));
            det_r[4] =
                _mm256_add_pd(det_r[4], _mm256_mul_pd(matrix[5][2][0], n_2_temp[4]));
            det_r[5] =
                _mm256_add_pd(det_r[5], _mm256_mul_pd(matrix[5][2][0], n_2_temp[5]));
            det_r[6] =
                _mm256_add_pd(det_r[6], _mm256_mul_pd(matrix[5][2][0], n_2_temp[6]));
        }
        {
            res_poly[0] = _mm256_sub_pd(res_poly[0], _mm256_mul_pd(det_l[0], det_r[0]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[0], det_r[1]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[0], det_r[2]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[0], det_r[3]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[0], det_r[4]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[0], det_r[5]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[0], det_r[6]));
            res_poly[1] = _mm256_sub_pd(res_poly[1], _mm256_mul_pd(det_l[1], det_r[0]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[1], det_r[1]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[1], det_r[2]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[1], det_r[3]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[1], det_r[4]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[1], det_r[5]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[1], det_r[6]));
            res_poly[2] = _mm256_sub_pd(res_poly[2], _mm256_mul_pd(det_l[2], det_r[0]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[2], det_r[1]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[2], det_r[2]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[2], det_r[3]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[2], det_r[4]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[2], det_r[5]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[2], det_r[6]));
            res_poly[3] = _mm256_sub_pd(res_poly[3], _mm256_mul_pd(det_l[3], det_r[0]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[3], det_r[1]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[3], det_r[2]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[3], det_r[3]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[3], det_r[4]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[3], det_r[5]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[3], det_r[6]));
            res_poly[4] = _mm256_sub_pd(res_poly[4], _mm256_mul_pd(det_l[4], det_r[0]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[4], det_r[1]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[4], det_r[2]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[4], det_r[3]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[4], det_r[4]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[4], det_r[5]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[4], det_r[6]));
            res_poly[5] = _mm256_sub_pd(res_poly[5], _mm256_mul_pd(det_l[5], det_r[0]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[5], det_r[1]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[5], det_r[2]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[5], det_r[3]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[5], det_r[4]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[5], det_r[5]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[5], det_r[6]));
            res_poly[6] = _mm256_sub_pd(res_poly[6], _mm256_mul_pd(det_l[6], det_r[0]));
            res_poly[7] = _mm256_sub_pd(res_poly[7], _mm256_mul_pd(det_l[6], det_r[1]));
            res_poly[8] = _mm256_sub_pd(res_poly[8], _mm256_mul_pd(det_l[6], det_r[2]));
            res_poly[9] = _mm256_sub_pd(res_poly[9], _mm256_mul_pd(det_l[6], det_r[3]));
            res_poly[10] =
                _mm256_sub_pd(res_poly[10], _mm256_mul_pd(det_l[6], det_r[4]));
            res_poly[11] =
                _mm256_sub_pd(res_poly[11], _mm256_mul_pd(det_l[6], det_r[5]));
            res_poly[12] =
                _mm256_sub_pd(res_poly[12], _mm256_mul_pd(det_l[6], det_r[6]));
        }
    }
    inline void det6x6(const __m256d matrix[6][6][8], __m256d res_poly[17])
    {
        det3_mul_det3_add_on<0, 1, 5, 2, 3, 4>(matrix, res_poly);
        det3_mul_det3_add_on<0, 2, 5, 1, 3, 4>(matrix, res_poly);
        det3_mul_det3_add_on<0, 3, 5, 1, 2, 4>(matrix, res_poly);
        det3_mul_det3_add_on<0, 4, 5, 1, 2, 3>(matrix, res_poly);
        det3_mul_det3_add_on<1, 2, 5, 0, 3, 4>(matrix, res_poly);
        det3_mul_det3_add_on<1, 3, 5, 0, 2, 4>(matrix, res_poly);
        det3_mul_det3_add_on<1, 4, 5, 0, 2, 3>(matrix, res_poly);
        det3_mul_det3_add_on<2, 3, 5, 0, 1, 4>(matrix, res_poly);
        det3_mul_det3_add_on<2, 4, 5, 0, 1, 3>(matrix, res_poly);
        det3_mul_det3_add_on<3, 4, 5, 0, 1, 2>(matrix, res_poly);
    }

} // namespace opt_onebounce_6x6