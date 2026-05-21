#pragma once

#include "Physics.h"
#include "Component.h"

#include "BoxColliderShape.h"
#include "SphereColliderShape.h"

class StaticRigidbodyComponent : public Component
{
public:

	StaticRigidbodyComponent(GameObject* gameObject, ColliderShape* collider);
	~StaticRigidbodyComponent();

	virtual void Update(float dt);

	virtual inline ComponentType GetType() const { return ComponentType::Rigidbody; }


private:


	physx::PxRigidStatic* body;


};

