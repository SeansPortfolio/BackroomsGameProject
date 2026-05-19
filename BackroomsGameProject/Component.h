#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class GameObject;

enum class ComponentType
{
	Transform,
	Renderer,
	Collider,
	Rigidbody,
	Controller,
};


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

	virtual inline ComponentType GetType() const = 0;

	inline bool IsPhysicsType() { return GetType() == ComponentType::Collider || GetType() == ComponentType::Rigidbody; }

protected:

	GameObject* gameObject;

	friend class GameObject;
};

#include "GameObject.h"

