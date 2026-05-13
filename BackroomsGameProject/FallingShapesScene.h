#pragma once
#include "Scene.h"

#include "GraphicsObject.h"
#include "PhysicsObject.h"

class FallingShapesScene : public Scene
{
public:

	void Load();

	void Unload();

	void LogicUpdate(float dt);

private:

	std::shared_ptr<GraphicsObject> CreatePhysicsCube();


};

