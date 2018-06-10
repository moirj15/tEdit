#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

/**
 * Exits the program after printing the given error message.
 *
 * @param err: The error message that will be printed.
 */
void quit(const char *err) 
{

	fprintf(stderr, "%s\n", err);
#ifdef _DEBUG
    getchar();
#endif
    exit(EXIT_FAILURE);
}

/**
 * Opens the given file with the given permissions.
 *
 * @param dir: The location of the file.
 * @param perm: The permissions to open the file with.
 * @return: The opened file.
 */
FILE *open_file(const char *dir, const char *perm) 
{
	FILE *fp = NULL;
	fp = fopen(dir, perm);
	if (!fp) {
		fprintf(stderr, "Failed to open file: %s\n", dir);
		exit(EXIT_FAILURE);
	}

	return fp;
}

/**
 * Closes the given file.
 *
 * @param fp: The file that will be closed.
 */
void close_file(FILE *fp) 
{
	if (0 != fclose(fp)) {
		fprintf(stderr, "Failed to close file");
		exit(EXIT_FAILURE);
	}
}

/**
 * Reads the contents of the file and returns it as a dynamically allocated
 * char array.
 *
 * @param name: The name of the file.
 * @return: A char aray of the contents of the file.
 */
char *read_file(const char *name) 
{
	FILE *fp = open_file(name, "r");
	char *src = NULL;
	uint64_t len = 0;

	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	rewind(fp);

	if (len == 0) {
		quit("failed to get file size");
	}

	src = (char *) calloc(len + 1, sizeof(char));
	len = fread(src, sizeof(char), len, fp);

	return src;
}

void print_shader_info_log(u32 shader) 
{
	s32 length = 0;
	GLsizei nchars = 0;
	char *log;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

	if (length > 0) {
		log = (char *) safe_malloc(length);

		if (log != NULL) {
			glGetShaderInfoLog(shader, length, &nchars, log);

			if (log[0] != '\0') {
				printf("shader log: '%s'\n", log);
			}

			free(log);
		}
	}
}

void print_program_info_log(u32 shader) 
{
	GLint length = 0;
	GLsizei nchars = 0;
	char *log;

	glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);

	if (length > 0) {
		log = (char *) safe_malloc(length);

		if (log != NULL) {
			glGetProgramInfoLog(shader, length, &nchars, log);

			if (log[0] != '\0') {
				printf("program log: '%s'\n", log);
			}

			free(log);
		}
	}
}


/**
 * Compiles and links the shader files.
 *
 * @param vert: The location of the vertex shader.
 * @param frag: The location of the fragment shader.
 * @return: The handle to the GLSL shader program.
 */
u32 shader_setup(const char *vert, const char *frag)
{
	char *vertSrc = NULL;
	char *fragSrc = NULL;
	u32 vertRef, fragRef, program;
	s32 flag;

	vertRef = glCreateShader(GL_VERTEX_SHADER);
	fragRef = glCreateShader(GL_FRAGMENT_SHADER);

	vertSrc = read_file(vert);
	fragSrc = read_file(frag);

	glShaderSource(vertRef, 1, const_cast<const GLchar **>(&vertSrc), NULL);
	glShaderSource(fragRef, 1, const_cast<const GLchar **>(&fragSrc), NULL);

	free(vertSrc);
	free(fragSrc);

	glCompileShader(vertRef);
	glGetShaderiv(vertRef, GL_COMPILE_STATUS, &flag);
	print_shader_info_log(vertRef);
	if (!flag) {
		quit("failed to compile frag shader");
	}
	
	glCompileShader(fragRef);
	glGetShaderiv(fragRef, GL_COMPILE_STATUS, &flag);
	print_shader_info_log(fragRef);
	if (!flag) {
		quit("failed to compile vert shader");
	}

	program = glCreateProgram();
	glAttachShader(program, vertRef);
	glAttachShader(program, fragRef);

	print_program_info_log(program);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &flag);
	
	print_program_info_log(program);
	
	if (!flag) {
		quit("failed to link shaderes");
	}

	return program;
}
