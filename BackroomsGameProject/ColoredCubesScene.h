#pragma once

#include "Scene.h"
#include "GraphicsObject.h"

#include <cstdlib>
#include <ctime>

class ColoredCubesScene : public Scene
{
public:

	ColoredCubesScene();

	~ColoredCubesScene();

	void Load();

	void Unload();

	void Update(float dt);

private:

	std::shared_ptr<GraphicsObject> CreateRandomCube();

	std::vector<const char*> TextureNames;
};

