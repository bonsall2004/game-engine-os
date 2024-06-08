/*
 * custom_os
 * Author: bonsall2004
 * Description: 
 */
#include <display.h>

__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(2);

__attribute__((used, section(".requests")))
volatile struct limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};

__attribute__((used, section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER

color_t RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  color_t color;
  color.rgb[0] = r;
  color.rgb[1] = g;
  color.rgb[2] = b;
  color.rgb[3] = a;
  return color;
}

void draw_pixel(uint16_t x, uint16_t y, color_t color)
{
  void* framebuffer = framebuffer_request.response->framebuffers[0]->address;
  color_t* row = framebuffer + framebuffer_request.response->framebuffers[0]->pitch * y;
  row[x] = color;
}

void fill_frame_buffer(color_t color)
{
  for (int y = 0; y < FRAME_BUFFER_HEIGHT; y++) {
    for (int x = 0; x < FRAME_BUFFER_WIDTH; x++) {
      draw_pixel(x, y, color);
    }
  }
}