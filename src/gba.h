// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-08

#include <stdlib.h>  // uint8_t, uint16_t, etc.

#ifndef GBA_H_
#define GBA_H_

/*******************************************************************************
 * Macro constants
 */

#define true 1
#define false 0

#define GBA_CPU_CLOCK 16780000

#define GBA_MAX_Y 160
#define GBA_MAX_X 240

#define GBA_VIDEO_MODE4 0x0004
#define GBA_VIDEO_BG2 0x0400

// See documentation for |*gba_buttons| below
#define GBA_BUTTON_A      0x001
#define GBA_BUTTON_B      0x002
#define GBA_BUTTON_SELECT 0x004
#define GBA_BUTTON_START  0x008
#define GBA_BUTTON_RIGHT  0x010
#define GBA_BUTTON_LEFT   0x020
#define GBA_BUTTON_UP     0x040
#define GBA_BUTTON_DOWN   0x080
#define GBA_BUTTON_R      0x100
#define GBA_BUTTON_L      0x200


/*******************************************************************************
 * Variable Constants
 */

// NOTE: Commented out 2017-04-08 because it will not be used in this project
//
// This is the 240x160 video memory buffer. When using MODE4 and MODE5, it
// should accept 8-bit color identifiers. However, it is impossible to write
// 8-bit values to this memory without affecting the other 8-bit block in the
// 16-bit register. This should be used with MODE3 or MODE2.
// uint16_t (*const gba_pixel_mat)[240] = (void*) 0x06000000;  // -> 0x06017fff

// Because of the limitations described above, this pointer is also a 16-bit
// matrix pointing to a row size of 1/2 for simplified subscripting:
// |gba_color_mat[y][x]| is the |2x+1|th and |2x|th pixels on the |y|th row.
// NOTE: the more significant byte contains the second value.
// Both bytes must still be written simultaneously.
extern volatile uint16_t (*const gba_color_mat_front)[120];
extern volatile uint16_t (*const gba_color_mat_back)[120];

// Under VIDEO MODE 4, each 8-bit block stores an offset from this pointer,
// which shall contain the actual color data in 16-bit RGB color defined as:
//     N BBBBB GGGGG RRRRR
// Where |N| is a null bit that does nothing and RGB are the respective
// color values.
extern volatile uint16_t* const gba_color_palette;

// Current line being drawn to the screen from video memory
extern volatile uint16_t* const gba_scan_line;

// This is used to select the video mode and display mode.
extern volatile unsigned long* const gba_display_control;

// This is the bitstring representing the depressed status of each button
// The buttons are located at the bits #define'd above. For example:
// "A is pressed" is equivalent to `!(*gba_buttons & GBA_BUTTON_A)`
// NOTE: The boolean value is inverted.
extern volatile uint16_t* const gba_buttons;

/*******************************************************************************
 * Functions
 */

// Block until the screen is drawn completely. This prevents us from switching
// buffers until the screen is drawn. Switching buffers while drawing the screen
// can result in tearing.
void gba_sync();

// Swap the working buffer with the display buffer
void gba_refresh();

// Fill the entire working buffer with a single color
void gba_fill_buffer(int color_id);

// Set the color of the pixel at (x, y) to the given color id
void gba_set_pixel(int x, int y, int color_id);

// Add the provided color to the next index in the palette, returning
// that index.
int gba_add_color(uint16_t color);

#endif  // GBA_H_
