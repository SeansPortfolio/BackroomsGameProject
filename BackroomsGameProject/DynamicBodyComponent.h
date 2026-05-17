#pragma once

#include "Physics.h"
#include "Component.h"

class DynamicBodyComponent : public Component
{
public:
	DynamicBodyComponent();

	~DynamicBodyComponent();

	virtual inline ComponentType GetType() const { return ComponentType::Rigidbody; }

private:

};

