#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "GameObject.h"

class CameraComponent : public Component
{
public:

	CameraComponent(GameObject* gameObject);

	~CameraComponent();

	glm::mat4 GetViewMatrix();

	glm::mat4 GetProjectionMatrix(float aspectRatio);

	//glm::vec3 Position;

	glm::vec3 Forward;

	glm::vec3 Up;

	float Yaw;
	
	float Pitch;

};

