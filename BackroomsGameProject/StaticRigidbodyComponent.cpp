#include "StaticRigidbodyComponent.h"

StaticRigidbodyComponent::StaticRigidbodyComponent(GameObject* gameObject) : Component(gameObject)
{
	physx::PxBoxGeometry box = Physics::CreateBoxGeometry(5.0f, 0.25f, 5.0f);
	physx::PxShape* shape = Physics::CreateShape(&box);

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
