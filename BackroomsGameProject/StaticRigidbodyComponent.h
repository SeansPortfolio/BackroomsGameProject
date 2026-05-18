#pragma once

#include "Physics.h"
#include "Component.h"

class StaticRigidbodyComponent : public Component
{
public:

	StaticRigidbodyComponent(GameObject* gameObject);
	~StaticRigidbodyComponent();

	virtual void Update(float dt);

	virtual inline ComponentType GetType() const { return ComponentType::Rigidbody; }


private:


	physx::PxRigidStatic* body;


};

