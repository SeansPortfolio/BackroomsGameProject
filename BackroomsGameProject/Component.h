#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Component
{
public:

	virtual void Update(float dt) = 0;

	virtual void Render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;

};

