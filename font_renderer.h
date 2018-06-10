#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include "utils.h"

void init_renderer(const char *vert, const char *frag);

void init_font(const char *font);

void set_window_size(f32 width, f32 height);
   
void render_character(char ch, u32 x, u32 y, u32 size);


#endif
