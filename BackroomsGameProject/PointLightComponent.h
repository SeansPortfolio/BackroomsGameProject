#pragma once

#include "Component.h"

class PointLightComponent : public Component
{
public:

	PointLightComponent(GameObject* gameObject, glm::vec3 color, float radius);

	~PointLightComponent();

	glm::vec3 color;

	float radius;
};

