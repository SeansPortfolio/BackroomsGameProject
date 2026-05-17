#pragma once

#include "Scene.h"

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

	std::shared_ptr<GameObject> CreateRandomCube();

	std::vector<const char*> CubeNames;


};

