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

physx::PxBoxGeometry Physics::CreateBoxGeometry(float halfExtentX, float halfExtentY, float halfExtentZ)
{
	return physx::PxBoxGeometry(halfExtentX, halfExtentY, halfExtentZ);
}

physx::PxShape* Physics::CreateShape(physx::PxGeometry* geometry)
{
	return Instance->CreateShape(geometry, NULL);
}

physx::PxShape* Physics::CreateShape(physx::PxGeometry* geometry, physx::PxMaterial* material)
{
	return Instance->CreateShape(geometry, material);
}

physx::PxRigidDynamic* Physics::CreateRigidDynamic(glm::vec3 pos, glm::vec3 rot)
{
	physx::PxTransform localTm(Physics::ConvertPosition(pos));
	physx::PxRigidDynamic* body = Instance->CreateRigidDynamic(localTm);
	return body;
}

physx::PxRigidStatic* Physics::CreateRigidStatic(glm::vec3 pos, glm::vec3 rot)
{
	physx::PxTransform localTm(Physics::ConvertPosition(pos));
	physx::PxRigidStatic* body = Instance->CreateRigidStatic(localTm);
	return body;
}

physx::PxVec3 Physics::ConvertPosition(glm::vec3 pos)
{
	return physx::PxVec3(pos.x, pos.y, pos.z);
}

glm::vec3 Physics::ConvertPosition(physx::PxVec3 pos)
{
	return glm::vec3(pos.x, pos.y, pos.z);
}

physx::PxQuat Physics::ConvertRotation(glm::vec3 rot)
{
	return physx::PxQuat();
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

	gMaterial = gPhysics->createMaterial(0.75f, 0.8f, 0.2f);


	physx::PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, physx::PxPlane(0, 1, 0, 0), *gMaterial);
	gScene->addActor(*groundPlane);
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

physx::PxShape* PhysicsContainer::CreateShape(physx::PxGeometry* geometry, physx::PxMaterial* material)
{
	if (material == NULL)
	{
		material = gMaterial;
	}

	return gPhysics->createShape(*geometry, *gMaterial);
}

physx::PxRigidDynamic* PhysicsContainer::CreateRigidDynamic(physx::PxTransform transform)
{
	auto actor = gPhysics->createRigidDynamic(transform);
	gScene->addActor(*actor);
	return actor;
}

physx::PxRigidStatic* PhysicsContainer::CreateRigidStatic(physx::PxTransform transform)
{
	auto actor = gPhysics->createRigidStatic(transform);
	gScene->addActor(*actor);
	return actor;
}
