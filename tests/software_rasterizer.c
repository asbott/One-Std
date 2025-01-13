

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

    float4 verts[] = {
        (float4){ -.5f, .5f, 0.f, 1.f },
        (float4){  0.f, .5f, 0.f, 1.f },
        (float4){  .5f, .5f, 0.f, 1.f },
    }

	while (!surface_should_close(surface)) {

		s64 width, height;
		assert(surface_get_framebuffer_size(surface, &width, &height));

		u32 *pixels = (u32*)surface_map_pixels(surface);
		assert(pixels);

		memset(pixels, 0x00, width*height*4);



		surface_blit_pixels(surface);


		surface_poll_events(surface);
	}

	return 0;
}