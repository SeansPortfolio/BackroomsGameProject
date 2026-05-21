#include "SphereColliderShape.h"

SphereColliderShape::SphereColliderShape(glm::vec3 center, float radius) : ColliderShape(center)
{
	Radius = radius;
}

SphereColliderShape::~SphereColliderShape()
{

}

physx::PxShape* SphereColliderShape::CreateShape()
{
	physx::PxSphereGeometry box = Physics::CreateSphereGeometry(Radius);
	physx::PxShape* shape = Physics::CreateShape(&box);
	return shape;
}
