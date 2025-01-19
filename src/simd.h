

typedef union __declspec(intrin_type) __declspec(align(16)) xmm {
     float               xmm_f32[4];
     unsigned __int64    xmm_u64[2];
     __int8              xmm_i8[16];
     __int16             xmm_i16[8];
     __int32             xmm_i32[4];
     __int64             xmm_i64[2];
     unsigned __int8     xmm_u8[16];
     unsigned __int16    xmm_u16[8];
     unsigned __int32    xmm_u32[4];
 } xmm;