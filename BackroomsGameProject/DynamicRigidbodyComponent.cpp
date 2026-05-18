#include "DynamicRigidbodyComponent.h"

DynamicRigidbodyComponent::DynamicRigidbodyComponent(GameObject* gameObject) : Component(gameObject)
{
	physx::PxBoxGeometry box = Physics::CreateBoxGeometry(1.0f, 1.0f, 1.0f);
	physx::PxShape* shape = Physics::CreateShape(&box);

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
}

