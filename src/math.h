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

unit_local inline f32 ln32(f32 x) {
    u32 bx = * (u32 *) (&x);
    u32 ex = bx >> 23;
    s32 t = (s32)ex-(s32)127;
    bx = 1065353216 | (bx & 8388607);
    x = * (f32 *) (&bx);
    return -1.49278f+(2.11263f+(-0.729104f+0.10969f*x)*x)*x+0.6931471806f*(f32)t;
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

unit_local inline f32 sqrt32(f32 n) {
    if (n < 0.0f) {
        return -1.0f;
    }
    if (n == 0.0f) {
        return 0.0f;
    }

    f32 x = n;
    f32 tolerance = 0.000001f;
    f32 delta;

    do {
        f32 next_x = 0.5f * (x + n / x);
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



#define v2_expand(v) (v).x, (v).y
#define v3_expand(v) (v).x, (v).y, (v).z
#define v4_expand(v) (v).x, (v).y, (v).z, (v).w

#define v2(x, y)       (f32v2) {x, y}
#define v3(x, y, z)    (f32v3) {x, y, z}
#define v4(x, y, z, w) (f32v4) {x, y, z, w}

#define v2_scalar f32v2_scalar
#define v3_scalar f32v3_scalar
#define v4_scalar f32v4_scalar

#define v2_one  f32v2_one
#define v3_one  f32v3_one
#define v4_one  f32v4_one

#define v2_zero  f32v2_zero
#define v3_zero  f32v3_zero
#define v4_zero  f32v4_zero

#define v2_add  f32v2_add
#define v3_add  f32v3_add
#define v4_add  f32v4_add

#define v2_sub  f32v2_sub
#define v3_sub  f32v3_sub
#define v4_sub  f32v4_sub

#define v2_mul  f32v2_mul
#define v3_mul  f32v3_mul
#define v4_mul  f32v4_mul

#define v2_mulf  f32v2_mulf32
#define v3_mulf  f32v3_mulf32
#define v4_mulf  f32v4_mulf32

#define v2_div  f32v2_div
#define v3_div  f32v3_div
#define v4_div  f32v4_div

#define v2_divf  f32v2_divf32
#define v3_divf  f32v3_divf32
#define v4_divf  f32v4_divf32

#define v2_len  f32v2_len
#define v3_len  f32v3_len
#define v4_len  f32v4_len

#define v2_lensq  f32v2_lensq
#define v3_lensq  f32v3_lensq
#define v4_lensq  f32v4_lensq

#define v2_average  f32v2_average
#define v3_average  f32v3_average
#define v4_average  f32v4_average

#define v2_normalize  f32v2_normalize
#define v3_normalize  f32v3_normalize
#define v4_normalize  f32v4_normalize

#define v2_dot  f32v2_dot
#define v3_dot  f32v3_dot
#define v4_dot  f32v4_dot

#define v2_perp  f32v2_perp
#define v3_cross  f32v3_cross

typedef struct f32v2 {
    f32 x, y;
} f32v2;
typedef struct f32v3 {
    f32 x, y, z;
} f32v3;
typedef struct f32v4 {
    f32 x, y, z, w;
} f32v4;

unit_local inline f32v2 f32v2_scalar(f32 a) { return (f32v2){a, a}; }
unit_local inline f32v3 f32v3_scalar(f32 a) { return (f32v3){a, a, a}; }
unit_local inline f32v4 f32v4_scalar(f32 a) { return (f32v4){a, a, a, a}; }

unit_local const f32v2 f32v2_one = {1, 1};
unit_local const f32v3 f32v3_one = {1, 1, 1};
unit_local const f32v4 f32v4_one = {1, 1, 1, 1};

unit_local const f32v2 f32v2_zero = {0, 0};
unit_local const f32v3 f32v3_zero = {0, 0, 0};
unit_local const f32v4 f32v4_zero = {0, 0, 0, 0};

unit_local inline f32v2 f32v2_add(f32v2 a, f32v2 b)  { return (f32v2){a.x+b.x, a.y+b.y}; }
unit_local inline f32v3 f32v3_add(f32v3 a, f32v3 b)  { return (f32v3){a.x+b.x, a.y+b.y, a.z+b.z}; }
unit_local inline f32v4 f32v4_add(f32v4 a, f32v4 b)  { return (f32v4){a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w}; }

unit_local inline f32v2 f32v2_sub(f32v2 a, f32v2 b)  { return (f32v2){a.x-b.x, a.y-b.y}; }
unit_local inline f32v3 f32v3_sub(f32v3 a, f32v3 b)  { return (f32v3){a.x-b.x, a.y-b.y, a.z-b.z}; }
unit_local inline f32v4 f32v4_sub(f32v4 a, f32v4 b)  { return (f32v4){a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w}; }

unit_local inline f32v2 f32v2_mul(f32v2 a, f32v2 b)  { return (f32v2){a.x*b.x, a.y*b.y}; }
unit_local inline f32v3 f32v3_mul(f32v3 a, f32v3 b)  { return (f32v3){a.x*b.x, a.y*b.y, a.z*b.z}; }
unit_local inline f32v4 f32v4_mul(f32v4 a, f32v4 b)  { return (f32v4){a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w}; }

unit_local inline f32v2 f32v2_mulf32(f32v2 a, f32 s) { return f32v2_mul(a, (f32v2){s, s}); }
unit_local inline f32v3 f32v3_mulf32(f32v3 a, f32 s) { return f32v3_mul(a, (f32v3){s, s, s}); }
unit_local inline f32v4 f32v4_mulf32(f32v4 a, f32 s) { return f32v4_mul(a, (f32v4){s, s, s, s}); }

unit_local inline f32v2 f32v2_div(f32v2 a, f32v2 b)  { return (f32v2){a.x/b.x, a.y/b.y}; }
unit_local inline f32v3 f32v3_div(f32v3 a, f32v3 b)  { return (f32v3){a.x/b.x, a.y/b.y, a.z/b.z}; }
unit_local inline f32v4 f32v4_div(f32v4 a, f32v4 b)  { return (f32v4){a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w}; }

unit_local inline f32v2 f32v2_divf32(f32v2 a, f32 s) { return f32v2_div(a, (f32v2){s, s}); }
unit_local inline f32v3 f32v3_divf32(f32v3 a, f32 s) { return f32v3_div(a, (f32v3){s, s, s}); }
unit_local inline f32v4 f32v4_divf32(f32v4 a, f32 s) { return f32v4_div(a, (f32v4){s, s, s, s}); }

unit_local inline f32 f32v2_lensq(f32v2 a) { return a.x*a.x + a.y*a.y; }
unit_local inline f32 f32v3_lensq(f32v3 a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
unit_local inline f32 f32v4_lensq(f32v4 a) { return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w; }

unit_local inline f32 f32v2_len(f32v2 a) { return sqrt32(a.x*a.x + a.y*a.y); }
unit_local inline f32 f32v3_len(f32v3 a) { return sqrt32(a.x * a.x + a.y * a.y + a.z * a.z); }
unit_local inline f32 f32v4_len(f32v4 a) { return sqrt32(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w); }

unit_local inline f32 f32v2_average(f32v2 a) { return (a.x+a.y)/2.0f; }
unit_local inline f32 f32v3_average(f32v3 a) { return (a.x + a.y + a.z) / 3.0f; }
unit_local inline f32 f32v4_average(f32v4 a) { return (a.x + a.y + a.z + a.w) / 4.0f; }


typedef struct s32v2 {
    s32 x, y;
} s32v2;
typedef struct s32v3 {
    s32 x, y, z;
} s32v3;
typedef struct s32v4 {
    s32 x, y, z, w;
} s32v4;

typedef struct u32v2 {
    u32 x, y;
} u32v2;
typedef struct u32v3 {
    u32 x, y, z;
} u32v3;
typedef struct u32v4 {
    u32 x, y, z, w;
} u32v4;


#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
#endif // __clang__

unit_local inline f32v2 f32v2_normalize(f32v2 a) { return f32v2_lensq(a) == 0 ? f32v2_scalar(0) : f32v2_divf32(a, f32v2_len(a)); }
unit_local inline f32v3 f32v3_normalize(f32v3 a) { return f32v3_lensq(a) == 0 ? f32v3_scalar(0) : f32v3_divf32(a, f32v3_len(a)); }
unit_local inline f32v4 f32v4_normalize(f32v4 a) { return f32v4_lensq(a) == 0 ? f32v4_scalar(0) : f32v4_divf32(a, f32v4_len(a)); }

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

unit_local inline f32 f32v2_dot(f32v2 a, f32v2 b) { return a.x * b.x + a.y * b.y; }
unit_local inline f32 f32v3_dot(f32v3 a, f32v3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
unit_local inline f32 f32v4_dot(f32v4 a, f32v4 b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

unit_local inline f32 f32v2_perp(f32v2 a, f32v2 b) { return (a.x * b.y) - (a.y * b.x); }
unit_local inline f32v3 f32v3_cross(f32v3 a, f32v3 b) { return (f32v3){(a.y*b.z)-(a.z*b.y), (a.z*b.x)-(a.x*b.z), (a.x*b.y)-(a.y*b.x)}; }


// Column major
typedef union f32m4x4 {
    f32 data[4][4];
    f32v4 cols[4];
} f32m4x4;
typedef f32m4x4 f32m4;

unit_local inline f32m4x4 m4_scalar(f32 scalar) {
    f32m4x4 m = (f32m4x4){0};
    m.data[0][0] = scalar; 
    m.data[1][1] = scalar; 
    m.data[2][2] = scalar; 
    m.data[3][3] = scalar; 
    return m;
}

unit_local inline f32m4x4 m4_identity(void) { return m4_scalar(1.0); }

unit_local inline f32m4x4 m4_make_translation(f32v3 translation) {
    f32m4x4 m = m4_identity();    
    *(f32v3*)m.data[3] = translation;
    
    return m;
}

unit_local inline f32m4x4 m4_translate(f32m4x4 m, f32v3 translation) {
    m.data[3][0] = translation.x;
    m.data[3][1] = translation.y;
    m.data[3][2] = translation.z;
    return m;
}

unit_local inline f32m4x4 m4_add(f32m4x4 m0, f32m4x4 m1) {
    *(f32v4*)m0.data[0] = v4_add(*(f32v4*)m0.data[0], *(f32v4*)m1.data[0]);
    *(f32v4*)m0.data[1] = v4_add(*(f32v4*)m0.data[1], *(f32v4*)m1.data[1]);
    *(f32v4*)m0.data[2] = v4_add(*(f32v4*)m0.data[2], *(f32v4*)m1.data[2]);
    *(f32v4*)m0.data[3] = v4_add(*(f32v4*)m0.data[3], *(f32v4*)m1.data[3]);
    
    return m0;
}

unit_local inline f32m4x4 m4_make_scale(f32v3 scalars) {
    f32m4x4 m = m4_identity();
    *(f32v4*)m.data[0] = v4_mulf(*(f32v4*)m.data[0], scalars.x);
    *(f32v4*)m.data[1] = v4_mulf(*(f32v4*)m.data[1], scalars.y);
    *(f32v4*)m.data[2] = v4_mulf(*(f32v4*)m.data[2], scalars.z);
    
    return m;
}

unit_local inline f32m4x4 m4_scalef(f32m4x4 m, f32 scalar) {
    *(f32v4*)m.data[0] = v4_mulf(*(f32v4*)m.data[0], scalar);
    *(f32v4*)m.data[1] = v4_mulf(*(f32v4*)m.data[1], scalar);
    *(f32v4*)m.data[2] = v4_mulf(*(f32v4*)m.data[2], scalar);
    *(f32v4*)m.data[3] = v4_mulf(*(f32v4*)m.data[3], scalar);
    
    return m;
}
unit_local inline f32m4x4 m4_scale(f32m4x4 m, f32v3 scalars) {
    *(f32v4*)m.data[0] = v4_mulf(*(f32v4*)m.data[0], scalars.x);
    *(f32v4*)m.data[1] = v4_mulf(*(f32v4*)m.data[1], scalars.y);
    *(f32v4*)m.data[2] = v4_mulf(*(f32v4*)m.data[2], scalars.z);
    
    return m;
}
unit_local inline f32m4x4 m4_scale_v4(f32m4x4 m, f32v4 scalars) {
    *(f32v4*)m.data[0] = v4_mulf(*(f32v4*)m.data[0], scalars.x);
    *(f32v4*)m.data[1] = v4_mulf(*(f32v4*)m.data[1], scalars.y);
    *(f32v4*)m.data[2] = v4_mulf(*(f32v4*)m.data[2], scalars.z);
    *(f32v4*)m.data[3] = v4_mulf(*(f32v4*)m.data[3], scalars.w);
    
    return m;
}

unit_local inline f32m4x4 m4_make_rotation_x(float rad) {
    float c = (f32)cos((f64)rad);
    float s = (f32)sin((f64)rad);
    return (f32m4x4){{
        {  c,  0, -s,  0 },
        {  0,  1,  0,  0 },
        {  0,  0,  c,  0 },
        {  s,  0,  0,  1 },
    }};
}
unit_local inline f32m4x4 m4_make_rotation_y(float rad) {
    float c = (f32)cos((f64)rad);
    float s = (f32)sin((f64)rad);
    return (f32m4x4){{
        {  1,  0,  0,  0 },
        {  0,  c,  s,  0 },
        {  0, -s,  c,  0 },
        {  0,  0,  0,  1 },
    }};
}
unit_local inline f32m4x4 m4_make_rotation_z(float rad) {
    float c = (f32)cos((f64)rad);
    float s = (f32)sin((f64)rad);
    return (f32m4x4){{
        {  c,  s,  0,  0 },
        { -s,  c,  0,  0 },
        {  0,  0,  1,  0 },
        {  0,  0,  0,  1 },
    }};
}

unit_local inline f32m4x4 m4_make_perspective_left_handed(f32 fov_rad, f32 aspect_ratio, f32 n, f32 f) {
    f32m4x4 proj = (f32m4x4){0};

    f32 s = 1.0f / (f32)tan((f64)fov_rad * 0.5);
    proj.cols[0].x = 1/(aspect_ratio*s);
    proj.cols[1].y = 1/s;
    proj.cols[2].z = f/(f - n);
    proj.cols[2].w = 1.0f;
    proj.cols[3].z = -n*f/(f - n);

    return proj;
}

unit_local inline f32m4x4 m4_transpose(f32m4x4 m) {
    f32m4x4 tm = m;
    
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

unit_local inline f32m4x4 m4_mulm4(f32m4x4 m0, f32m4x4 m1) {
/*
        m = m0 * m1
        
        each ij in m should be dot(m0[row:i], m1[col:j])
        
        We transpose m0 so we can read rows trivially (since our matrices are column-major)
*/

    // todo(charlie) very easily vectorized


    f32m4x4 tm0 = m4_transpose(m0);
    f32m4x4 m;
    
    *(float*)&m.data[0][0] = v4_dot(*(f32v4*)tm0.data[0], *(f32v4*)m1.data[0]);
    *(float*)&m.data[0][1] = v4_dot(*(f32v4*)tm0.data[1], *(f32v4*)m1.data[0]);
    *(float*)&m.data[0][2] = v4_dot(*(f32v4*)tm0.data[2], *(f32v4*)m1.data[0]);
    *(float*)&m.data[0][3] = v4_dot(*(f32v4*)tm0.data[3], *(f32v4*)m1.data[0]);
    
    *(float*)&m.data[1][0] = v4_dot(*(f32v4*)tm0.data[0], *(f32v4*)m1.data[1]);
    *(float*)&m.data[1][1] = v4_dot(*(f32v4*)tm0.data[1], *(f32v4*)m1.data[1]);
    *(float*)&m.data[1][2] = v4_dot(*(f32v4*)tm0.data[2], *(f32v4*)m1.data[1]);
    *(float*)&m.data[1][3] = v4_dot(*(f32v4*)tm0.data[3], *(f32v4*)m1.data[1]);
    
    *(float*)&m.data[2][0] = v4_dot(*(f32v4*)tm0.data[0], *(f32v4*)m1.data[2]);
    *(float*)&m.data[2][1] = v4_dot(*(f32v4*)tm0.data[1], *(f32v4*)m1.data[2]);
    *(float*)&m.data[2][2] = v4_dot(*(f32v4*)tm0.data[2], *(f32v4*)m1.data[2]);
    *(float*)&m.data[2][3] = v4_dot(*(f32v4*)tm0.data[3], *(f32v4*)m1.data[2]);
    
    *(float*)&m.data[3][0] = v4_dot(*(f32v4*)tm0.data[0], *(f32v4*)m1.data[3]);
    *(float*)&m.data[3][1] = v4_dot(*(f32v4*)tm0.data[1], *(f32v4*)m1.data[3]);
    *(float*)&m.data[3][2] = v4_dot(*(f32v4*)tm0.data[2], *(f32v4*)m1.data[3]);
    *(float*)&m.data[3][3] = v4_dot(*(f32v4*)tm0.data[3], *(f32v4*)m1.data[3]);
    
    return m;
}

unit_local inline f32v4 m4_mulv4(f32m4x4 m0, f32v4 m1) {
    f32m4x4 tm0 = m4_transpose(m0);
    
    f32v4 f;
    f.x = v4_dot(*(f32v4*)tm0.data[0], m1);
    f.y = v4_dot(*(f32v4*)tm0.data[1], m1);
    f.z = v4_dot(*(f32v4*)tm0.data[2], m1);
    f.w = v4_dot(*(f32v4*)tm0.data[3], m1);
    
    return f;
}

unit_local inline f32v3 m4_mulv3_trunc(f32m4x4 m0, f32v3 m1) {
    f32m4x4 tm0 = m4_transpose(m0);
    
    f32v3 f;
    f.x = v4_dot(*(f32v4*)tm0.data[0], v4(m1.x, m1.y, m1.z, 1.0f));
    f.y = v4_dot(*(f32v4*)tm0.data[1], v4(m1.x, m1.y, m1.z, 1.0f));
    f.z = v4_dot(*(f32v4*)tm0.data[2], v4(m1.x, m1.y, m1.z, 1.0f));
    
    return f;
} 
unit_local inline f32v2 m4_mulv2_trunc(f32m4x4 m0, f32v2 m1) {
    f32m4x4 tm0 = m4_transpose(m0);
    
    f32v2 f;
    f.x = v4_dot(*(f32v4*)tm0.data[0], v4(m1.x, m1.y, 0.0f, 1.0f));
    f.y = v4_dot(*(f32v4*)tm0.data[1], v4(m1.x, m1.y, 0.0f, 1.0f));
    
    return f;
} 

unit_local inline f64 get_power_of_two_f64(f64 x, u64 exp) {
    return x * (f64)(1ULL << exp);
}

// Column major
typedef union f32m3x3 {
    f32 data[3][3];
    f32v3 cols[3];
} f32m3x3;
typedef f32m3x3 f32m3;

unit_local inline f32m3x3 m3_scalar(f32 scalar) {
    f32m3x3 m = (f32m3x3){0};
    m.data[0][0] = scalar;
    m.data[1][1] = scalar;
    m.data[2][2] = scalar;
    return m;
}

unit_local inline f32m3x3 m3_identity(void) { return m3_scalar(1.0f); }

unit_local inline f32m3x3 m3_make_translation(f32v2 translation) {
    f32m3x3 m = m3_identity();
    m.data[2][0] = translation.x;
    m.data[2][1] = translation.y;
    return m;
}

unit_local inline f32m3x3 m3_translate(f32m3x3 m, f32v2 translation) {
    m.data[2][0] = translation.x;
    m.data[2][1] = translation.y;
    return m;
}

unit_local inline f32m3x3 m3_add(f32m3x3 m0, f32m3x3 m1) {
    *(f32v3*)m0.data[0] = v3_add(*(f32v3*)m0.data[0], *(f32v3*)m1.data[0]);
    *(f32v3*)m0.data[1] = v3_add(*(f32v3*)m0.data[1], *(f32v3*)m1.data[1]);
    *(f32v3*)m0.data[2] = v3_add(*(f32v3*)m0.data[2], *(f32v3*)m1.data[2]);
    return m0;
}

unit_local inline f32m3x3 m3_make_scale(f32v2 scalars) {
    f32m3x3 m = m3_identity();
    *(f32v3*)m.data[0] = v3_mulf(*(f32v3*)m.data[0], scalars.x);
    *(f32v3*)m.data[1] = v3_mulf(*(f32v3*)m.data[1], scalars.y);
    return m;
}

unit_local inline f32m3x3 m3_scalef(f32m3x3 m, f32 scalar) {
    *(f32v3*)m.data[0] = v3_mulf(*(f32v3*)m.data[0], scalar);
    *(f32v3*)m.data[1] = v3_mulf(*(f32v3*)m.data[1], scalar);
    *(f32v3*)m.data[2] = v3_mulf(*(f32v3*)m.data[2], scalar);
    return m;
}

unit_local inline f32m3x3 m3_scale(f32m3x3 m, f32v2 scalars) {
    *(f32v3*)m.data[0] = v3_mulf(*(f32v3*)m.data[0], scalars.x);
    *(f32v3*)m.data[1] = v3_mulf(*(f32v3*)m.data[1], scalars.y);
    return m;
}

unit_local inline f32m3x3 m3_make_rotation(f32v3 axis, f32 rad) {
    f32v3 u = v3_normalize(axis);
    float c  = (f32)cos((f64)rad);
    float s  = (f32)sin((f64)rad);
    float oc = 1.0f - c;
    
    return (f32m3x3){{
        { c + u.x * u.x * oc,        u.x * u.y * oc + u.z * s,  u.x * u.z * oc - u.y * s },
        { u.x * u.y * oc - u.z * s,  c + u.y * u.y * oc,        u.y * u.z * oc + u.x * s },
        { u.x * u.z * oc + u.y * s,  u.y * u.z * oc - u.x * s,  c + u.z * u.z * oc }
    }};
}

unit_local inline f32m3x3 m3_make_rotation_z(float rad) {
    float c = (f32)cos((f64)rad);
    float s = (f32)sin((f64)rad);
    return (f32m3x3){{
        {  c,  s,  0 },
        { -s,  c,  0 },
        {  0,  0,  1 },
    }};
}

unit_local inline f32m3x3 m3_transpose(f32m3x3 m) {
    f32m3x3 tm = m;
    
    tm.data[0][1] = m.data[1][0];
    tm.data[0][2] = m.data[2][0];
    
    tm.data[1][0] = m.data[0][1];
    tm.data[1][2] = m.data[2][1];
    
    tm.data[2][0] = m.data[0][2];
    tm.data[2][1] = m.data[1][2];
    
    return tm;
}

unit_local inline f32m3x3 m3_mulm3(f32m3x3 m0, f32m3x3 m1) {
    f32m3x3 tm0 = m3_transpose(m0);
    f32m3x3 m;
    
    m.data[0][0] = v3_dot(*(f32v3*)tm0.data[0], *(f32v3*)m1.data[0]);
    m.data[0][1] = v3_dot(*(f32v3*)tm0.data[1], *(f32v3*)m1.data[0]);
    m.data[0][2] = v3_dot(*(f32v3*)tm0.data[2], *(f32v3*)m1.data[0]);
    
    m.data[1][0] = v3_dot(*(f32v3*)tm0.data[0], *(f32v3*)m1.data[1]);
    m.data[1][1] = v3_dot(*(f32v3*)tm0.data[1], *(f32v3*)m1.data[1]);
    m.data[1][2] = v3_dot(*(f32v3*)tm0.data[2], *(f32v3*)m1.data[1]);
    
    m.data[2][0] = v3_dot(*(f32v3*)tm0.data[0], *(f32v3*)m1.data[2]);
    m.data[2][1] = v3_dot(*(f32v3*)tm0.data[1], *(f32v3*)m1.data[2]);
    m.data[2][2] = v3_dot(*(f32v3*)tm0.data[2], *(f32v3*)m1.data[2]);
    
    return m;
}

unit_local inline f32v3 m3_mulv3(f32m3x3 m, f32v3 v) {
    f32m3x3 tm = m3_transpose(m);
    
    f32v3 f;
    f.x = v3_dot(*(f32v3*)tm.data[0], v);
    f.y = v3_dot(*(f32v3*)tm.data[1], v);
    f.z = v3_dot(*(f32v3*)tm.data[2], v);
    
    return f;
}

unit_local inline f32v2 m3_mulv2_trunc(f32m3x3 m, f32v2 v) {
    f32m3x3 tm = m3_transpose(m);
    
    f32v2 f;
    f.x = v3_dot(*(f32v3*)tm.data[0], v3(v.x, v.y, 1.0f));
    f.y = v3_dot(*(f32v3*)tm.data[1], v3(v.x, v.y, 1.0f));
    
    return f;
}


#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

#endif //_MATH_H
