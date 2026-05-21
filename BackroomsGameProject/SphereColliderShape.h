#pragma once
#include "ColliderShape.h"

class SphereColliderShape : public ColliderShape
{
public:

	SphereColliderShape(glm::vec3 center, float radius);
	~SphereColliderShape();

	inline void SetRadius(float radius) { Radius = radius; }

	inline const float GetRadius() { return Radius; }

	physx::PxShape* CreateShape();

private:

	float Radius;
};

