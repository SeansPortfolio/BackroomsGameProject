#include "Camera.h"

Camera::Camera()
{
	Forward = glm::vec3(0, 0, 1.0f);
	Up = glm::vec3(0, 1, 0);
	Position = glm::vec3(0, 0, 0);

	Yaw = 90.0f;
	Pitch = 0.0f;
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec3 forward;

	forward.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	forward.y = sin(glm::radians(Pitch));
	forward.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Forward = glm::normalize(forward);

	return glm::lookAt(Position, Position + Forward, Up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio)
{
	return glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 1000.0f);
}
