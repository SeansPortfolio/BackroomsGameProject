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
	physx::PxSphereGeometry sphere = Physics::CreateSphereGeometry(Radius);
	physx::PxShape* shape = Physics::CreateShape(&sphere);

	physx::PxTransform pos(physx::PxVec3(Center.x, Center.y, Center.z));
	shape->setLocalPose(pos);

	return shape;
}
