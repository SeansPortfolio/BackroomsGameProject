#pragma once
#include "Scene.h"

class FallingShapesScene : public Scene
{
public:

	void Load();

	void Unload();

	void Update(float dt);

private:

	std::vector<const char*> TextureNames;

};

