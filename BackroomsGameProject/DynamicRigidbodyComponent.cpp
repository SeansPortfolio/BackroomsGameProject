#include "DynamicRigidbodyComponent.h"

DynamicRigidbodyComponent::DynamicRigidbodyComponent(OLDGameObject* gameObject, ColliderShape* collider) : Component(gameObject)
{
	physx::PxShape* shape = collider->CreateShape();

	body = Physics::CreateRigidDynamic(
		gameObject->GetPosition(),
		gameObject->GetRotation());

	body->attachShape(*shape);
	shape->release();
}

DynamicRigidbodyComponent::~DynamicRigidbodyComponent()
{


}

void DynamicRigidbodyComponent::Update(float dt)
{
	auto globalPos = body->getGlobalPose();
	gameObject->SetRotation(Physics::ConvertPosition(globalPos.p));
	gameObject->SetRotation(Physics::ConvertRotation(globalPos.q));
}

