#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Resources.h"

#include "Input.h"
#include "Physics.h"

#include <vector>
#include <queue>
#include <array>

class Scene
{
public:

	virtual void Init();

	virtual void Load() = 0;

	virtual void Unload() = 0;

	virtual void Update(float dt);

	virtual void Render(float aspectRatio);

	GameObject CreateGameObject();

	bool DestroyGameObjectWithID(GameObject id);

	void SetGameObjectComponents(GameObject id, ComponentMask signature);

	ComponentMask GetComponentMask(GameObject id);




protected:

	std::uint32_t activeGameObjects;

	std::queue<GameObject> availableIDs;

	std::vector<std::shared_ptr<OLDGameObject>> SceneObjects;

	std::array<ComponentMask, MaxGameObjects> ComponentMasks;

	Camera SceneCam;

};

