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

glm::mat4 TransformComponent::GetModelMatrix(glm::mat4 parent)
{
	glm::mat4 modelMatrix = glm::mat4(parent);

	modelMatrix = glm::translate(modelMatrix, Position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, Scale);

	return modelMatrix;
}
