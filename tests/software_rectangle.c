#define OSTD_IMPL
#define OSTD_NO_GRAPHICS
#include "../src/ostd.h"

int main(void) {

#if OS_FLAGS & OS_FLAG_HAS_WINDOW_SYSTEM
	Surface_Handle surface = sys_make_surface(DEFAULT(Surface_Desc));
#else
	Surface_Handle surface = sys_get_surface();
#endif
	while (!surface_should_close(surface)) {
		
		s64 width, height;
		assert(surface_get_framebuffer_size(surface, &width, &height));
		
		u32 *pixels = (u32*)surface_map_pixels(surface);
		assert(pixels);
		
		memset(pixels, 0x00, width*height*4);
		
		for (s64 x = 100; x < 300; x += 1) {
			for (s64 y = 50; y < 150; y += 1) {
				pixels[y*width+x] = 0xffffffff;
			}
		}
		
		surface_blit_pixels(surface);
		
		
		surface_poll_events(surface);
	}

	return 0;
}