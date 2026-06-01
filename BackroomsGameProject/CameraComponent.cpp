#include "CameraComponent.h"

CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
{
	Forward = glm::vec3(0, 0, 1.0f);
	Up = glm::vec3(0, 1, 0);

	Yaw = 90.0f;
	Pitch = 0.0f;
}

CameraComponent::~CameraComponent()
{

}

glm::mat4 CameraComponent::GetViewMatrix()
{
	auto pos = gameObject->GetPosition();
	glm::vec3 forward;

	forward.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	forward.y = sin(glm::radians(Pitch));
	forward.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Forward = glm::normalize(forward);

	return glm::lookAt(pos, pos + Forward, Up);
}

glm::mat4 CameraComponent::GetProjectionMatrix(float aspectRatio)
{
	return glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 1000.0f);
}
