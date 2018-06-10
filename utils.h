#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef int8_t  s8;
typedef int16_t	s16;
typedef int32_t s32;
typedef int64_t	s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

#define db() printf("hit\n");

#define PI 3.14159

/**
 * Exits the program after printing the given error message.
 *
 * @param err: The error message that will be printed.
 */
void quit(const char *err);

/**
 * Opens the given file with the given permissions.
 *
 * @param dir: The location of the file.
 * @param perm: The permissions to open the file with.
 * @return: The opened file.
 */
FILE *open_file(const char *dir, const char *perm);

/**
 * Closes the given file.
 *
 * @param fp: The file that will be closed.
 */
void close_file(FILE *fp);

/**
 * Reads the contents of the file and returns it as a dynamically allocated
 * char array.
 *
 * @param name: The name of the file.
 * @return: A char aray of the contents of the file.
 */
char *read_file(const char *name);

/**
 * Compiles and links the shader files.
 *
 * @param vert: The location of the vertex shader.
 * @param frag: The location of the fragment shader.
 * @return: The handle to the GLSL shader program.
 */
u32 shader_setup(const char *vert, const char *frag);

inline void *safe_malloc(u64 size)
{
	void *ret = NULL;
	ret = malloc(size);
	if (!ret) {
		fprintf(stderr, "failed to allocate\n");
		exit(EXIT_FAILURE);
	}

	return ret;
}

#endif
