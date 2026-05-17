#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Component.h"

class TransformComponent : public Component
{
public:

	TransformComponent(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

	~TransformComponent();

	void Update(float dt);

	void Render(glm::mat4 parentModel, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	virtual inline ComponentType GetType() const { return ComponentType::Transform; }

	glm::mat4 GetModelMatrix(glm::mat4 parent);

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

};

