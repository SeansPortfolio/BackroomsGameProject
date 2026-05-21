#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <physx/PxPhysicsAPI.h>
#include <map>
#include <iostream>

class PhysicsContainer;

class Physics
{
public:

	static void Init();

	static void RegisterActor(physx::PxActor* actor);

	static void Simulate(float dt);

	static void Quit();

	static physx::PxSphereGeometry CreateSphereGeometry(float radius);

	static physx::PxBoxGeometry CreateBoxGeometry(float halfExtentX, float halfExtentY, float halfExtentZ);

	static physx::PxShape* CreateShape(physx::PxGeometry* geometry);

	static physx::PxShape* CreateShape(physx::PxGeometry* geometry, physx::PxMaterial* material);

	static physx::PxRigidDynamic* CreateRigidDynamic(glm::vec3 pos, glm::vec3 rot);

	static physx::PxRigidStatic* CreateRigidStatic(glm::vec3 pos, glm::vec3 rot);

	static physx::PxController* CreateController(physx::PxCapsuleControllerDesc& desc);

	static physx::PxVec3 ConvertPosition(glm::vec3 pos);

	static glm::vec3 ConvertPosition(physx::PxVec3 pos);

	static physx::PxQuat ConvertRotation(glm::vec3 rot);

	static glm::vec3 ConvertRotation(physx::PxQuat rot);

private:

	static std::unique_ptr<PhysicsContainer> Instance;

};

class PhysicsContainer
{
private:

	void InitPhysics();

	void RegisterActor(physx::PxActor* actor);

	void Simulate(float dt);

	void Quit();

	physx::PxShape* CreateShape(physx::PxGeometry* geometry, physx::PxMaterial* material);

	physx::PxRigidDynamic* CreateRigidDynamic(physx::PxTransform transform);

	physx::PxRigidStatic* CreateRigidStatic(physx::PxTransform transform);

	physx::PxController* CreateController(physx::PxControllerDesc& desc);

	physx::PxDefaultAllocator		gAllocator;
	physx::PxDefaultErrorCallback	gErrorCallback;
	physx::PxFoundation* gFoundation = NULL;
	physx::PxPhysics* gPhysics = NULL;
	physx::PxDefaultCpuDispatcher* gDispatcher = NULL;
	physx::PxScene* gScene = NULL;
	physx::PxMaterial* gMaterial = NULL;
	physx::PxPvd* gPvd = NULL;

	physx::PxControllerManager* controllerManager;

	const char* localHost = "127.0.0.1";

	friend class Physics;
};