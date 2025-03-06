#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wreserved-macro-identifier"
#if defined(_MSC_VER) || defined(__EMSCRIPTEN__)
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif



#include <intrin.h>
#include <immintrin.h>

#undef log

#undef min
#undef max
#undef __crt_va_start
#undef __crt_va_arg
#undef __crt_va_end

#define OSTD_IMPL
#define OSTD_NO_GRAPHICS
#include "../src/ostd.h"
//#include "../ostd_single_header.h"


typedef struct Scanline {
	s16 vpx0;
	s16 vpx1;
	s16 vpy;
	s16 pad;
} Scanline;

int main(void) {
	//sys_set_thread_affinity_mask(sys_get_current_thread(), 1);
	//sys_set_local_process_priority_level(SYS_PRIORITY_HIGH);
	//sys_set_thread_priority_level(sys_get_current_thread(), SYS_PRIORITY_HIGH);

#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
	Surface_Handle surface = sys_make_surface(DEFAULT(Surface_Desc));
	assert(surface);
#else
	Surface_Handle surface = sys_get_surface();
#endif

	

	bool culling = false;

    float2 verts[] = {
        (float2){ -.25f,-.25f },
        (float2){  0.f,  .25f },
        (float2){  .25f,-.25f },

        (float2){ -.25f+0.65f, .25f  },
        (float2){  0.f+0.75f, -.25f  },
        (float2){  .25f+0.75f, .25f  },
    };
    
    u32 colors[] = {
    	0x00ff0000,
    	0x0000ff00,
    	0x000000ff,
    	
    	0x00ff0000,
    	0x0000ff00,
    	0x000000ff,
    };

    float target_frametime = 1.0f/60.0f;


    u64 vertex_count = sizeof(verts)/sizeof(float2);

    float rot = 0;

	f64 start_time = sys_get_seconds_monotonic();
	(void)start_time;
	
	while (!surface_should_close(surface)) {

	    Physical_Monitor monitor;
	    if (surface_get_monitor(surface, &monitor)) {
	    	target_frametime = (float)monitor.refresh_rate/1.0f;
	    }

		s64 width, height;
		assert(surface_get_framebuffer_size(surface, &width, &height));

		u32 *pixels = (u32*)surface_map_pixels(surface);
		assert(pixels);
		assert((u64)pixels % 32 == 0);

		memset(pixels, 0x00, (sys_uint)(width*height*4));

		float frag_x = (2.0f/(float)width);
		float frag_y = (1.0f/(float)height);
		(void)frag_x; (void)frag_y;
		
		//float frag = frag_x*frag_y;

		s32 hw = (s32)width/2;
		s32 hh = (s32)height/2;

		rot += target_frametime*0.00001f;

		float2 tri0 = m4_mulf2_trunc(m4_make_rotation_z(rot), (float2){ -.25f,-.25f });
        float2 tri1 = m4_mulf2_trunc(m4_make_rotation_z(rot), (float2){  0.f,  .25f });
        float2 tri2 = m4_mulf2_trunc(m4_make_rotation_z(rot), (float2){  .25f,-.25f });

		verts[0] = tri0;
	    verts[1] = tri1;
	    verts[2] = tri2;

		Scanline scanlines[1024];
		u64 scanline_count = 0;
		(void)scanlines; (void)scanline_count;
		
		u64 cyc_triangles = 0;
		u64 num_triangles = 0;
		u64 cyc_pixels = 0;
		u64 num_pixels = 0;
		// u64 cyc_scanlines = 0;
		// u64 num_scanlines = 0;
		
		
		float64 tt0 = sys_get_seconds_monotonic();
		u64 cyc_tri0 = __rdtsc();
		for (u64 i = 0; i+2 < vertex_count; i += 3) {
			float2 p0 = verts[i+0];
			float2 p1 = verts[i+1];
			float2 p2 = verts[i+2];
			
			u32 col0 = colors[i+0];
			u32 col1 = colors[i+1];
			u32 col2 = colors[i+2];

			float2 p1_to_p0 = f2_sub(p0, p1);
			float2 p1_to_p2 = f2_sub(p2, p1);

			if (culling) {
				float2 p1_to_p2_perp = f2(-p1_to_p2.y, p1_to_p2.x);
				if (f2_dot(p1_to_p2_perp, p1_to_p0) < 0.0f) {
					continue;
				}
			}


			float2 v0 = f2_sub(p1, p0);
			float2 v1 = p1_to_p2;
			float2 v2 = f2_sub(p0, p2);
			float area = (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);

			float min_x = min(p0.x, min(p1.x, p2.x));
			float max_x = max(p0.x, max(p1.x, p2.x));
			float min_y = min(p0.y, min(p1.y, p2.y));
			float max_y = max(p0.y, max(p1.y, p2.y));


			float4 sl = (float4){0};
			sl.x = min_x;
			sl.z = max_x;

			// Scan line vector
			float2 slv = (float2) { max_x-min_x, 0 };
			(void)slv;

			for (float y = min_y; y < max_y; y += frag_y) {
				//u64 cyc_sl0 = __rdtsc();
				float intersections[2] = {0};
				u64 intersection_count = 0;

				float s_to_v0_perp = slv.x*v0.y-slv.y*v0.x;
				float s_to_v1_perp = slv.x*v1.y-slv.y*v1.x;
				float s_to_v2_perp = slv.x*v2.y-slv.y*v2.x;

				// Vector from start of v0 to start of scanline
				float2 vs0 = (float2){ p0.x-min_x, p0.y-y };
				float2 vs1 = (float2){ p1.x-min_x, p1.y-y };
				float2 vs2 = (float2){ p2.x-min_x, p2.y-y };

				float vs0_to_sl_perp = vs0.x*slv.y-vs0.y*slv.x;
				float vs0_to_v0_perp = vs0.x*v0.y-vs0.y*v0.x;

				float vs1_to_sl_perp = vs1.x*slv.y-vs1.y*slv.x;
				float vs1_to_v1_perp = vs1.x*v1.y-vs1.y*v1.x;

				float vs2_to_sl_perp = vs2.x*slv.y-vs2.y*slv.x;
				float vs2_to_v2_perp = vs2.x*v2.y-vs2.y*v2.x;

				float t0 = vs0_to_v0_perp/s_to_v0_perp;
				float u0 = vs0_to_sl_perp/s_to_v0_perp;

				float t1 = vs1_to_v1_perp/s_to_v1_perp;
				float u1 = vs1_to_sl_perp/s_to_v1_perp;

				float t2 = vs2_to_v2_perp/s_to_v2_perp;
				float u2 = vs2_to_sl_perp/s_to_v2_perp;

				if (t0 >= 0 && t0 <= 1.0f && u0 >= 0 && u0 <= 1.0f) {
					intersections[intersection_count++] = min_x+t0*slv.x;
				}
				if (t1 >= 0 && t1 <= 1.0f && u1 >= 0 && u1 <= 1.0f) {
					intersections[intersection_count++] = min_x+t1*slv.x;
				}
				if (t2 >= 0 && t2 <= 1.0f && u2 >= 0 && u2 <= 1.0f) {
					intersections[intersection_count++] = min_x+t2*slv.x;
				}

				if (intersection_count == 2) {
					float l = intersections[0];
					float r = intersections[1];
					/*if (l > r) {
						float temp = l;
						l = r;
						r = temp;
					}*/

					s32 vpx0 = (s32)(l*(float)(hw))+hw;
					s32 vpx1 = (s32)(r*(float)(hw))+hw;
					s32 vpy  = (s32)(y*(float)(hh))+hh;
					
					
					
					if (vpx0 == vpx1) continue;
					
					// Barycentric coords
					
					float lbar0 = ((p1.x - l) * (p2.y - y) - (p2.x - l) * (p1.y - y)) / area;
			        float lbar1 = ((p2.x - l) * (p0.y - y) - (p0.x - l) * (p2.y - y)) / area;
			        float lbar2 = 1.0f - lbar0 - lbar1;
			        
					float rbar0 = ((p1.x - r) * (p2.y - y) - (p2.x - r) * (p1.y - y)) / area;
			        float rbar1 = ((p2.x - r) * (p0.y - y) - (p0.x - r) * (p2.y - y)) / area;
			        float rbar2 = 1.0f - rbar0 - rbar1;
			
			        u32 lr0 = (u32)(lbar0*(f32)(((col0) & 0x00ff0000) >> 16));
			        u32 lg0 = (u32)(lbar0*(f32)(((col0) & 0x0000ff00) >> 8));
			        u32 lb0 = (u32)(lbar0*(f32)(((col0)  & 0x000000ff) >> 0));
			        
			        u32 lr1 = (u32)(lbar1*(f32)(((col1) & 0x00ff0000) >> 16));
			        u32 lg1 = (u32)(lbar1*(f32)(((col1) & 0x0000ff00) >> 8));
			        u32 lb1 = (u32)(lbar1*(f32)(((col1)  & 0x000000ff) >> 0));
			        
			        u32 lr2 = (u32)(lbar2*(f32)(((col2) & 0x00ff0000) >> 16));
			        u32 lg2 = (u32)(lbar2*(f32)(((col2) & 0x0000ff00) >> 8));
			        u32 lb2 = (u32)(lbar2*(f32)(((col2)  & 0x000000ff) >> 0));
			        
			        
			        u32 rr0 = (u32)(rbar0*(f32)(((col0) & 0x00ff0000) >> 16));
			        u32 rg0 = (u32)(rbar0*(f32)(((col0) & 0x0000ff00) >> 8));
			        u32 rb0 = (u32)(rbar0*(f32)(((col0)  & 0x000000ff) >> 0));
			        
			        u32 rr1 = (u32)(rbar1*(f32)(((col1) & 0x00ff0000) >> 16));
			        u32 rg1 = (u32)(rbar1*(f32)(((col1) & 0x0000ff00) >> 8));
			        u32 rb1 = (u32)(rbar1*(f32)(((col1)  & 0x000000ff) >> 0));
			        
			        u32 rr2 = (u32)(rbar2*(f32)(((col2) & 0x00ff0000) >> 16));
			        u32 rg2 = (u32)(rbar2*(f32)(((col2) & 0x0000ff00) >> 8));
			        u32 rb2 = (u32)(rbar2*(f32)(((col2)  & 0x000000ff) >> 0));

			        s32 lr = (s32)((lr0+lr1+lr2));
			        s32 lg = (s32)((lg0+lg1+lg2));
			        s32 lb = (s32)((lb0+lb1+lb2));
			        
			        s32 rr = (s32)((rr0+rr1+rr2));
			        s32 rg = (s32)((rg0+rg1+rg2));
			        s32 rb = (s32)((rb0+rb1+rb2));
			        
			        f32 pitch = (f32)(vpx1-vpx0);
			        
			        f32 stepr = (f32)(((f32)(rr-lr)/pitch)); 
			        f32 stepg = (f32)(((f32)(rg-lg)/pitch)); 
			        f32 stepb = (f32)(((f32)(rb-lb)/pitch)); 
			        
					if (vpx1 < vpx0) {
						Swap(vpx0, vpx1);
						Swap(lr, rr);
						Swap(lg, rg);
						Swap(lb, rb);
					}
					
					s32 yindex = vpy * (s32)width;
					
					f32 lrf = (f32)lr;
					f32 lgf = (f32)lg;
					f32 lbf = (f32)lb;
					
					volatile u64 cyc_px0 = __rdtsc();
					
#if !(OS_FLAGS & OS_FLAG_WEB)
					__m256 accr256 = _mm256_set_ps(lrf+stepr*7,lrf+stepr*6,lrf+stepr*5,lrf+stepr*4,lrf+stepr*3,lrf+stepr*2,lrf+stepr*1,lrf+stepr*0);
					__m256 accg256 = _mm256_set_ps(lgf+stepg*7,lgf+stepg*6,lgf+stepg*5,lgf+stepg*4,lgf+stepg*3,lgf+stepg*2,lgf+stepg*1,lgf+stepg*0);
					__m256 accb256 = _mm256_set_ps(lbf+stepb*7,lbf+stepb*6,lbf+stepb*5,lbf+stepb*4,lbf+stepb*3,lbf+stepb*2,lbf+stepb*1,lbf+stepb*0);
					
					__m256 stepr256 = _mm256_set1_ps(stepr*8);
					__m256 stepg256 = _mm256_set1_ps(stepg*8);
					__m256 stepb256 = _mm256_set1_ps(stepb*8);
					
					__m256i cmp_vec_base  = _mm256_set_epi32(7, 6, 5, 4, 3, 2, 1, 0);
					
					s32 vpx = vpx0;
					for (; vpx < vpx1; vpx += 8) {
						
						u32 *start = pixels + yindex + vpx;

						__m256i a256 = _mm256_set1_epi32((int)0xff000000);
						
						__m256i r256 = _mm256_cvtps_epi32(accr256);
						// avx 2
						r256 = _mm256_slli_epi32(r256, 16);
						
						
						__m256i g256 = _mm256_cvtps_epi32(accg256);
						// avx 2
						g256 = _mm256_slli_epi32(g256, 8);
						
						
						__m256i b256 = _mm256_cvtps_epi32(accb256);

						__m256i rgba256 = _mm256_or_si256(a256, r256);
						rgba256 = _mm256_or_si256(rgba256, g256);
						rgba256 = _mm256_or_si256(rgba256, b256);
						
						__m256i vpx256 = _mm256_set1_epi32(vpx);
						__m256i cmp_vec = _mm256_add_epi32(cmp_vec_base, vpx256);
						
						__m256i threshold = _mm256_set1_epi32(vpx1);
						
						__m256i mask = _mm256_cmpgt_epi32(threshold, cmp_vec);
						
						_mm256_maskstore_epi32((s32*)start, mask, rgba256);
						
						accr256 = _mm256_add_ps(accr256, stepr256);
						accg256 = _mm256_add_ps(accg256, stepg256);
						accb256 = _mm256_add_ps(accb256, stepb256);
						
						
					}
#else // !(OS_FLAGS & OS_FLAG_WEB)
					v128_t accr = wasm_f32x4_make(lrf + stepr * 0,
				                                  lrf + stepr * 1,
				                                  lrf + stepr * 2,
				                                  lrf + stepr * 3);
				    v128_t accg = wasm_f32x4_make(lgf + stepg * 0,
				                                  lgf + stepg * 1,
				                                  lgf + stepg * 2,
				                                  lgf + stepg * 3);
				    v128_t accb = wasm_f32x4_make(lbf + stepb * 0,
				                                  lbf + stepb * 1,
				                                  lbf + stepb * 2,
				                                  lbf + stepb * 3);
				
				    v128_t stepr128 = wasm_f32x4_splat(stepr * 4);
				    v128_t stepg128 = wasm_f32x4_splat(stepg * 4);
				    v128_t stepb128 = wasm_f32x4_splat(stepb * 4);
				
				    v128_t cmp_vec_base = wasm_i32x4_make(0, 1, 2, 3);
				
				    for (int vpx = vpx0; vpx < vpx1; vpx += 4) {
				        u32 *start = pixels + yindex + vpx;
				
				        v128_t aacc = wasm_i32x4_splat((s32)0xff000000);
				
				        v128_t racc = wasm_i32x4_trunc_sat_f32x4(accr);
				        racc = wasm_i32x4_shl(racc, 16);
				
				        v128_t gacc = wasm_i32x4_trunc_sat_f32x4(accg);
				        gacc = wasm_i32x4_shl(gacc, 8);
				
				        v128_t bacc = wasm_i32x4_trunc_sat_f32x4(accb);
				
				        v128_t rgba = wasm_v128_or(aacc, racc);
				        rgba = wasm_v128_or(rgba, gacc);
				        rgba = wasm_v128_or(rgba, bacc);
				
				        v128_t vpx_vec = wasm_i32x4_splat(vpx);
				        v128_t cmp_vec = wasm_i32x4_add(cmp_vec_base, vpx_vec);
				        v128_t threshold = wasm_i32x4_splat(vpx1);
				
				        v128_t mask = wasm_i32x4_gt(threshold, cmp_vec);
				
				        v128_t dst = wasm_v128_load(start);
				        v128_t allOnes = wasm_i32x4_splat(-1);
				        v128_t not_mask = wasm_v128_xor(mask, allOnes);
				        v128_t blended = wasm_v128_or(wasm_v128_and(mask, rgba),
				                                      wasm_v128_and(not_mask, dst));
				        wasm_v128_store(start, blended);
				
				        accr = wasm_f32x4_add(accr, stepr128);
				        accg = wasm_f32x4_add(accg, stepg128);
				        accb = wasm_f32x4_add(accb, stepb128);
				    }
#endif // (OS_FLAGS & OS_FLAG_WEB)
					volatile u64 cyc_px1 = __rdtsc();
					volatile u64 cyc_px = cyc_px1-cyc_px0;
					cyc_pixels += cyc_px;
					num_pixels += (u64)vpx1-(u64)vpx0;
					
					/*for (; vpx < vpx1; vpx += 1) {
						volatile u64 cyc_px0 = __rdtsc();
						
						pixels[yindex + vpx] 
							= 0xff000000 
							| (((u32)accs[0] << 16)) 
							| (((u32)accs[1] << 8)) 
							| ((u32)accs[2]);
						
						*((f32*)(void*)&accr256 + 7) += *((f32*)(void*)&stepr256 + 7);
						*((f32*)(void*)&accg256 + 7) += *((f32*)(void*)&stepg256 + 7);
						*((f32*)(void*)&accb256 + 7) += *((f32*)(void*)&stepb256 + 7);
						
						volatile u64 cyc_px1 = __rdtsc();
						volatile u64 cyc_px = cyc_px1-cyc_px0;
						cyc_pixels += cyc_px;
						num_pixels += 1;
					}*/
					
				}
				
				//u64 cyc_sl1 = __rdtsc();
				//u64 cyc_sl = cyc_sl1-cyc_sl0;
				//cyc_scanlines += cyc_sl;
				//num_scanlines += 1;
			}
		}
		u64 cyc_tri1 = __rdtsc();
		u64 cyc_tri = cyc_tri1-cyc_tri0;
		cyc_triangles += cyc_tri;
		num_triangles += vertex_count/3;
		
		u64 cyc_avg_triangles = cyc_triangles/num_triangles;
		/*u64 cyc_avg_scanlines = cyc_scanlines/num_scanlines;*/
		f64 cyc_avg_pixels = (f64)cyc_pixels/(f64)num_pixels;
		
		(void)cyc_avg_triangles;
		/*(void)cyc_avg_scanlines;*/
		//(void)cyc_avg_pixels;
		
		print("\n%u triangles: %u per / %u total\n", num_triangles, cyc_avg_triangles, cyc_triangles);
		/*print("%u scanlines: %u per / %u total\n", num_scanlines, cyc_avg_scanlines, cyc_scanlines);*/
		print("%u pixels: %f per / %u total\n", num_pixels, cyc_avg_pixels, cyc_pixels);
		
		float64 tt1 = sys_get_seconds_monotonic();
		float64 ms = (tt1-tt0)*1000.0;
		print("%fms\n", ms);

		sys_wait_vertical_blank(monitor);
		surface_blit_pixels(surface);


		surface_poll_events(surface);
		
#ifdef RUNNING_TESTS
        if (sys_get_seconds_monotonic()-start_time > TESTING_DURATION) {
            surface_close(surface);
        }
#endif // RUNNING_TESTS
	}

	return 0;
}

