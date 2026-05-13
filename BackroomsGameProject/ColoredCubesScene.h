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

	void Render(float aspectRatio);

private:

	std::shared_ptr<GraphicsObject> CreateRandomCube();

	std::vector<const char*> TextureNames;
};

