#pragma once

#include "Component.h"

#include "Physics.h"

class BoxColliderComponent : public Component
{
public:

	BoxColliderComponent(glm::vec3 halfExtents);
	~BoxColliderComponent();

	virtual inline ComponentType GetType() const { return ComponentType::Collider; }

	inline glm::vec3 GetSize() const { return Size; }

private:

	physx::PxShape* shape;

	glm::vec3 Size;

};

