#include "BoxColliderShape.h"

BoxColliderShape::BoxColliderShape(glm::vec3 center, glm::vec3 extents) : ColliderShape(center)
{
	Extents = extents;
}

BoxColliderShape::~BoxColliderShape()
{

}

physx::PxShape* BoxColliderShape::CreateShape()
{
	physx::PxBoxGeometry box = Physics::CreateBoxGeometry(Extents.x, Extents.y, Extents.z);
	physx::PxShape* shape = Physics::CreateShape(&box);

	physx::PxTransform pos(physx::PxVec3(Center.x, Center.y, Center.z));
	shape->setLocalPose(pos);

    return shape;
}
