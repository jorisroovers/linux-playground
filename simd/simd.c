#include "nmmintrin.h" // for SSE4.2
#include <stdio.h>     // needed for printf

// SIMD types:
// __m128 = 4 x 1 float = 4 x 32 bits = "quadfloat"
// __m128i = 4 x 1 int = 4 x 32 bits = "quadint"

// macro to print a __m128 vector
// From: http://www.cs.colostate.edu/~cs675/Exercises/SSETP1/example.c
#define PVEC(a)                                                               \
    {                                                                         \
        float tp[4];                                                          \
        _mm_storeu_ps(tp, a);                                                 \
        printf("VEC %7.1f %7.1f %7.1f %7.1f \n", tp[0], tp[1], tp[2], tp[3]); \
    }

int main()
{
    __m128 a4 = _mm_set_ps(4.0f, 4.1f, 4.2f, 4.3f);
    __m128 b4 = _mm_set_ps(1.0f, 1.0f, 1.0f, 1.0f);

    __m128 sum4 = _mm_add_ps(a4, b4);

    PVEC(sum4);

    //The __mm_set_ps and _mm_add_ps keywords are called intrinsics.

}
