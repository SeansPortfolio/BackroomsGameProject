#pragma once

// https://austinmorlan.com/posts/entity_component_system/

#include <memory>
#include <vector>
#include <bitset>

#include "Physics.h"

#include "Component.h"
#include "RendererComponent.h"
#include "StaticRigidbodyComponent.h"
#include "DynamicRigidbodyComponent.h"
#include "CharacterControllerComponent.h"

class Component;
class RendererComponent;

using GameObject = std::uint32_t;
using ComponentMask = std::bitset<MaxComponents>;

const GameObject MaxGameObjects = 5000;











class OLDGameObject
{
public:

	OLDGameObject();
	OLDGameObject(glm::vec3 pos);
	OLDGameObject(glm::vec3 pos, glm::vec3 rot);
	OLDGameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	~OLDGameObject();

	virtual void AddChild(std::shared_ptr<OLDGameObject> child);

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
		Components.push_back(newComponent);

		return *newComponent;
	}

private:

	std::vector<std::shared_ptr<OLDGameObject>> Children;

	std::vector<std::shared_ptr<Component>> Components;

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

};
