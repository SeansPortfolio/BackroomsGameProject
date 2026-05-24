#include "Scene.h"

void Scene::Init()
{
	for (GameObject id = 0; id < MaxGameObjects; id++)
	{
		availableIDs.push(id);
	}
}

void Scene::Update(float dt)
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

GameObject Scene::CreateGameObject()
{
	GameObject id = availableIDs.front();
	activeGameObjects++;
	return id;
}

bool Scene::DestroyGameObjectWithID(GameObject id)
{
	ComponentMasks[id].reset();
	availableIDs.push(id);
	activeGameObjects--;
	return true;
}

void Scene::SetGameObjectComponents(GameObject id, ComponentMask signature)
{
	ComponentMasks[id] = signature;
}

ComponentMask Scene::GetComponentMask(GameObject id)
{
	return ComponentMasks[id];
}
