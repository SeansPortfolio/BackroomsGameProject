#pragma once

#include "Physics.h"
#include "Component.h"
#include "Input.h"

class CharacterControllerComponent : public Component
{
public:
	CharacterControllerComponent(GameObject* gameObject);
	~CharacterControllerComponent();

	virtual void Update(float dt);

private:

	physx::PxController* controller;

};

