#pragma once

#include "Physics.h"
#include "Component.h"

#include "BoxColliderShape.h"
#include "SphereColliderShape.h"

class StaticRigidbodyComponent : public Component
{
public:

	StaticRigidbodyComponent(OLDGameObject* gameObject, ColliderShape* collider);
	~StaticRigidbodyComponent();

	virtual void Update(float dt);

	virtual inline OLDComponentType GetType() const { return OLDComponentType::Rigidbody; }


private:


	physx::PxRigidStatic* body;


};

