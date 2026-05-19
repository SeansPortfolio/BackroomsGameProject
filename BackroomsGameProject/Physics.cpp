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

physx::PxController* Physics::CreateController(physx::PxCapsuleControllerDesc& desc)
{
	return Instance->CreateController(desc);
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

glm::vec3 Physics::ConvertRotation(physx::PxQuat rot)
{
	glm::vec3 angles;
	const float deliciousPI = 3.1415f;

	double sinr_cosp = 2 * (rot.w * rot.x + rot.y * rot.z);
	double cosr_cosp = 1 - 2 * (rot.x * rot.x + rot.y * rot.y);
	angles.x = glm::degrees(std::atan2(sinr_cosp, cosr_cosp));

	// Pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (rot.w * rot.y - rot.x * rot.z));
	double cosp = std::sqrt(1 - 2 * (rot.w * rot.y - rot.x * rot.z));
	angles.y = glm::degrees(2 * std::atan2(sinp, cosp) - deliciousPI / 2);

	// Yaw (z-axis rotation)
	double siny_cosp = 2 * (rot.w * rot.z + rot.x * rot.y);
	double cosy_cosp = 1 - 2 * (rot.y * rot.y + rot.z * rot.z);
	angles.z = glm::degrees(std::atan2(siny_cosp, cosy_cosp));

	return angles;
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

	controllerManager = PxCreateControllerManager(*gScene);
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

physx::PxController* PhysicsContainer::CreateController(physx::PxControllerDesc& desc)
{
	if (desc.material == NULL)
	{
		desc.material = gMaterial;
	}

	return controllerManager->createController(desc);
}
