#if 0
#include "ostd.h" // For syntax highlighting.
#endif

// Natural logarithm
float32 ln32(float32 x);
float64 ln64(float64 x);
u64 powu(u64 x, u64 e);

#ifdef OSTD_IMPL

float32 ln32(float32 x) {
    u32 bx = * (u32 *) (&x);
    u32 ex = bx >> 23;
    s32 t = (s32)ex-(s32)127;
    bx = 1065353216 | (bx & 8388607);
    x = * (float32 *) (&bx);
    return -1.49278f+(2.11263f+(-0.729104f+0.10969f*x)*x)*x+0.6931471806f*(float32)t;
}

float64 ln64(float64 x) {
    u64 bx = *(u64 *)(&x); // Read float64 bits
    u64 ex = bx >> 52; // Extract exponent (11 bits)
    s32 t = (s32)ex - 1023; // Adjust for float64 bias
    bx = 4607182418800017408ULL | (bx & 4503599627370495ULL); // Normalize mantissa
    x = *(float64 *)(&bx);
    return -1.49278 + (2.11263 + (-0.729104 + 0.10969 * x) * x) * x + 0.6931471806 * t;
}

u64 powu(u64 x, u64 e) {
    u64 result = x;
    for (u64 i = 0; i < e; i += 1) {
        result *= x;
    }
    return result;
}

typedef union float4x32 {
    struct { f32 x; f32 y; f32 z; f32 w; } XXX;
} float4x32;

typedef float4x32 float4;

#endif // OSTD_IMPL

