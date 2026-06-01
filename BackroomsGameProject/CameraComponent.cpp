#include "CameraComponent.h"

CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
{
	Up = glm::vec3(0, 1, 0);
}

CameraComponent::~CameraComponent()
{

}

glm::mat4 CameraComponent::GetViewMatrix()
{
	auto pos = gameObject->GetPosition();
	auto forward = gameObject->GetForward();

	return glm::lookAt(pos, pos + forward, Up);
}

glm::mat4 CameraComponent::GetProjectionMatrix(float aspectRatio)
{
	return glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 1000.0f);
}
