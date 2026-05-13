#include "Physics.h"

std::map<int, physx::PxRigidDynamic*> Physics::physObjects;

void Physics::Init()
{
	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);

	if (!mFoundation)
	{
		throw("PxCreateFoundation Failed.");
	}

	mPvd = PxCreatePvd(*mFoundation);

	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	mToleranceScale.length = 100;        // typical length of an object
	mToleranceScale.speed = 981;         // typical speed of an object, gravity*1s is a reasonable choice
	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);


	physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = mDispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	mScene = mPhysics->createScene(sceneDesc);

	physx::PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	mScene->addActor(*groundPlane);


	static physx::PxReal stackZ = 10.0f;


	physx::PxShape* shape = mPhysics->createShape(physx::PxBoxGeometry(2.0f, 2.0f, 2.0f), *mMaterial);
	physx::PxTransform localTm(physx::PxVec3(physx::PxReal(0) - physx::PxReal(10), physx::PxReal(1), 0) * 2.0f);
	physx::PxRigidDynamic* body = mPhysics->createRigidDynamic(physx::PxTransform(physx::PxVec3(0, 0, 0)));
	body->attachShape(*shape);
	physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
	mScene->addActor(*body);


	physObjects[totalObjects] = body;


	//for (physx::PxU32 i = 0; i < 5; i++)
		//createStack(physx::PxTransform(physx::PxVec3(0, 0, stackZ -= 10.0f)), 10, 2.0f);

}

void Physics::Simulate(float dt)
{
	mScene->simulate(dt);
	mScene->fetchResults(true);

}

void Physics::Cleanup()
{
}
