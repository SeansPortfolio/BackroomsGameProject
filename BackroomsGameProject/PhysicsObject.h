#pragma once

#include "GraphicsObject.h"
#include <physx/PxPhysicsAPI.h>

class PhysicsObject : public GraphicsObject
{

public:

	void Update(float dt);

	void AddBody(physx::PxRigidDynamic* body);

private:

	physx::PxRigidDynamic* body;



};

