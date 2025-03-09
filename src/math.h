#ifndef _MATH_H
#define _MATH_H

#ifndef _BASE_H
#include "base.h"
#endif // _BASE_H

#include "trig_tables.h"

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wbad-function-cast"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
#pragma clang diagnostic ignored "-Wbad-function-cast"
#endif // __clang__

#define clamp(x, a, b) (min(max((x), (a)), (b)))

#define abs(x) ((x) < 0 ? -(x) : (x))

#define PI 3.141592653589793
#define TAU (PI*2)

unit_local inline f32 lerp32(f32 a, f32 b, f32 t) {
    return a + (b-a)*t;
}
unit_local inline f64 lerp64(f64 a, f64 b, f64 t) {
    return a + (b-a)*t;
}

unit_local inline f32 floor32(f32 f) {
    return (f32)((f) < 0 ? (s64)(f) - 1 : (s64)(f));
}
unit_local inline f32 ceil32(f32 f) {
    return (f32)((f) == (f32)(s64)(f) ? (s64)(f) : (f) > 0 ? (s64)(f) + 1 : (s64)(f));
}
unit_local inline f64 floor64(f64 f) {
    return (f64)((f) < 0 ? (s64)(f) - 1 : (s64)(f));
}
unit_local inline f64 ceil64(f64 f) {
    return (f64)((f) == (f64)(s64)(f) ? (s64)(f) : (f) > 0 ? (s64)(f) + 1 : (s64)(f));
}

#define trig_lookup(t, f) do { \
    s64 c = sizeof(t) / sizeof(f64); \
    f64 norm_index = (f) * (f64)c; \
    s64 ilo = (s64)floor64(norm_index); \
    s64 ihi = (s64)ceil64(norm_index); \
    if (ihi >= c) return t[0]; \
    f64 t_frac = norm_index - (f64)ilo;\
    return lerp64(t[ilo], t[ihi], t_frac); \
} while (0)


unit_local inline float64 fmod_cycling(float64 x, float64 y) {
    if (y == 0.0) {
        return 0.0;
    }
    float64 n = (int)(x / y);
    return x - n * y;
}

unit_local inline float64 sin(float64 x) {
    if (x == 0.0) return 0.0;
    x = fmod_cycling(x, TAU);
    trig_lookup(sine_table, x/TAU);
}
unit_local inline float64 asin(float64 x) {
    if (x == 0.0) return 0.0;
    x = clamp(x, -1.0, 1.0);
    trig_lookup(asine_table, ((x+1.0)/2.0)/TAU);
}
unit_local inline float64 cos(float64 x) {
    if (x == 0.0) return 1.0;
    x = fmod_cycling(x, TAU);
    trig_lookup(cosine_table, x/TAU);
}
unit_local inline float64 acos(float64 x) {
    if (x == 1.0) return 0.0;
    x = clamp(x, -1.0, 1.0);
    trig_lookup(acosine_table, ((x+1.0)/2.0)/TAU);
}
unit_local inline float64 tan(float64 x) {
    x = fmod_cycling(x, TAU);
    s64 i = (s64)((x/TAU) * (f64)(sizeof(tan_table)/sizeof(float64)));
    if (i >= (s64)(sizeof(tan_table)/sizeof(float64))) return tan_table[0];
    return tan_table[i];
}
unit_local inline float64 atan(float64 x) {
    if (x == 0.0) return 0.0;
    float64 theta = (x < 1.0 && x > -1.0) ? x : (x > 0.0 ? PI / 2 : -PI / 2);
    
    for (int i = 0; i < 5; ++i) { 
        float64 sin_theta = sin(theta);
        float64 cos_theta = cos(theta);
        float64 tan_theta = sin_theta / cos_theta;
        
        theta -= (tan_theta - x) / (1.0 + tan_theta * tan_theta);
    }
    
    return theta;
}

unit_local inline float64 atan2(float64 y, float64 x) {
    return (x > 0) ? atan(y / x) :
           (x < 0 && y >= 0) ? atan(y / x) + PI :
           (x < 0 && y < 0) ? atan(y / x) - PI :
           (y > 0) ? PI / 2 :
           (y < 0) ? -PI / 2 : 0.0;
}

