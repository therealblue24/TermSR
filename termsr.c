#include "termsr.h"

tsr_view_t *tsr_view_create(uint16_t width, uint16_t height)
{
	tsr_view_t *ret = calloc(1, sizeof(tsr_view_t));
	ret->pixls = calloc(height * 3, width);
	ret->pxsize = height * width * 3;
	ret->height = height;
	ret->width = width;
	return ret;
}

int tsr_view_validate(tsr_view_t *vw)
{
	if(vw->pixls == NULL)
		return EXIT_FAILURE;
	if(vw->width == 0)
		return EXIT_FAILURE;
	if(vw->height % 2)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

void tsr_view_nuke(tsr_view_t *vw)
{
	free(vw->pixls);
	free(vw);
	return;
}

static const char *truecolor(uint8_t *px, char seq[], tsr_layer_t layer)
{
	char cat = layer == FOREGROUND ? '3' : '4';
	snprintf(seq, MAX_ESC_SEQUENCE_LEN, "%c8;2;%03d;%03d;%03d", cat, px[0],
			 px[1], px[2]);
	return seq;
}

static void termsr_render_internal(tsr_view_t *vw)
{
	char upper[MAX_ESC_SEQUENCE_LEN], lower[MAX_ESC_SEQUENCE_LEN];
	int width = vw->width;
	int height = vw->height;
	uint8_t *pixels = vw->pixls;

	for(int y = 1; y < height; y += 2) {
		for(int x = 0; x < width; x++) {
			uint8_t *top = pixels + 3 * (x + width * (y - 1));
			uint8_t *bottom = pixels + 3 * (x + width * y);
			printf("\033[%s;%sm▄", truecolor(top, upper, BACKGROUND),
				   truecolor(bottom, lower, FOREGROUND));
		}
		printf("\033[39;49m\n");
	}
}

int tsr_view_display(tsr_view_t *vw)
{
	if(tsr_view_validate(vw))
		return EXIT_FAILURE;
	termsr_render_internal(vw);
	printf("\n\033[%dA", vw->height);
	return EXIT_SUCCESS;
}

void tsr_view_set_pixel(tsr_view_t *vw, uint16_t x, uint16_t y, uint8_t r,
						uint8_t g, uint8_t b)
{
	if(tsr_view_validate(vw)) {
		return;
	}
	vw->pixls[(3 * (x + (vw->width * y)))] = r;
	vw->pixls[(3 * (x + (vw->width * y))) + 1] = g;
	vw->pixls[(3 * (x + (vw->width * y))) + 2] = b;
}
