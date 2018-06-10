#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "opengl.h"


static u32 make_buffer(GLenum target, const void *data, GLsizei size) 
{
	GLuint buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, size, data, GL_STATIC_DRAW);

	return buffer;
}

void initGL(void) 
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glPolygonMode(GL_FRONT, GL_LINE);
	glClearDepth(4.0);
	glDepthFunc(GL_LESS);
}

/**
 * Handles the glfw keyboard input.
 */
void keyboard(GLFWwindow *window, u32 codepoint) 
{
	switch (codepoint & 0x7f) {
		case 'q':
			glfwSetWindowShouldClose(window, 1);
			break;
	}
	
}

/**
 * Function called by opengl when an error occurs.
 */
void glfw_error(int code, const char *desc) 
{
	fprintf(stdout, "GLFW error %d: %s\n", code, desc);
	exit(EXIT_FAILURE);
}

static u32 vertex, element;

/**
 * Sends the given vertex buffer to the GPU.
 *
 * @param vb: The vertex buffer that will be drawn.
 * @param program: The GLSL program to be used with the vertex buffer. 
 */
void send_buffer(VertexBuffer *vb) 
{
	if (vertex) {
		glDeleteBuffers(1, &vertex);
		glDeleteBuffers(1, &element);
	}
	vertex = make_buffer(GL_ARRAY_BUFFER, vb->vertexData, sizeof(float) * vb->vSize);
	element = make_buffer(GL_ELEMENT_ARRAY_BUFFER, vb->elementData, 
			sizeof(u32) * vb->eSize);
}

/**
 * Draws the contents of the vertex buffer that was sent to the GPU using
 * the given GLSL program.
 *
 * @param program: The GLSL program used.
 * @param vb: The vertex buffer that gets drawn.
 * @param w: The GLFW window that gets drawn to.
 */
void draw_buffer(u32 program, VertexBuffer *vb, GLFWwindow *w) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element);
	
	u32 vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, false, 0, 0);
	glDrawElements(GL_TRIANGLES, vb->eSize, GL_UNSIGNED_INT, (void *)0);
	
	glfwSwapBuffers(w);
}

/**
 * Sets up the frustum matrix in the given GLSL program.
 *
 * @param program: The GLSL program that will have the frustum matrix sent to.
 */
void setup_frustum(u32 program) 
{
	const float fov		= 90.0;
	const float aspect	= 16.0f / 9.0f;
	const float right 	= 1.0;
	const float left	= -1.0;
	const float top 	= 1.0;
	const float bottom	= -1.0;
	const float near	= 0.1;
	const float far		= 100.0;

	glm::mat4 perspective = glm::perspective(fov, aspect, near, far);
	
	s32 projectionLoc = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, false, (f32 *)glm::value_ptr(perspective));
}

/**
 * Sets up and sends the transformation matrix to the given GLSL program.
 *
 * @param program: The GLSL program that the matrix will be sent to.
 * @param scale: The scaling vector.
 * @param rotate: The rotation vector.
 * @param translate: The translation vector.
 */
void setup_transforms(u32 program, glm::vec3 &scale, glm::vec3 &rotate, 
						glm::vec3 &translate) 
{
	glm::mat4 scaleMat = glm::mat4(1.0f);
	scaleMat[0][0] = scale.x;
	scaleMat[1][1] = scale.y;
	scaleMat[2][2] = scale.z;

	float radianX = (rotate.x * 180.0) / PI;
	float radianY = (rotate.y * 180.0) / PI;
	float radianZ = (rotate.z * 180.0) / PI;

	glm::mat4 rotateXMat = glm::mat4(1.0f);
	rotateXMat[1][1] = cos(radianX);
	rotateXMat[2][1] = -sin(radianX);
	rotateXMat[1][2] = sin(radianX);
	rotateXMat[2][2] = cos(radianX);

	glm::mat4 rotateYMat = glm::mat4(1.0f);
	rotateYMat[0][0] = cos(radianY);
	rotateYMat[2][0] = sin(radianY);
	rotateYMat[0][2] = -sin(radianY);
	rotateYMat[2][2] = cos(radianY);
	
	glm::mat4 rotateZMat = glm::mat4(1.0f);
	rotateZMat[0][0] = cos(radianZ);
	rotateZMat[1][0] = -sin(radianZ);
	rotateZMat[0][1] = sin(radianZ);
	rotateZMat[1][1] = cos(radianZ);

	glm::mat4 translateMat = glm::mat4(1.0f);
	translateMat[3][0] = translate.x;
	translateMat[3][1] = translate.y;
	translateMat[3][2] = translate.z;
               
	glm::mat4 transform = glm::mat4(1.0f);


	s32 transformLoc = glGetUniformLocation(program, "transform");
	glUniformMatrix4fv(transformLoc, 1, false, (f32 *)glm::value_ptr(transform));
}

/**
 * Sets the identity matrix for the given GLSL program to the identity matrix.
 *
 * @param program: The GLSL program who's transformation matrix will be set to
 * the identity matrix
 */
void clear_transforms(u32 program) 
{
	glm::mat4 transform = glm::mat4(1.0);
	s32 transformLoc = glGetUniformLocation(program, "transform");
	glUniformMatrix4fv(transformLoc, 1, false, (f32 *)glm::value_ptr(transform));
}


/**
 * Clears the camera matrix for the given GLSL program.
 *
 * @param program: The program who's camera matrix will be cleared.
 */
void clear_camera(u32 program) 
{
	glm::vec3 n = {0.0, 0.0, 1.0};
	glm::vec3 u = {1.0, 0.0, 0.0};
	glm::vec3 v = {0.0, 1.0, 0.0};

	glm::mat4 camera = glm::mat4(1.0);
	camera[0][0] = u.x;
	camera[0][1] = v.x;
	camera[0][2] = n.x;
	camera[0][3] = 0.0;
	
	camera[1][0] = u.y;
	camera[1][1] = v.y;
	camera[1][2] = n.y;
	camera[1][3] = 0.0;
	
	camera[2][0] = u.z; 
	camera[2][1] = v.z; 
	camera[2][2] = n.z; 
	camera[2][3] = 0.0;
	
	camera[3][0] = 0.0;
	camera[3][1] = 0.0;
	camera[3][2] = 0.0;
	camera[3][3] = 1.0;

	s32 cameraLoc = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(cameraLoc, 1, false, (f32 *)glm::value_ptr(camera));
}

/**
 * Constructs and sends the camera matrix to the given GLSL program.
 *
 * @param program: The program that the camera matrix will be sent to.
 * @param camera: The camera that will be sent to the GLSL program.
 */
void setup_camera(u32 program, glm::mat4 &view_mat) 
{
	float *cameraMat = (f32 *) glm::value_ptr(view_mat);
	s32 cameraLoc = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(cameraLoc, 1, false, cameraMat);
}









