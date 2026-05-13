#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

class GameObject
{
public:

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	GameObject();
	~GameObject();

	glm::mat4 GetModelMatrix();

	virtual void Update(float dt) = 0;

	virtual void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;

private:




};

