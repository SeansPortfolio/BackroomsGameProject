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

		shader->SetInt("TotalSpotLights", 1);

		shader->SetVec3("spotLights[0].position", camera->GetPosition());
		shader->SetVec3("spotLights[0].direction", camera->GetForward());

		shader->SetVec3("spotLights[0].color", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->SetFloat("spotLights[0].cutOff", glm::cos(glm::radians(40.0f)));
		shader->SetFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(45.0f)));

		shader->SetFloat("spotLights[0].constant", 1.0f);
		shader->SetFloat("spotLights[0].linear", 0.04f);
		shader->SetFloat("spotLights[0].quadratic", 0.002f);

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
