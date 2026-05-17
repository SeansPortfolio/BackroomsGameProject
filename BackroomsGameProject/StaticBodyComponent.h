#pragma once
#include "Component.h"
class StaticBodyComponent : public Component
{
public:

	virtual inline ComponentType GetType() const { return ComponentType::Rigidbody; }


private:


};

