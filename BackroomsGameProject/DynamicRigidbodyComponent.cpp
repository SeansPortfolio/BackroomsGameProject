#include "DynamicRigidbodyComponent.h"

DynamicRigidbodyComponent::DynamicRigidbodyComponent(GameObject* gameObject, ColliderShape* collider) : Component(gameObject)
{
	physx::PxShape* shape = collider->CreateShape();

	body = Physics::CreateRigidDynamic(
		gameObject->Transform->Position,
		gameObject->Transform->Rotation);

	body->attachShape(*shape);
	shape->release();
}

DynamicRigidbodyComponent::~DynamicRigidbodyComponent()
{


}

void DynamicRigidbodyComponent::Update(float dt)
{
	auto globalPos = body->getGlobalPose();
	gameObject->Transform->Position = Physics::ConvertPosition(globalPos.p);
	gameObject->Transform->Rotation = Physics::ConvertRotation(globalPos.q);
}

