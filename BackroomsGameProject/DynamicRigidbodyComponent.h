#pragma once

#include "Physics.h"
#include "Component.h"

#include "BoxColliderShape.h"
#include "SphereColliderShape.h"

class DynamicRigidbodyComponent : public Component
{
public:
	DynamicRigidbodyComponent(OLDGameObject* gameObject, ColliderShape* collider);
	~DynamicRigidbodyComponent();

	virtual void Update(float dt);

	virtual inline OLDComponentType GetType() const { return OLDComponentType::Rigidbody; }

private:

	physx::PxRigidDynamic* body;

};

