#pragma once

#include "Physics.h"
#include "Component.h"
#include "Input.h"

class CharacterControllerComponent : public Component
{
public:
	CharacterControllerComponent(OLDGameObject* gameObject);
	~CharacterControllerComponent();

	virtual void Update(float dt);

	virtual inline OLDComponentType GetType() const { return OLDComponentType::Controller; }

private:

	physx::PxController* controller;

};

