#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "termsr.h"

// 75% 144p. Pathetic.
#define WIDTH 144
#define HEIGHT 108
//#define WIDTH 640
//#define HEIGHT 480

void demoscene(tsr_view_t *vw, float time)
{
	for(int x = 0; x < vw->width; x++) {
		for(int y = 0; y < vw->height; y++) {
			float uvx = (float)x / (float)vw->width;
			float uvy = (float)y / (float)vw->height;
			float r = time + uvx;
			float g = time + uvy + 2.0;
			float b = time + uvx + 4.0;
			r = cosf(r) * 0.5;
			g = cosf(g) * 0.5;
			b = cosf(b) * 0.5;
			r += 0.5;
			g += 0.5;
			b += 0.5;
			uint8_t normr, normg, normb;
			normr = (r * 255);
			normg = (g * 255);
			normb = (b * 255);
			tsr_view_set_pixel(vw, x, y, normr, normg, normb);
		}
	}
}

int evenify(int prev)
{
	int ret = prev;
	if(prev % 2) {
		ret++;
	}
	return ret;
}

uint64_t timems()
{
	struct timespec tv;
	clock_gettime(CLOCK_MONOTONIC, &tv);
	return (1000000 * tv.tv_sec) + (tv.tv_nsec / 1000);
}

int main(int argc, char *argv[])
{
	float sc = atof(argv[1]);
	tsr_view_t *vw = tsr_view_create(WIDTH * sc, evenify(HEIGHT * sc));
	if(tsr_view_validate(vw)) {
		fprintf(stderr, "error\n");
		return EXIT_FAILURE;
	}
	float t = 0.0;
	float frac = 0.0;
	uint64_t init, now, diff;

	for(;;) {
		demoscene(vw, t);
		init = timems();
		tsr_view_display(vw);

		usleep(1000000 / 30);
		now = timems();
		diff = now - init;
		frac = (diff / 1000000.f);
		t += frac;
	}
	tsr_view_nuke(vw);
}
