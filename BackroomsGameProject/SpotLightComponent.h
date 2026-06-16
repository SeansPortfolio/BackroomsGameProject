#pragma once

#include "Component.h"

class SpotLightComponent : public Component
{
public:

	SpotLightComponent(GameObject* gameObject, glm::vec3 color, float cutoff, float outerCutoff);

	~SpotLightComponent();

	glm::vec3 color;

	float cutoff;

	float outerCutoff;

	glm::vec3 GetPosition();

	glm::vec3 GetForward();

};

