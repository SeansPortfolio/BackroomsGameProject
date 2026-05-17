#pragma once
#include "Scene.h"

class FallingShapesScene : public Scene
{
public:

	void Load();

	void Unload();

	void LogicUpdate(float dt);

private:

	std::vector<const char*> TextureNames;

};

