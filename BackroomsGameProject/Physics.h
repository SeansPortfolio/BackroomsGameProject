#pragma once

#include "PhysicsObject.h"

#include <physx/PxPhysicsAPI.h>
#include <map>
#include <iostream>

class Physics
{
public:

	void Init();

	void Simulate(float dt);

	void Cleanup();

	static std::map<int, physx::PxRigidDynamic*> physObjects;

private:

	physx::PxDefaultAllocator      mDefaultAllocatorCallback;
	physx::PxDefaultErrorCallback  mDefaultErrorCallback;

	physx::PxFoundation* mFoundation = NULL;
	physx::PxPvd* mPvd = NULL;
	physx::PxPhysics* mPhysics = NULL;
	physx::PxScene* mScene = NULL;
	physx::PxDefaultCpuDispatcher* mDispatcher = NULL;
	physx::PxMaterial* mMaterial = NULL;

	physx::PxTolerancesScale       mToleranceScale;

	int totalObjects = 0;
};

