#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

/**
 * Constructor.
 */
Camera* create_camera(void) 
{
	Camera *camera = (Camera *)safe_malloc(sizeof(Camera));
	camera->forward 	= false;
	camera->backward 	= false;
	camera->strafeLeft 	= false;
	camera->strafeRight = false;
	camera->rotateRight = false;
	camera->rotateLeft 	= false;

	camera->speed = 0.01f;

	//glfwSetMousePos(1280 / 2, 720 / 2);

	camera->position 	= glm::vec3(0.0f, 0.0f, 0.0f);
	camera->look_at		= glm::vec3(0.0f, 0.0f, -1.0f);
	camera->up 			= glm::vec3(0.0f, 1.0f, 0.0f);
	camera->strafe 		= glm::cross(camera->look_at, camera->up);

	camera->view_mat = glm::lookAt(camera->position, camera->position + camera->look_at, camera->up);

	return camera;
}

/**
 * Destructor.
 */
void destroy_camera(Camera *camera) {
	free(camera);
}

/**
 * Modifies the camera's position or view direction depending on what
 * flags are set to true.
 */
void move(Camera *camera, f64 last_frame_time, f64 curr_frame_time) {
	f32 delta = (curr_frame_time - last_frame_time) * 1000.0;
	f32 dz = camera->look_at.z * delta;
	//printf("start%f\n", last_frame_time);
	//printf("end%f\n", curr_frame_time);
	f32 dx = camera->look_at.x * delta;

	if (camera->forward) {
		camera->position.x += camera->speed * dx;
		camera->position.z += camera->speed * dz;
	} 
	if (camera->backward) {
		camera->position.x -= camera->speed * dx;
		camera->position.z -= camera->speed * dz;
	} 
	if (camera->strafeLeft) {
		camera->position.x -= camera->speed * camera->strafe.x * delta;
		camera->position.z -= camera->speed * camera->strafe.z * delta;
	} 
	if (camera->strafeRight) {
		camera->position.x += camera->speed * camera->strafe.x * delta;
		camera->position.z += camera->speed * camera->strafe.z * delta;

	} 
	if (camera->rotateRight) {
		float angle = -0.01 * delta;
		camera->look_at = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f))) * camera->look_at;
		camera->strafe = glm::cross(camera->look_at, camera->up);
	} 
	if (camera->rotateLeft) {
		float angle = 0.01 * delta;
		camera->look_at = glm::mat3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f))) * camera->look_at;
		camera->strafe = glm::cross(camera->look_at, camera->up);
	}
	camera->view_mat = glm::lookAt(camera->position, camera->position + camera->look_at, camera->up);
}






