#include "font_renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>
#include <cstdio>

#include <ft2build.h>
#include FT_FREETYPE_H

#define CHARACTER_BASE 33

struct Character
{
	u32 texture_id;
	u32 width;
	u32 height;
	u32 width_offset;
	u32 height_offset;
	u32 next_char_offset;

	Character(void) { }
	Character(u32 t_id, u32 w, u32 h, u32 w_off, u32 h_off, u32 n_off) :
		texture_id(t_id), width(w), height(h), width_offset(w_off),
		height_offset(h_off), next_char_offset(n_off) { }
};

// Characters '!' to '~'
Character characters[126 - 33];

static FT_Library font_lib = NULL;
static FT_Face font_face = NULL;

static u32 program;

void init_renderer(const char *vert, const char *frag)
{
	program = shader_setup(vert, frag);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/**
 * Initialzes the font to the given true type font.
 *
 * @param font: The location of the .ttf file.
 */
void init_font(const char *font)
{
	// Make sure the FT_library and FT_Face weren't initialized already
	// if they are, free them
	if (font_lib) {
		FT_Done_FreeType(font_lib);
	}
	if (font_face) {
		FT_Done_Face(font_face);
	}

	// Init the FT_Library and FT_face
	if (FT_Init_FreeType(&font_lib)) {
		fprintf(stderr, "failed to init font_lib\n");
		exit(EXIT_FAILURE);
	}	
	if (FT_New_Face(font_lib, font, 0, &font_face)) {
		fprintf(stderr, "failed to init font_face\n");
		exit(EXIT_FAILURE);
	}
	glUseProgram(program);
    FT_Set_Pixel_Sizes(font_face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Load the characters into the Character array
	for (u8 c = 33; c < 126; c++) {
		if (FT_Load_Char(font_face, c, FT_LOAD_RENDER)) {
			fprintf(stderr, "failed to load character: %c\n", c);
			exit(EXIT_FAILURE);
		}
		u32 texture_id;
		glGenTextures(1, &texture_id);
		
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, font_face->glyph->bitmap.width,
					font_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
					font_face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		characters[c - CHARACTER_BASE] = Character(texture_id,
												font_face->glyph->bitmap.width,
												font_face->glyph->bitmap.rows,
												font_face->glyph->bitmap_left,
												font_face->glyph->bitmap_top,
												font_face->glyph->advance.x);
	}
}

// Not sure if the shader program should be passed through
void set_window_size(f32 width, f32 height)
{
	glViewport(0, 0, static_cast<u32>(width), static_cast<u32>(height));
	glm::mat4 projection = glm::ortho(0.0f, width, 0.0f, height);
	s32 projectionLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, false,
					   static_cast<f32 *>(glm::value_ptr(projection)));
}

// TODO: finish converting this to use Character struct for font info
void render_character(char ch, u32 x, u32 y, u32 size)
{
	Character character = characters[ch - CHARACTER_BASE];
	// Create the VAO and VBO's for rendering a character
	u32 VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "textColor"), 1.0f, 1.0f, 1.0f);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	f32 xpos = x + character.width_offset * size;
	f32 ypos = y - (character.height - character.height_offset) * size;
	f32 w = character.width * size;
	f32 h = character.height * size;

	f32 vertices[6][4] = {
		{ xpos, 	ypos + h, 0.0f, 0.0f},
		{ xpos, 	ypos, 	  0.0f, 1.0f},
		{ xpos + w, ypos, 	  1.0f, 1.0f},

		{ xpos, 	ypos + h, 0.0f, 0.0f},
		{ xpos + w, ypos, 	  1.0f, 1.0f},
		{ xpos + w, ypos + h, 1.0f, 0.0f}
	};
	glBindTexture(GL_TEXTURE_2D, character.texture_id);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
