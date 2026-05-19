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

	virtual inline ComponentType GetType() const { return ComponentType::Controller; }

private:

	physx::PxController* controller;

};