#define f2_expand(v) (v).x, (v).y
#define f3_expand(v) (v).x, (v).y, (v).z
#define f4_expand(v) (v).x, (v).y, (v).z, (v).w

#define f2 f2x32
#define f3 f3x32
#define f4 f4x32

#define f2_scalar f2x32_scalar
#define f3_scalar f3x32_scalar
#define f4_scalar f4x32_scalar

#define f2_one  f2x32_one
#define f3_one  f3x32_one
#define f4_one  f4x32_one

#define f2_zero  f2x32_zero
#define f3_zero  f3x32_zero
#define f4_zero  f4x32_zero

#define f2_add  f2x32_add
#define f3_add  f3x32_add
#define f4_add  f4x32_add

#define f2_sub  f2x32_sub
#define f3_sub  f3x32_sub
#define f4_sub  f4x32_sub

#define f2_mul  f2x32_mul
#define f3_mul  f3x32_mul
#define f4_mul  f4x32_mul

#define f2_mulf  f2x32_mulf32
#define f3_mulf  f3x32_mulf32
#define f4_mulf  f4x32_mulf32

#define f2_div  f2x32_div
#define f3_div  f3x32_div
#define f4_div  f4x32_div

#define f2_divf  f2x32_divf32
#define f3_divf  f3x32_divf32
#define f4_divf  f4x32_divf32

#define f2_len  f2x32_len
#define f3_len  f3x32_len
#define f4_len  f4x32_len

#define f2_lensq  f2x32_lensq
#define f3_lensq  f3x32_lensq
#define f4_lensq  f4x32_lensq

#define f2_average  f2x32_average
#define f3_average  f3x32_average
#define f4_average  f4x32_average

#define f2_normalize  f2x32_normalize
#define f3_normalize  f3x32_normalize
#define f4_normalize  f4x32_normalize

#define f2_dot  f2x32_dot
#define f3_dot  f3x32_dot
#define f4_dot  f4x32_dot

#define f2_perp  f2x32_perp
#define f3_cross  f3x32_cross

typedef struct int32x2 {
    int32 x, y;
} int32x2;

typedef struct int32x4 {
    int32 x, y, z, w;
} int32x4;

typedef int32x2 int2;


typedef struct float2x32 {
    float x, y;
} float2x32;
typedef struct float3x32 {
    float x, y, z;
} float3x32;
typedef struct float4x32 {
    float x, y, z, w;
} float4x32;

typedef float2x32 float2;
typedef float3x32 float3;
typedef float4x32 float4;

unit_local inline float32 ln32(float32 x) {
    u32 bx = * (u32 *) (&x);
    u32 ex = bx >> 23;
    s32 t = (s32)ex-(s32)127;
    bx = 1065353216 | (bx & 8388607);
    x = * (float32 *) (&bx);
    return -1.49278f+(2.11263f+(-0.729104f+0.10969f*x)*x)*x+0.6931471806f*(float32)t;
}
unit_local inline float64 ln64(float64 x) {
    u64 bx = *(u64 *)(&x);
    u64 ex = bx >> 52;
    s32 t = (s32)ex - 1023;
    bx = 4607182418800017408ULL | (bx & 4503599627370495ULL);
    x = *(float64 *)(&bx);
    return -1.49278 + (2.11263 + (-0.729104 + 0.10969 * x) * x) * x + 0.6931471806 * t;
}

unit_local inline u64 powu(u64 x, u64 e) {
    if (e == 0) return 1;
    u64 result = x;
    for (u64 i = 0; i < e-1; i += 1) {
        result *= x;
    }
    return result;
}
unit_local inline f64 powf64(f64 x, f64 e) {
    if (e == 0) return 1;
    f64 result = x;
    for (f64 i = 0; i < e-1; i += 1) {
        result *= x;
    }
    return result;
}

unit_local inline float32 sqrt32(float32 n) {
    if (n < 0.0f) {
        return -1.0f;
    }
    if (n == 0.0f) {
        return 0.0f;
    }

    float32 x = n;
    float32 tolerance = 0.000001f;
    float32 delta;

    do {
        float32 next_x = 0.5f * (x + n / x);
        delta = next_x - x;
        if (delta < 0.0f) {
            delta = -delta;
        }
        x = next_x;
    } while (delta > tolerance);

    return x;
}

