#pragma once

#include <memory>
#include <vector>

#include "Physics.h"

#include "Component.h"
#include "RendererComponent.h"
#include "TransformComponent.h"
#include "DynamicRigidbodyComponent.h"

class Component;
class RendererComponent;
class TransformComponent;

class GameObject
{
public:

	GameObject();
	GameObject(glm::vec3 pos);
	GameObject(glm::vec3 pos, glm::vec3 rot);
	GameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	~GameObject();

	virtual void AddChild(std::shared_ptr<GameObject> child);

	virtual void Update(float dt);

	virtual void Render(glm::mat4 parentModel, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	template<typename T, typename... Args>
	inline T& AddComponent(Args && ...args)
	{
		static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component");

		auto newComponent = std::make_shared<T>(std::forward<Args>(args)...);
		newComponent->gameObject = this;
		Components.push_back(newComponent);

		return *newComponent;
	}

	std::unique_ptr <TransformComponent> Transform;

private:

	std::vector<std::shared_ptr<GameObject>> Children;

	std::vector<std::shared_ptr<Component>> Components;
};
