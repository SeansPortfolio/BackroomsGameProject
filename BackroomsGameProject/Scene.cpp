#include "Scene.h"

void Scene::Update(float dt)
{
	for (int i = 0; i < SceneObjects.size(); i++)
	{
		SceneObjects[i]->Update(dt);
	}
}

void Scene::Render(float aspectRatio)
{
	if (SceneCam == nullptr)
	{
		return;
	}

	glm::mat4 model(1.0f);
	glm::mat4 viewMatrix = SceneCam->GetViewMatrix();
	glm::mat4 projectionMatrix = SceneCam->GetProjectionMatrix(aspectRatio);

	for (int i = 0; i < SceneObjects.size(); i++)
	{
		SceneObjects[i]->Render(model, viewMatrix, projectionMatrix);
	}
}