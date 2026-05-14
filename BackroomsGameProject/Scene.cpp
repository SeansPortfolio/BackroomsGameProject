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