unit_local inline float64 sqrt64(float64 n) {
    if (n < 0.0) {
        return -1.0;
    }
    if (n == 0.0) {
        return 0.0;
    }

    float64 x = n;
    float64 tolerance = 0.000001;
    float64 delta;

    do {
        float64 next_x = 0.5 * (x + n / x);
        delta = next_x - x;
        if (delta < 0.0) {
            delta = -delta;
        }
        x = next_x;
    } while (delta > tolerance);

    return x;
}

unit_local inline float2x32 f2x32(float32 x, float32 y)                       { return (float2x32){x, y}; }
unit_local inline float3x32 f3x32(float32 x, float32 y, float32 z)            { return (float3x32){x, y, z}; }
unit_local inline float4x32 f4x32(float32 x, float32 y, float32 z, float32 w) { return (float4x32){x, y, z, w}; }

unit_local inline float2x32 f2x32_scalar(float32 a) { return (float2x32){a, a}; }
unit_local inline float3x32 f3x32_scalar(float32 a) { return (float3x32){a, a, a}; }
unit_local inline float4x32 f4x32_scalar(float32 a) { return (float4x32){a, a, a, a}; }

unit_local const float2x32 f2x32_one = {1, 1};
unit_local const float3x32 f3x32_one = {1, 1, 1};
unit_local const float4x32 f4x32_one = {1, 1, 1, 1};

unit_local const float2x32 f2x32_zero = {0, 0};
unit_local const float3x32 f3x32_zero = {0, 0, 0};
unit_local const float4x32 f4x32_zero = {0, 0, 0, 0};

unit_local inline float2x32 f2x32_add(float2x32 a, float2x32 b)  { return f2x32(a.x+b.x, a.y+b.y); }
unit_local inline float3x32 f3x32_add(float3x32 a, float3x32 b)  { return f3x32(a.x+b.x, a.y+b.y, a.z+b.z); }
unit_local inline float4x32 f4x32_add(float4x32 a, float4x32 b)  { return f4x32(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w); }

unit_local inline float2x32 f2x32_sub(float2x32 a, float2x32 b)  { return f2x32(a.x-b.x, a.y-b.y); }
unit_local inline float3x32 f3x32_sub(float3x32 a, float3x32 b)  { return f3x32(a.x-b.x, a.y-b.y, a.z-b.z); }
unit_local inline float4x32 f4x32_sub(float4x32 a, float4x32 b)  { return f4x32(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w); }

unit_local inline float2x32 f2x32_mul(float2x32 a, float2x32 b)  { return f2x32(a.x*b.x, a.y*b.y); }
unit_local inline float3x32 f3x32_mul(float3x32 a, float3x32 b)  { return f3x32(a.x*b.x, a.y*b.y, a.z*b.z); }
unit_local inline float4x32 f4x32_mul(float4x32 a, float4x32 b)  { return f4x32(a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w); }

unit_local inline float2x32 f2x32_mulf32(float2x32 a, float32 s) { return f2x32_mul(a, f2x32(s, s)); }
unit_local inline float3x32 f3x32_mulf32(float3x32 a, float32 s) { return f3x32_mul(a, f3x32(s, s, s)); }
unit_local inline float4x32 f4x32_mulf32(float4x32 a, float32 s) { return f4x32_mul(a, f4x32(s, s, s, s)); }

unit_local inline float2x32 f2x32_div(float2x32 a, float2x32 b)  { return f2x32(a.x/b.x, a.y/b.y); }
unit_local inline float3x32 f3x32_div(float3x32 a, float3x32 b)  { return f3x32(a.x/b.x, a.y/b.y, a.z/b.z); }
unit_local inline float4x32 f4x32_div(float4x32 a, float4x32 b)  { return f4x32(a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w); }

