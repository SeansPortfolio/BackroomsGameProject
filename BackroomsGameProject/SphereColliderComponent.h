#pragma once
#include "Component.h"
class SphereColliderComponent : public Component
{
public:

	SphereColliderComponent(float radius);
	~SphereColliderComponent();

	virtual inline ComponentType GetType() const { return ComponentType::Collider; }


private:

	float Radius;
};

