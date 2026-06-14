#include "PointLightComponent.h"

PointLightComponent::PointLightComponent(GameObject* gameObject, glm::vec3 color, float radius) : Component(gameObject)
{
	this->color = color;
	this->radius = radius;
}

PointLightComponent::~PointLightComponent()
{
}

glm::vec3 PointLightComponent::GetPosition()
{
	return gameObject->GetPosition();
}
