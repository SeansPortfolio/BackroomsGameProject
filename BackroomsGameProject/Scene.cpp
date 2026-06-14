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
		SceneObjects[i]->Render(SceneCam->GetPosition(), model, viewMatrix, projectionMatrix);
	}

	auto lights = GetAllComponents<PointLightComponent>();
	auto renderers = GetAllComponents<RendererComponent>();

	for (auto& renderer : renderers)
	{
		auto shader = renderer->shader;
		shader->Bind();


		shader->SetMat4("Projection", projectionMatrix);
		shader->SetMat4("View", viewMatrix);


		shader->SetVec3("pointLights[0].color", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("pointLights[0].position", glm::vec3(5.0f, 2.5f, 5.0f));

		shader->SetFloat("pointLights[0].constant", 1);
		shader->SetFloat("pointLights[0].linear", 0.09f);
		shader->SetFloat("pointLights[0].exponent", 0.032f);
		shader->SetFloat("pointLights[0].radius", 20);

		shader->SetVec3("pointLights[2].color", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("pointLights[2].position", glm::vec3(75.0f, 2.5f, 5.0f));

		shader->SetFloat("pointLights[2].constant", 1);
		shader->SetFloat("pointLights[2].linear", 0.09f);
		shader->SetFloat("pointLights[2].exponent", 0.032f);
		shader->SetFloat("pointLights[2].radius", 10);

		shader->SetVec3("pointLights[3].color", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetVec3("pointLights[3].position", glm::vec3(5.0f, 2.5f, 75.0f));


		shader->SetFloat("pointLights[3].constant", 1);
		shader->SetFloat("pointLights[3].linear", 0.09f);
		shader->SetFloat("pointLights[3].exponent", 0.032f);
		shader->SetFloat("pointLights[3].radius", 5);

		shader->SetVec3("pointLights[1].color", glm::vec3(1.0f, 1.0f, 0.1f));
		shader->SetVec3("pointLights[1].position", glm::vec3(75.0f, 2.5f, 75.0f));

		shader->SetFloat("pointLights[1].constant", 1.0f);
		shader->SetFloat("pointLights[1].linear", 0.09f);
		shader->SetFloat("pointLights[1].exponent", 0.032f);
		shader->SetFloat("pointLights[1].radius", 2);

		shader->Unbind();
	}

}