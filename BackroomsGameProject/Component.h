#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class GameObject;

class Component
{
public:

	Component(GameObject* gameObject)
	{
		this->gameObject = gameObject;
	}

	~Component()
	{
		gameObject = NULL;
	}

	virtual void Update(float dt) { }

	virtual void Render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) { }

protected:

	GameObject* gameObject;

	friend class GameObject;
};

#include "GameObject.h"

