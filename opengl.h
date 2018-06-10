#ifndef OPENGL_H
#define OPENGL_H

#include <glm/glm.hpp>

#include "utils.h"
#include "vertexBuffer.h"

/**
 * Initializes OpenGL
 */
void initGL(void);

/**
 * Handles the glfw keyboard input.
 */
void keyboard(GLFWwindow *window, u32 codepoint); 

/**
 * Function called by opengl when an error occurs.
 */
void glfw_error(int code, const char *desc); 

/**
 * Sends the given vertex buffer to the GPU.
 *
 * @param vb: The vertex buffer that will be drawn.
 * @param program: The GLSL program to be used with the vertex buffer. 
 */
void send_buffer(VertexBuffer *vb);

/**
 * Draws the contents of the vertex buffer that was sent to the GPU using
 * the given GLSL program.
 *
 * @param program: The GLSL program used.
 * @param vb: The vertex buffer that gets drawn.
 * @param w: The GLFW window that gets drawn to.
 */
void draw_buffer(u32 program, VertexBuffer *vb, GLFWwindow *w);

/**
 * Sets up the frustum matrix in the given GLSL program.
 *
 * @param program: The GLSL program that will have the frustum matrix sent to.
 */
void setup_frustum(u32 program);

/**
 * Sets up and sends the transformation matrix to the given GLSL program.
 *
 * @param program: The GLSL program that the matrix will be sent to.
 * @param scale: The scaling vector.
 * @param rotate: The rotation vector.
 * @param translate: The translation vector.
 */
void setup_transforms(u32 program, glm::vec3 &scale, glm::vec3 &rotate, 
						glm::vec3 &translate);

/**
 * Sets the identity matrix for the given GLSL program to the identity matrix.
 *
 * @param program: The GLSL program who's transformation matrix will be set to
 * the identity matrix
 */
void clear_transforms(u32 program);

/**
 * Clears the camera matrix for the given GLSL program.
 *
 * @param program: The program who's camera matrix will be cleared.
 */
void clear_camera(u32 program);

/**
 * Constructs and sends the camera matrix to the given GLSL program.
 *
 * @param program: The program that the camera matrix will be sent to.
 * @param camera: The camera that will be sent to the GLSL program.
 */
void setup_camera(u32 program, glm::mat4 &view_mat);
#endif
