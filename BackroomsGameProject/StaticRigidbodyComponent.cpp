#include "StaticRigidbodyComponent.h"

StaticRigidbodyComponent::StaticRigidbodyComponent(GameObject* gameObject, ColliderShape* collider) : Component(gameObject)
{
	physx::PxShape* shape = collider->CreateShape();

	body = Physics::CreateRigidStatic(
		gameObject->GetPosition(),
		gameObject->GetRotation());

	body->attachShape(*shape);
	shape->release();
}

StaticRigidbodyComponent::~StaticRigidbodyComponent()
{

}

void StaticRigidbodyComponent::Update(float dt)
{

}
