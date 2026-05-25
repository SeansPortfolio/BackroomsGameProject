#pragma once

#include <unordered_map>
#include <memory>
#include <vector>

#include "Physics.h"

#include "Component.h"
#include "RendererComponent.h"
#include "StaticRigidbodyComponent.h"
#include "DynamicRigidbodyComponent.h"
#include "CharacterControllerComponent.h"

class Component;
class RendererComponent;

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

	glm::mat4 GetModelMatrix(glm::mat4 parent);

	inline glm::vec3 GetPosition() const { return Position; }

	inline glm::vec3 GetRotation() const { return Rotation; }

	inline glm::vec3 GetScale() const { return Scale; }

	inline void SetPosition(glm::vec3 pos) { Position = pos; }

	inline void SetRotation(glm::vec3 rot) { Rotation = rot; }

	inline void SetScale(glm::vec3 scale) { Scale = scale; }

	template<typename T, typename... Args>
	inline T& AddComponent(Args && ...args)
	{
		static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component");
		auto newComponent = std::make_shared<T>(this, std::forward<Args>(args)...);

		auto name = typeid(T).name();
		ComponentTypeMap[name] = newComponent;

		return *newComponent;
	}

	template<typename T>
	inline T& GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component");

		auto name = typeid(T).name();

		static_assert(ComponentTypeMap.find(name) != ComponentTypeMap.end() && "Component not registered before use.");

		return std::static_pointer_cast<T>(ComponentTypeMap[name]);
	}

	template<typename T>
	inline bool RemoveComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Type must inherit from Component");

		auto name = typeid(T).name();

		if (ComponentTypeMap.find(name) != ComponentTypeMap.end())
		{
			ComponentTypeMap.erase(name);
			return true;
		}

		return false;
	}


private:

	std::vector<std::shared_ptr<GameObject>> Children;

	std::unordered_map<const char*, std::shared_ptr<Component>> ComponentTypeMap;

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

};
