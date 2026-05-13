#pragma once
#include "Scene.h"

#include "GraphicsObject.h"
#include "PhysicsObject.h"

class FallingShapesScene : public Scene
{
public:

	void Load();

	void Unload();

	void Update(float dt);

	void Render(float aspectRatio);

private:

	std::shared_ptr<GraphicsObject> CreatePhysicsCube();


};

