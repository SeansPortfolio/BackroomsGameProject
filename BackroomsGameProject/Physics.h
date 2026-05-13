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

	void createStack(const physx::PxTransform& t, physx::PxU32 size, physx::PxReal halfExtent)
	{


		physx::PxShape* shape = mPhysics->createShape(physx::PxBoxGeometry(halfExtent, halfExtent, halfExtent), *mMaterial);
		for (physx::PxU32 i = 0; i < size; i++)
		{
			for (physx::PxU32 j = 0; j < size - i; j++)
			{
				physx::PxTransform localTm(physx::PxVec3(physx::PxReal(j * 2) - physx::PxReal(size - i), physx::PxReal(i * 2 + 1), 0) * halfExtent);
				physx::PxRigidDynamic* body = mPhysics->createRigidDynamic(t.transform(localTm));
				body->attachShape(*shape);
				physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
				mScene->addActor(*body);				


				physObjects[totalObjects] = body;
				totalObjects++;
			}
		}
		shape->release();
	}

};

