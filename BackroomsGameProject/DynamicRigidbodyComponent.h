#pragma once

#include "Physics.h"
#include "Component.h"

class DynamicRigidbodyComponent : public Component
{
public:
	DynamicRigidbodyComponent(GameObject* gameObject);
	~DynamicRigidbodyComponent();

	virtual void Update(float dt);

	virtual inline ComponentType GetType() const { return ComponentType::Rigidbody; }

private:

	physx::PxRigidDynamic* body;

};

