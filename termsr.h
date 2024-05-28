#ifndef TERMSR
#define TERMSR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

enum { MAX_ESC_SEQUENCE_LEN = sizeof("38;2;000;000;000;48;2;000;000;000") };

typedef enum tsr_layer_e { BACKGROUND, FOREGROUND } tsr_layer_t;

typedef struct tsr_view_s {
	uint8_t *pixls;
	size_t pxsize;
	uint16_t width;
	uint16_t height;
} tsr_view_t;

tsr_view_t *tsr_view_create(uint16_t width, uint16_t height);
int tsr_view_validate(tsr_view_t *vw);
void tsr_view_nuke(tsr_view_t *vw);
int tsr_view_display(tsr_view_t *vw);
void tsr_view_set_pixel(tsr_view_t *vw, uint16_t x, uint16_t y, uint8_t r,
						uint8_t g, uint8_t b);

#endif /* TERMSR */
