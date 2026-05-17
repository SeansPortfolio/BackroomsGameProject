#pragma once

#include <memory>
#include <vector>

#include "Component.h"
#include "RendererComponent.h"
#include "TransformComponent.h"

class Component;
class RendererComponent;

class GameObject
{
public:

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
	
	GameObject();
	GameObject(glm::vec3 pos);
	GameObject(glm::vec3 pos, glm::vec3 rot);
	GameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

	~GameObject();

	glm::mat4 GetModelMatrix();

	glm::mat4 GetModelMatrix(glm::mat4 parent);

	virtual void AddChild(std::shared_ptr<GameObject> child);

	virtual void Update(float dt);

	virtual void Render(glm::mat4 parentModel, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	template<typename T, typename... Args>
	inline T& AddComponent(Args && ...args)
	{
		static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component");

		auto newComponent = std::make_shared<T>(std::forward<Args>(args)...);
		components.push_back(newComponent);
		return *newComponent;
	}

protected:

	std::vector<std::shared_ptr<GameObject>> Children;


private:

	std::vector<std::shared_ptr<Component>> components;


};

