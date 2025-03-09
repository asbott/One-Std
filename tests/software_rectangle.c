#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#pragma clang diagnostic ignored "-Wpre-c23-compat"
#endif

#define OSTD_IMPL
#define OSTD_NO_GRAPHICS
#include "../src/ostd.h"

int main(void) {

#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
	Surface_Handle surface = sys_make_surface(DEFAULT(Surface_Desc));
	assert(surface);
#else
	Surface_Handle surface = sys_get_surface();
#endif

	f64 start_time = sys_get_seconds_monotonic();
	(void)start_time;

	while (!surface_should_close(surface)) {

		s64 width, height;
		assert(surface_get_framebuffer_size(surface, &width, &height));
		
		u32 *pixels = (u32*)surface_map_pixels(surface);
		assert(pixels);
		
		memset(pixels, 0x00, (sys_uint)((u64)width*(u64)height*4));

		for (s64 x = 200; x < 450; x += 1) {
			for (s64 y = 100; y < 250; y += 1) {
				pixels[y*width+x] = 0xffffffff;
			}
		}

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
