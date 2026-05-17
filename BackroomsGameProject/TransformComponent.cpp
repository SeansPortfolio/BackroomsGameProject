#include "TransformComponent.h"

TransformComponent::TransformComponent(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	Position = pos;
	Rotation = rot;
	Scale = scale;
}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::Update(float dt)
{

}

void TransformComponent::Render(glm::mat4 parentModel, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{

}
