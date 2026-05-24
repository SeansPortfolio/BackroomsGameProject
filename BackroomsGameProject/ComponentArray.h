#pragma once

#include "GameObject.h"

#include <array>
#include <unordered_map>

class IComponentArray
{
public:

	virtual ~IComponentArray() = default;

	virtual void OnGameObjectDestroyed(GameObject id) = 0;
};




template<typename T>
class ComponentArray : IComponentArray
{
public:
	
	void AddComponent(GameObject id, T component);

	void RemoveComponent(GameObject id);

	T& GetComponent(GameObject id);

	void OnGameObjectDestroyed(GameObject id);

private:

	std::array<T, MaxGameObjects> components;

	std::unordered_map<GameObject, std::size_t> gameObjectToIndexMap;

	std::unordered_map<std::size_t, GameObject> indexToGameObjectMap;

	std::size_t elementCount;
};
