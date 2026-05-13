#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Resources.h"

#include "Input.h"
#include "Physics.h"

#include <vector>


class Scene
{
public:

	virtual void Load() = 0;

	virtual void Unload() = 0;

	void InitPhysics();

	virtual void PhysicsUpdate(float dt);

	virtual void LogicUpdate(float dt);

	virtual void Render(float aspectRatio);

protected:

	std::vector<std::shared_ptr<GameObject>> SceneObjects;

	std::shared_ptr<GameObject> fallingShape;

	Camera SceneCam;

private:

	std::unique_ptr<Physics> PhysicsSystem;

};

