#pragma once

#include "Physics.h"
#include "Component.h"

#include "BoxColliderShape.h"
#include "SphereColliderShape.h"

class DynamicRigidbodyComponent : public Component
{
public:
	DynamicRigidbodyComponent(GameObject* gameObject, ColliderShape* collider);
	~DynamicRigidbodyComponent();

	virtual void Update(float dt);

	virtual inline ComponentType GetType() const { return ComponentType::Rigidbody; }

private:

	physx::PxRigidDynamic* body;

};

