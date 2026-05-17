#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class GameObject;

class Component
{
public:

	~Component()
	{
		gameObject = NULL;
	}

	virtual void Update(float dt) = 0;

	virtual void Render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;

private:

	GameObject* gameObject;

	friend class GameObject;
};

#include "GameObject.h"

