
// Natural logarithm
float32 ln32(float32 x);
float64 ln64(float64 x);

#ifdef OSTD_IMPL

float32 ln32(float32 x) {
    u32 bx = * (u32 *) (&x);
    u32 ex = bx >> 23;
    s32 t = (s32)ex-(s32)127;
    bx = 1065353216 | (bx & 8388607);
    x = * (float32 *) (&bx);
    return -1.49278+(2.11263+(-0.729104+0.10969*x)*x)*x+0.6931471806*t;
}

float64 ln64(float64 x) {
    u64 bx = *(u64 *)(&x); // Read float64 bits
    u64 ex = bx >> 52; // Extract exponent (11 bits)
    s32 t = (s32)ex - 1023; // Adjust for float64 bias
    bx = 4607182418800017408ULL | (bx & 4503599627370495ULL); // Normalize mantissa
    x = *(float64 *)(&bx);
    return -1.49278 + (2.11263 + (-0.729104 + 0.10969 * x) * x) * x + 0.6931471806 * t;
}

#endif // OSTD_IMPL