#pragma once
#include "Scene.h"

class FallingShapesScene : public Scene
{
public:

	void Load();

	void Unload();

	void Update(float dt);

private:

	std::shared_ptr<OLDGameObject> CreateRandomCube(glm::vec3 pos);

	std::vector<const char*> CubeNames;

};

