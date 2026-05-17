#include "Physics.h"

std::unique_ptr<PhysicsContainer> Physics::Instance;

void Physics::Init()
{
	Instance = std::make_unique<PhysicsContainer>();
	Instance->InitPhysics();
}

void Physics::RegisterActor(physx::PxActor* actor)
{
	Instance->RegisterActor(actor);
}

void Physics::Simulate(float dt)
{
	Instance->Simulate(dt);
}

void Physics::Quit()
{
	Instance->Quit();
	Instance.release();
}

void PhysicsContainer::InitPhysics()
{
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(localHost, 5425, 10);
	gPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, physx::PxTolerancesScale(), true, gPvd);

	physx::PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);

	physx::PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
}

void PhysicsContainer::RegisterActor(physx::PxActor* actor)
{
	gScene->addActor(*actor);
}

void PhysicsContainer::Simulate(float dt)
{
	gScene->simulate(dt);
	gScene->fetchResults(true);
}

void PhysicsContainer::Quit()
{
	PX_RELEASE(gScene);
	PX_RELEASE(gDispatcher);
	PX_RELEASE(gPhysics);

	if (gPvd)
	{
		physx::PxPvdTransport* transport = gPvd->getTransport();
		PX_RELEASE(gPvd);
		PX_RELEASE(transport);
	}

	PX_RELEASE(gFoundation);
}
