#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Physics.h"

class ColliderShape
{
public:

	ColliderShape(glm::vec3 center);
	~ColliderShape();

	virtual physx::PxShape* CreateShape() = 0;

	inline void SetCenter(glm::vec3 pos) { Center = pos; }

	inline glm::vec3 GetCenter() { return Center; }

protected:

	glm::vec3 Center;

};

