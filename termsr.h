#ifndef TERMSR
#define TERMSR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

enum { MAX_ESC_SEQUENCE_LEN = sizeof("38;2;000;000;000;48;2;000;000;000") };

// don't use this
typedef enum tsr_layer_e { BACKGROUND, FOREGROUND } tsr_layer_t;

/// main view struct
// stores the pixel buffer, buffer size, width and height of the
// TermSR view
typedef struct tsr_view_s {
	uint8_t *pixls;
	size_t pxsize;
	uint16_t width;
	uint16_t height;
} tsr_view_t;

// create a new TermSR render view
tsr_view_t *tsr_view_create(uint16_t width, uint16_t height);
// validate if a TermSR view is OK or not
int tsr_view_validate(tsr_view_t *vw);
// delete a TermSR view
void tsr_view_nuke(tsr_view_t *vw);
// render a TermSR view onto the terminal
int tsr_view_display(tsr_view_t *vw);
// convience funciton; set pixel of the view @ (x,y) to (r,g,b)
void tsr_view_set_pixel(tsr_view_t *vw, uint16_t x, uint16_t y, uint8_t r,
						uint8_t g, uint8_t b);

#endif /* TERMSR */
