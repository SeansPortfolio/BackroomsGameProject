#include "PhysicsObject.h"

void PhysicsObject::Update(float dt)
{
	physx::PxTransform transform = body->getGlobalPose();
	physx::PxVec3 position = transform.p;
	physx::PxQuat rotation = transform.q;

	this->Position.x = position.x;
	this->Position.y = position.y;
	this->Position.z = position.z;

}

void PhysicsObject::AddBody(physx::PxRigidDynamic* body)
{
	this->body = body;
}