unit_local inline float2x32 f2x32_divf32(float2x32 a, float32 s) { return f2x32_div(a, f2x32(s, s)); }
unit_local inline float3x32 f3x32_divf32(float3x32 a, float32 s) { return f3x32_div(a, f3x32(s, s, s)); }
unit_local inline float4x32 f4x32_divf32(float4x32 a, float32 s) { return f4x32_div(a, f4x32(s, s, s, s)); }

unit_local inline float32 f2x32_lensq(float2x32 a) { return a.x*a.x + a.y*a.y; }
unit_local inline float32 f3x32_lensq(float3x32 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
unit_local inline float32 f4x32_lensq(float4x32 a) { return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w; }

unit_local inline float32 f2x32_len(float2x32 a) { return sqrt32(a.x*a.x + a.y*a.y); }
unit_local inline float32 f3x32_len(float3x32 a) { return sqrt32(a.x * a.x + a.y * a.y + a.z * a.z); }
unit_local inline float32 f4x32_len(float4x32 a) { return sqrt32(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w); }

unit_local inline float32 f2x32_average(float2x32 a) { return (a.x+a.y)/2.0f; }
unit_local inline float32 f3x32_average(float3x32 a) { return (a.x + a.y + a.z) / 3.0f; }
unit_local inline float32 f4x32_average(float4x32 a) { return (a.x + a.y + a.z + a.w) / 4.0f; }

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
#endif // __clang__

unit_local inline float2x32 f2x32_normalize(float2x32 a) { return f2x32_lensq(a) == 0 ? f2x32_scalar(0) : f2x32_divf32(a, f2x32_len(a)); }
unit_local inline float3x32 f3x32_normalize(float3x32 a) { return f3x32_lensq(a) == 0 ? f3x32_scalar(0) : f3x32_divf32(a, f3x32_len(a)); }
unit_local inline float4x32 f4x32_normalize(float4x32 a) { return f4x32_lensq(a) == 0 ? f4x32_scalar(0) : f4x32_divf32(a, f4x32_len(a)); }

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

unit_local inline float32 f2x32_dot(float2x32 a, float2x32 b) { return a.x * b.x + a.y * b.y; }
unit_local inline float32 f3x32_dot(float3x32 a, float3x32 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
unit_local inline float32 f4x32_dot(float4x32 a, float4x32 b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

unit_local inline float32 f2x32_perp(float2x32 a, float2x32 b) { return (a.x * b.y) - (a.y * b.x); }
unit_local inline float3x32 f3x32_cross(float3x32 a, float3x32 b) { return f3x32((a.y*b.z)-(a.z*b.y), (a.z*b.x)-(a.x*b.z), (a.x*b.y)-(a.y*b.x)); }


// Column major
typedef struct Matrix4 {
    float32 data[4][4];
} Matrix4;

unit_local inline Matrix4 m4_scalar(float32 scalar) {
    Matrix4 m = (Matrix4){0};
    m.data[0][0] = scalar; 
    m.data[1][1] = scalar; 
    m.data[2][2] = scalar; 
    m.data[3][3] = scalar; 
    return m;
}

unit_local inline Matrix4 m4_identity(void) { return m4_scalar(1.0); }

unit_local inline Matrix4 m4_make_translation(float3 translation) {
    Matrix4 m = m4_identity();    
    *(float3*)m.data[3] = translation;
    
    return m;
}

unit_local inline Matrix4 m4_translate(Matrix4 m, float3 translation) {
    m.data[3][0] = translation.x;
    m.data[3][1] = translation.y;
    m.data[3][2] = translation.z;
    return m;
}

unit_local inline float m4_trace(Matrix4 m) {
    float a = m.data[0][0];
    a += m.data[1][1];
    a += m.data[2][2];
    a += m.data[3][3];
    
    return a;
}

unit_local inline Matrix4 m4_add(Matrix4 m0, Matrix4 m1) {
    *(float4*)m0.data[0] = f4_add(*(float4*)m0.data[0], *(float4*)m1.data[0]);
    *(float4*)m0.data[1] = f4_add(*(float4*)m0.data[1], *(float4*)m1.data[1]);
    *(float4*)m0.data[2] = f4_add(*(float4*)m0.data[2], *(float4*)m1.data[2]);
    *(float4*)m0.data[3] = f4_add(*(float4*)m0.data[3], *(float4*)m1.data[3]);
    
    return m0;
}

unit_local inline Matrix4 m4_make_scale(float3 scalars) {
    Matrix4 m = m4_identity();
    *(float4*)m.data[0] = f4_mulf(*(float4*)m.data[0], scalars.x);
    *(float4*)m.data[1] = f4_mulf(*(float4*)m.data[1], scalars.y);
    *(float4*)m.data[2] = f4_mulf(*(float4*)m.data[2], scalars.z);
    
    return m;
}

unit_local inline Matrix4 m4_scalef(Matrix4 m, float32 scalar) {
    *(float4*)m.data[0] = f4_mulf(*(float4*)m.data[0], scalar);
    *(float4*)m.data[1] = f4_mulf(*(float4*)m.data[1], scalar);
    *(float4*)m.data[2] = f4_mulf(*(float4*)m.data[2], scalar);
    *(float4*)m.data[3] = f4_mulf(*(float4*)m.data[3], scalar);
    
    return m;
}
unit_local inline Matrix4 m4_scale(Matrix4 m, float3 scalars) {
    *(float4*)m.data[0] = f4_mulf(*(float4*)m.data[0], scalars.x);
    *(float4*)m.data[1] = f4_mulf(*(float4*)m.data[1], scalars.y);
    *(float4*)m.data[2] = f4_mulf(*(float4*)m.data[2], scalars.z);
    
    return m;
}
unit_local inline Matrix4 m4_scale_f4(Matrix4 m, float4 scalars) {
    *(float4*)m.data[0] = f4_mulf(*(float4*)m.data[0], scalars.x);
    *(float4*)m.data[1] = f4_mulf(*(float4*)m.data[1], scalars.y);
    *(float4*)m.data[2] = f4_mulf(*(float4*)m.data[2], scalars.z);
    *(float4*)m.data[3] = f4_mulf(*(float4*)m.data[3], scalars.w);
    
    return m;
}

unit_local inline Matrix4 m4_make_rotation_x(float rad) {
    float c = (f32)cos((f64)rad);
    float s = (f32)sin((f64)rad);
    return (Matrix4){{
        {  c,  0, -s,  0 },
        {  0,  1,  0,  0 },
        {  0,  0,  c,  0 },
        {  s,  0,  0,  1 },
    }};
}
unit_local inline Matrix4 m4_make_rotation_y(float rad) {
    float c = (f32)cos((f64)rad);
    float s = (f32)sin((f64)rad);
    return (Matrix4){{
        {  1,  0,  0,  0 },
        {  0,  c,  s,  0 },
        {  0, -s,  c,  0 },
        {  0,  0,  0,  1 },
    }};
}
unit_local inline Matrix4 m4_make_rotation_z(float rad) {
    float c = (f32)cos((f64)rad);
    float s = (f32)sin((f64)rad);
    return (Matrix4){{
        {  c,  s,  0,  0 },
        { -s,  c,  0,  0 },
        {  0,  0,  1,  0 },
        {  0,  0,  0,  1 },
    }};
}

unit_local inline Matrix4 m4_transpose(Matrix4 m) {
    Matrix4 tm = m;
    
    // Diagonal is copied over, but swap each side of it
    
    tm.data[0][1] = m.data[1][0];
    tm.data[0][2] = m.data[2][0];
    tm.data[0][3] = m.data[3][0];
    
    tm.data[1][0] = m.data[0][1];
    tm.data[1][2] = m.data[2][1];
    tm.data[1][3] = m.data[3][1];
    
    tm.data[2][0] = m.data[0][2];
    tm.data[2][1] = m.data[1][2];
    tm.data[2][3] = m.data[3][2];
    
    tm.data[3][0] = m.data[0][3];
    tm.data[3][1] = m.data[1][3];
    tm.data[3][2] = m.data[2][3];
    
    return tm;
} 

unit_local inline Matrix4 m4_mulm4(Matrix4 m0, Matrix4 m1) {
/*
        m = m0 * m1
        
        each ij in m should be dot(m0[row:i], m1[col:j])
        
        We transpose m0 so we can read rows trivially (since our matrices are column-major)
*/

    // todo(charlie) very easily vectorized


    Matrix4 tm0 = m4_transpose(m0);
    Matrix4 m;
    
    *(float*)&m.data[0][0] = f4_dot(*(float4*)tm0.data[0], *(float4*)m1.data[0]);
    *(float*)&m.data[0][1] = f4_dot(*(float4*)tm0.data[1], *(float4*)m1.data[0]);
    *(float*)&m.data[0][2] = f4_dot(*(float4*)tm0.data[2], *(float4*)m1.data[0]);
    *(float*)&m.data[0][3] = f4_dot(*(float4*)tm0.data[3], *(float4*)m1.data[0]);
    
    *(float*)&m.data[1][0] = f4_dot(*(float4*)tm0.data[0], *(float4*)m1.data[1]);
    *(float*)&m.data[1][1] = f4_dot(*(float4*)tm0.data[1], *(float4*)m1.data[1]);
    *(float*)&m.data[1][2] = f4_dot(*(float4*)tm0.data[2], *(float4*)m1.data[1]);
    *(float*)&m.data[1][3] = f4_dot(*(float4*)tm0.data[3], *(float4*)m1.data[1]);
    
    *(float*)&m.data[2][0] = f4_dot(*(float4*)tm0.data[0], *(float4*)m1.data[2]);
    *(float*)&m.data[2][1] = f4_dot(*(float4*)tm0.data[1], *(float4*)m1.data[2]);
    *(float*)&m.data[2][2] = f4_dot(*(float4*)tm0.data[2], *(float4*)m1.data[2]);
    *(float*)&m.data[2][3] = f4_dot(*(float4*)tm0.data[3], *(float4*)m1.data[2]);
    
    *(float*)&m.data[3][0] = f4_dot(*(float4*)tm0.data[0], *(float4*)m1.data[3]);
    *(float*)&m.data[3][1] = f4_dot(*(float4*)tm0.data[1], *(float4*)m1.data[3]);
    *(float*)&m.data[3][2] = f4_dot(*(float4*)tm0.data[2], *(float4*)m1.data[3]);
    *(float*)&m.data[3][3] = f4_dot(*(float4*)tm0.data[3], *(float4*)m1.data[3]);
    
    return m;
}

unit_local inline float4 m4_mulf4(Matrix4 m0, float4 m1) {
    Matrix4 tm0 = m4_transpose(m0);
    
    float4 f;
    f.x = f4_dot(*(float4*)tm0.data[0], m1);
    f.y = f4_dot(*(float4*)tm0.data[1], m1);
    f.z = f4_dot(*(float4*)tm0.data[2], m1);
    f.w = f4_dot(*(float4*)tm0.data[3], m1);
    
    return f;
}

// This aren't actually real well-defined mathmatical operations,
// but nevertheless useful and makes sense to a game developer.
// It just fills in the z w components to 0 1 if missing.
// This only makes sense in games.
unit_local inline float3 m4_mulf3_trunc(Matrix4 m0, float3 m1) {
    Matrix4 tm0 = m4_transpose(m0);
    
    float3 f;
    f.x = f4_dot(*(float4*)tm0.data[0], f4(m1.x, m1.y, m1.z, 1.0f));
    f.y = f4_dot(*(float4*)tm0.data[1], f4(m1.x, m1.y, m1.z, 1.0f));
    f.z = f4_dot(*(float4*)tm0.data[2], f4(m1.x, m1.y, m1.z, 1.0f));
    
    return f;
} 
unit_local inline float2 m4_mulf2_trunc(Matrix4 m0, float2 m1) {
    Matrix4 tm0 = m4_transpose(m0);
    
    float2 f;
    f.x = f4_dot(*(float4*)tm0.data[0], f4(m1.x, m1.y, 0.0f, 1.0f));
    f.y = f4_dot(*(float4*)tm0.data[1], f4(m1.x, m1.y, 0.0f, 1.0f));
    
    return f;
} 

unit_local inline f64 get_power_of_two_f64(f64 x, u64 exp) {
    return x * (f64)(1ULL << exp);
}

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

#endif //_MATH_H
