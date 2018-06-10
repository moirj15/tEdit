#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GlFW/glfw3.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdio>
#include <cstdlib>

#include "utils.h"
#include "opengl.h"
#include "font_renderer.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	glfwSetErrorCallback(glfw_error);

	if (!glfwInit()) {
		fprintf(stderr, "Failed to init GLFW\n");
		exit(EXIT_FAILURE);
	}

	GLFWwindow *window = NULL;
	window = glfwCreateWindow(800, 600, "bspEngine", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "glew error: %s\n", glewGetErrorString(err));
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	init_renderer("shader.vert", "shader.frag");
	init_font("consola.ttf");
	set_window_size(800.0f, 600.0f);
/*
	glViewport(0, 0, 800, 600);
	u32 program = shader_setup("shader.vert", "shader.frag");
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glUseProgram(program);

	//initGL();

	
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		printf("failed to init ft\n");
	}
	FT_Face face;
	if (FT_New_Face(ft, "consola.ttf", 0, &face)) {
		printf("failed to init face\n");
	}
	FT_Set_Pixel_Sizes(face, 0, 48);

	if (FT_Load_Char(face, 'x', FT_LOAD_RENDER)) {
		printf("no loadarino\n");
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	u32 texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
				 face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
				 face->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	s32 projectionLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, false, (f32 *)glm::value_ptr(projection));

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
	f32 xpos = 25.0f + face->glyph->bitmap_left * 5.0f;
	f32 ypos = 25.0f - (face->glyph->bitmap.rows - face->glyph->bitmap_top) * 5.0f;
	f32 w = face->glyph->bitmap.width * 1.0f;
	f32 h = face->glyph->bitmap.rows * 1.0f;

	f32 vertices[6][4] = {
		{ xpos, 	ypos + h, 0.0f, 0.0f},
		{ xpos, 	ypos, 	  0.0f, 1.0f},
		{ xpos + w, ypos, 	  1.0f, 1.0f},

		{ xpos, 	ypos + h, 0.0f, 0.0f},
		{ xpos + w, ypos, 	  1.0f, 1.0f},
		{ xpos + w, ypos + h, 1.0f, 0.0f}
	};
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	printf("don good\n");
	*/
	render_character('I', 05, 25, 1);
	render_character('m', 35, 25, 1);
	render_character('a', 55, 25, 1);
	render_character('d', 75, 25, 1);
	render_character('e', 95, 25, 1);
	render_character('t', 125, 25, 1);
	render_character('h', 145, 25, 1);
	render_character('i', 165, 25, 1);
	render_character('s', 185, 25, 1);
	glfwSwapBuffers(window);	
	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
	//	FT_Done_Face(face);
	//FT_Done_FreeType(ft);
	glfwDestroyWindow(window);
	glfwTerminate();
	
	printf("n0\n");
	return EXIT_SUCCESS;
}
