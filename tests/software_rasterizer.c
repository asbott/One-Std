


#define OSTD_IMPL
#define OSTD_NO_GRAPHICS
#include "../src/ostd.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#if COMPILER_FLAGS & COMPILER_FLAG_MSC
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif

int main(void) {

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
    
    //verts[0] = m4_mulf2_trunc(m4_make_scale(f3(1.0f, 2.5f, 1.0f)), verts[0]);
    //verts[1] = m4_mulf2_trunc(m4_make_scale(f3(1.0f, 2.5f, 1.0f)), verts[1]);
    //verts[2] = m4_mulf2_trunc(m4_make_scale(f3(1.0f, 2.5f, 1.0f)), verts[2]);
    
    //verts[0] = m4_mulf2_trunc(m4_make_translation(f3(-0.1f, -0.3f, 0)), verts[0]);
    //verts[1] = m4_mulf2_trunc(m4_make_translation(f3(-0.1f, -0.3f, 0)), verts[1]);
    //verts[2] = m4_mulf2_trunc(m4_make_translation(f3(-0.1f, -0.3f, 0)), verts[2]);
    
    float target_frametime = 1.0f/60.0f;
    
    
    u64 vertex_count = sizeof(verts)/sizeof(float2);
    
    float r = 0;

	while (!surface_should_close(surface)) {

	    Physical_Monitor monitor;
	    if (surface_get_monitor(surface, &monitor)) {
	    	target_frametime = (float)monitor.refresh_rate/1.0f;
	    }
	    
		s64 width, height;
		assert(surface_get_framebuffer_size(surface, &width, &height));

		u32 *pixels = (u32*)surface_map_pixels(surface);
		assert(pixels);

		memset(pixels, 0x00, (u64)(width*height*4));

		float frag_x = (2.0f/(float)width);
		float frag_y = (1.0f/(float)height);
		//float frag = frag_x*frag_y;

		s64 hw = width/2;
		s64 hh = height/2;
		
		r += target_frametime*0.0001;
		
		float2 tri0 = m4_mulf2_trunc(m4_make_rotation_z(r), (float2){ -.25f,-.25f });
        float2 tri1 = m4_mulf2_trunc(m4_make_rotation_z(r), (float2){  0.f,  .25f });
        float2 tri2 = m4_mulf2_trunc(m4_make_rotation_z(r), (float2){  .25f,-.25f });
		
		verts[0] = tri0;
	    verts[1] = tri1;
	    verts[2] = tri2;
	    
	    

		for (u64 i = 0; i+2 < vertex_count; i += 3) {
			float2 p0 = verts[i+0];
			float2 p1 = verts[i+1];
			float2 p2 = verts[i+2];
			
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
			
			float min_x = min(p0.x, min(p1.x, p2.x));
			float max_x = max(p0.x, max(p1.x, p2.x));
			float min_y = min(p0.y, min(p1.y, p2.y));
			float max_y = max(p0.y, max(p1.y, p2.y));
			
			
			float4 sl = (float4){0};
			sl.x = min_x;
			sl.z = max_x;
			
			// Scan line vector
			float2 slv = (float2) { max_x-min_x, 0 };
			
			for (float y = min_y; y < max_y; y += frag_y) {
			
				float2 intersections[2] = {0};
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
					intersections[intersection_count++] = (float2) { min_x+t0*slv.x, y*t0+slv.y };
				}
				if (t1 >= 0 && t1 <= 1.0f && u1 >= 0 && u1 <= 1.0f) {
					intersections[intersection_count++] = (float2) { min_x+t1*slv.x, y*t1+slv.y };
				}
				if (t2 >= 0 && t2 <= 1.0f && u2 >= 0 && u2 <= 1.0f) {
					//assert(intersection_count == 1);
					intersections[intersection_count++] = (float2) { min_x+t2*slv.x, y*t2+slv.y };
				}
			
				if (intersection_count == 2) {
					if (intersections[0].x > intersections[1].x) {
						float2 temp = intersections[0];
						intersections[0] = intersections[1];
						intersections[1] = temp;
					}
					
					for (float x = intersections[0].x; x < intersections[1].x; x += frag_x) {
						s64 vpx = (s64)(x*(float)(hw))+hw;
						s64 vpy = (s64)(y*(float)(hh))+hh;
						
						pixels[vpy*width+vpx] = 0xffffffff;
					}
				}
			
				/*for (float x = min_x; x < max_x; x += frag_x) {
					
					float2 p = (float2){x, y};
					float2 w0 = f2_sub(p,p0);
					float2 w1 = f2_sub(p,p1);
					float2 w2 = f2_sub(p,p2);
					
					float c0 = v0.x*w0.y - w0.x*v0.y;
					float c1 = v1.x*w1.y - w1.x*v1.y;
					float c2 = v2.x*w2.y - w2.x*v2.y;
					
					if ((c0 <= 0.0f && c1 <= 0.0f && c2 <= 0.0f) || (c0 >= -0.0f && c1 >= -0.0f && c2 >= -0.0f)) {
						s64 vpx = (s64)(x*(float)(hw))+hw;
						s64 vpy = (s64)(y*(float)(hh))+hh;
						
						pixels[vpy*width+vpx] = 0xffffffff;
					}
				}*/
			}
		}

		// This waits exactly until vblank happened, letting you do 100% smooth frame pacing.
		sys_wait_vertical_blank(monitor);
		surface_blit_pixels(surface);


		surface_poll_events(surface);
	}

	return 0;
}

