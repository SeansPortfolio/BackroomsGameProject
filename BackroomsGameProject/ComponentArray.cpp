#include "ComponentArray.h"

template<typename T>
inline void ComponentArray<T>::AddComponent(GameObject id, T component)
{
	if (gameObjectToIndexMap.find(id) != gameObjectToIndexMap.end())
	{
		return;
	}

	std::size_t newIndex = elementCount;
	gameObjectToIndexMap[id] = newIndex;
	indexToGameObjectMap[newIndex] = id;
	components[newIndex] = component;
	elementCount++;

}

template<typename T>
inline void ComponentArray<T>::RemoveComponent(GameObject id)
{
	std::size_t indexOfRemovedEntity = gameObjectToIndexMap[id];
	std::size_t indexOfLastElement = elementCount - 1;
	components[indexOfRemovedEntity] = components[indexOfLastElement];

	GameObject previousID = indexToGameObjectMap[indexOfLastElement];
	gameObjectToIndexMap[previousID] = indexOfRemovedEntity;
	indexToGameObjectMap[indexOfRemovedEntity] = previousID;

	gameObjectToIndexMap.erase(id);
	indexToGameObjectMap.erase(indexOfLastElement);

	elementCount--;
}

template<typename T>
inline T& ComponentArray<T>::GetComponent(GameObject id)
{
	return components[gameObjectToIndexMap[id]];
}

template<typename T>
inline void ComponentArray<T>::OnGameObjectDestroyed(GameObject id)
{
	if (gameObjectToIndexMap.find(id) != gameObjectToIndexMap.end())
	{
		RemoveComponent(id);
	}
}
