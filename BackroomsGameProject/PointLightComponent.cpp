#include "PointLightComponent.h"

PointLightComponent::PointLightComponent(GameObject* gameObject, glm::vec3 color, float radius) : Component(gameObject)
{
	this->color = color;
	this->radius = radius;
}

PointLightComponent::~PointLightComponent()
{
}
