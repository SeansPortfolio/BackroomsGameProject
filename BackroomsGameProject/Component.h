#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class OLDGameObject;

enum class OLDComponentType
{
	Transform,
	Renderer,
	Collider,
	Rigidbody,
	Controller,
};



using ComponentType = std::uint8_t;
const ComponentType MaxComponents = 31;


struct TransformComponent
{
	glm::vec3 Position;
};








class Component
{
public:

	Component(OLDGameObject* gameObject)
	{
		this->gameObject = gameObject;
	}

	~Component()
	{
		gameObject = NULL;
	}

	virtual void Update(float dt) { }

	virtual void Render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) { }

	virtual inline OLDComponentType GetType() const = 0;

	inline bool IsPhysicsType() { return GetType() == OLDComponentType::Collider || GetType() == OLDComponentType::Rigidbody; }

protected:

	OLDGameObject* gameObject;

	friend class OLDGameObject;
};

#include "GameObject.h"

