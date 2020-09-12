#include <emmintrin.h>
#include <immintrin.h>
#include <stdio.h>

int main()
{
    __m256i fls = _mm256_setr_epi32(1, 2, 3, 4, 5, 6, 7, 8);
    __m256i ins;
    __m256i res;
    ins = _mm256_setr_epi32(1,2,3,4,5,6,7,8);
    res = _mm256_mullo_epi32(ins, fls);
    const int32_t *p = (const int32_t *)&res;
    res = _mm256_add_epi32(res, _mm256_srli_si256(res, 8));
    printf("%d %d %d %d %d %d %d %d\n", p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);

    res = _mm256_add_epi32(res, _mm256_srli_si256(res, 4));
    printf("%d %d %d %d %d %d %d %d\n", p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
    printf("%d\n", p[0]+p[4]);
    const int32_t *q = (const int32_t *)&fls;
    printf("%d %d %d %d", q[0], q[1], q[2], q[3]);
}
