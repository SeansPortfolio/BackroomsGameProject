#include "StaticRigidbodyComponent.h"

StaticRigidbodyComponent::StaticRigidbodyComponent(GameObject* gameObject, ColliderShape* collider) : Component(gameObject)
{
	physx::PxShape* shape = collider->CreateShape();

	body = Physics::CreateRigidStatic(
		gameObject->Transform->Position,
		gameObject->Transform->Rotation);

	body->attachShape(*shape);
	shape->release();
}

StaticRigidbodyComponent::~StaticRigidbodyComponent()
{

}

void StaticRigidbodyComponent::Update(float dt)
{

}
