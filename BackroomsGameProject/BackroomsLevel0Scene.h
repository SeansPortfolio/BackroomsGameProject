#pragma once

#include "Scene.h"

class BackroomsLevel0Scene : public Scene
{
public:


	BackroomsLevel0Scene();

	~BackroomsLevel0Scene();

	void Load();

	void Unload();

	void Update(float dt);



private:

	std::shared_ptr<GameObject> Player;

};

