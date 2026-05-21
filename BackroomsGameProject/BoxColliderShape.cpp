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
    return shape;
}
