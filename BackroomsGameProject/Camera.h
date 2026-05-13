#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:

	Camera();

	~Camera();

	glm::mat4 GetViewMatrix();

	glm::mat4 GetProjectionMatrix(float aspectRatio);

	glm::vec3 Position;

	glm::vec3 Forward;

	glm::vec3 Up;

	float Yaw;
	
	float Pitch;

};

