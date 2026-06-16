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
	auto cameras = GetAllComponents<CameraComponent>();

	if (cameras.size() == 0)
	{
		return;
	}

	for (auto& cam : cameras)
	{
		Render(cam, aspectRatio);
	}
}

void Scene::Render(std::shared_ptr<CameraComponent> camera, float aspectRatio)
{
	glm::mat4 model(1.0f);
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glm::mat4 projectionMatrix = camera->GetProjectionMatrix(aspectRatio);

	for (int i = 0; i < SceneObjects.size(); i++)
	{
		SceneObjects[i]->Render(model);
	}

	auto pointLights = GetAllComponents<PointLightComponent>();
	auto spotLights = GetAllComponents<SpotLightComponent>();
	auto renderers = GetAllComponents<RendererComponent>();

	for (auto& renderer : renderers)
	{
		auto shader = renderer->shader;
		shader->Bind();

		shader->SetMat4("Projection", projectionMatrix);
		shader->SetMat4("View", viewMatrix);
		shader->SetVec3("viewPos", camera->GetPosition());

		auto numLights = pointLights.size();
		shader->SetInt("TotalPointLights", numLights); 

		for (int i = 0; i < numLights; i++)
		{
			auto light = pointLights[i];
			auto indexStr = std::to_string(i);

			auto colorName = "pointLights[" + indexStr + "].color";
			auto positionName = "pointLights[" + indexStr + "].position";
			auto radiusName = "pointLights[" + indexStr + "].radius";

			auto constantName = "pointLights[" + indexStr + "].constant";
			auto linearName = "pointLights[" + indexStr + "].linear";
			auto exponentName = "pointLights[" + indexStr + "].exponent";

			shader->SetVec3(colorName.c_str(), light->color);
			shader->SetVec3(positionName.c_str(), light->GetPosition());
			shader->SetFloat(radiusName.c_str(), light->radius);

			shader->SetFloat(constantName.c_str(), 1);
			shader->SetFloat(linearName.c_str(), 0.09f);
			shader->SetFloat(exponentName.c_str(), 0.032f);
		}

		numLights = spotLights.size();
		shader->SetInt("TotalSpotLights", numLights);
		for (int i = 0; i < numLights; i++)
		{
			auto light = spotLights[i];
			auto indexStr = std::to_string(i);

			auto colorName = "spotLights[" + indexStr + "].color";
			auto positionName = "spotLights[" + indexStr + "].position";
			auto directionName = "spotLights[" + indexStr + "].direction";

			auto cutOffName = "spotLights[" + indexStr + "].cutOff";
			auto outerCutoffName = "spotLights[" + indexStr + "].outerCutOff";

			auto constantName = "spotLights[" + indexStr + "].constant";
			auto linearName = "spotLights[" + indexStr + "].linear";
			auto exponentName = "spotLights[" + indexStr + "].exponent";

			shader->SetVec3(colorName.c_str(), light->color);
			shader->SetFloat(cutOffName.c_str(), light->cutoff);
			shader->SetFloat(outerCutoffName.c_str(), light->outerCutoff);

			shader->SetVec3(directionName.c_str(), light->GetForward());
			shader->SetVec3(positionName.c_str(), light->GetPosition());

			shader->SetFloat(constantName.c_str(), 1.0f);
			shader->SetFloat(linearName.c_str(), 0.04f);
			shader->SetFloat(exponentName.c_str(), 0.002f);
		}

		shader->Unbind();
	}
}

template<typename T>
inline std::vector<std::shared_ptr<T>> Scene::GetAllComponents()
{
	static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component");

	std::vector<std::shared_ptr<T>> result;
	for (auto& gameObject : SceneObjects)
	{
		auto component = gameObject->GetComponent<T>();
		if (component != NULL)
		{
			result.push_back(component);
		}
	}

	return result;
}
