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

	physx::PxDefaultAllocator		gAllocator;
	physx::PxDefaultErrorCallback	gErrorCallback;
	physx::PxFoundation* gFoundation = NULL;
	physx::PxPhysics* gPhysics = NULL;
	physx::PxDefaultCpuDispatcher* gDispatcher = NULL;
	physx::PxScene* gScene = NULL;
	physx::PxMaterial* gMaterial = NULL;
	physx::PxPvd* gPvd = NULL;

	const char* localHost = "127.0.0.1";

	friend class Physics;
};