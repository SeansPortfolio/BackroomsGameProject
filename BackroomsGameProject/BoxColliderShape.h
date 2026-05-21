#pragma once
#include "ColliderShape.h"


class BoxColliderShape : public ColliderShape
{
public:

	BoxColliderShape(glm::vec3 center, glm::vec3 extents);
	~BoxColliderShape();

	inline glm::vec3 SetExtents(glm::vec3 extents) { Extents = extents; }

	inline const glm::vec3 GetExtents() { return Extents; }

	virtual physx::PxShape* CreateShape();

private:

	glm::vec3 Extents;


};

