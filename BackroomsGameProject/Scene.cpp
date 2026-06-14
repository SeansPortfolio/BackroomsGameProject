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

		auto numLights = lights.size();
		shader->SetInt("TotalLights", numLights);

		for (int i = 0; i < numLights; i++)
		{
			auto light = lights[i];

			auto colorName = "pointLights[" + std::to_string(i) + "].color";
			auto positionName = "pointLights[" + std::to_string(i) + "].position";
			auto radiusName = "pointLights[" + std::to_string(i) + "].radius";

			auto constantName = "pointLights[" + std::to_string(i) + "].constant";
			auto linearName = "pointLights[" + std::to_string(i) + "].linear";
			auto exponentName = "pointLights[" + std::to_string(i) + "].exponent";

			shader->SetVec3(colorName.c_str(), light->color);
			shader->SetVec3(positionName.c_str(), light->GetPosition());
			shader->SetFloat(radiusName.c_str(), light->radius);

			shader->SetFloat(constantName.c_str(), 1);
			shader->SetFloat(linearName.c_str(), 0.09f);
			shader->SetFloat(exponentName.c_str(), 0.032f);
		}

		shader->Unbind();
	}

}