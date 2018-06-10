#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "utils.h"


struct Camera {
	f32 speed;
	
	u32 oldX, oldY;

	glm::vec3 position;	// position of the camera
	glm::vec3 look_at;		
	glm::vec3 up;
	glm::vec3 strafe;

	glm::mat4 view_mat;

	bool forward;
	bool backward;
	bool strafeLeft;
	bool strafeRight;
	bool rotateRight;
	bool rotateLeft;
};

Camera *create_camera(void);

void destroy_camera(Camera *camera);

void move(Camera *camera, f64 last_time_time, f64 curr_frame_time);
#endif
