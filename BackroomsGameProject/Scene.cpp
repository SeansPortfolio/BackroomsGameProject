#include "Scene.h"

void Scene::InitPhysics()
{
	PhysicsSystem = std::make_unique<Physics>();
	PhysicsSystem->Init();
}

void Scene::PhysicsUpdate(float dt)
{
	PhysicsSystem->Simulate(dt);
}

void Scene::LogicUpdate(float dt)
{
	for (int i = 0; i < SceneObjects.size(); i++)
	{
		SceneObjects[i]->Update(dt);
	}
}

void Scene::Render(float aspectRatio)
{
	glm::mat4 model(1.0f);
	glm::mat4 viewMatrix = SceneCam.GetViewMatrix();
	glm::mat4 projectionMatrix = SceneCam.GetProjectionMatrix(aspectRatio);

	for (int i = 0; i < SceneObjects.size(); i++)
	{
		SceneObjects[i]->Render(model, viewMatrix, projectionMatrix);
	}
}

std::shared_ptr<PhysicsObject> Scene::CreatePhysicsObject(glm::vec3 position)
{
	auto mat = PhysicsSystem->mMaterial;
	float halfExtent = 1;

	physx::PxShape* shape = PhysicsSystem->mPhysics->createShape(physx::PxBoxGeometry(halfExtent, halfExtent, halfExtent), *(PhysicsSystem->mMaterial));
	physx::PxTransform localTm(physx::PxVec3(position.x, position.y, position.z));
	physx::PxRigidDynamic* body = PhysicsSystem->mPhysics->createRigidDynamic(localTm);
	body->attachShape(*shape);
	physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
	PhysicsSystem->mScene->addActor(*body);

	auto physObj = std::make_shared<PhysicsObject>();

	physObj->AddBody(body);
	physObj->Position = position;

	shape->release();

	return physObj;
}
