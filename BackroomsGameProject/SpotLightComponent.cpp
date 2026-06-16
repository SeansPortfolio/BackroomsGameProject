#include "SpotLightComponent.h"

SpotLightComponent::SpotLightComponent(GameObject* gameObject, glm::vec3 color, float cutoff, float outerCutoff) : Component(gameObject)
{
	this->color = color;
	this->cutoff = cutoff;
	this->outerCutoff = outerCutoff;
}

SpotLightComponent::~SpotLightComponent()
{
}

glm::vec3 SpotLightComponent::GetPosition()
{
	return gameObject->GetPosition();
}

glm::vec3 SpotLightComponent::GetForward()
{
	return gameObject->GetForward();
}
