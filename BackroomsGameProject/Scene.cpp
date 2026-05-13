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
	glm::mat4 viewMatrix = SceneCam.GetViewMatrix();
	glm::mat4 projectionMatrix = SceneCam.GetProjectionMatrix(aspectRatio);

	for (int i = 0; i < SceneObjects.size(); i++)
	{
		SceneObjects[i]->Render(viewMatrix, projectionMatrix);
	}
}
