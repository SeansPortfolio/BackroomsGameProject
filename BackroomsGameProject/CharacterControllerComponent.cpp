#include "CharacterControllerComponent.h"

CharacterControllerComponent::CharacterControllerComponent(GameObject* gameObject) : Component(gameObject)
{
	physx::PxCapsuleControllerDesc desc;

	desc.height = 1.0f;
	desc.radius = 0.5f;
	desc.climbingMode = physx::PxCapsuleClimbingMode::eEASY;

	desc.position = physx::PxExtendedVec3(0, 1, 0);

	controller = Physics::CreateController(desc);
}

CharacterControllerComponent::~CharacterControllerComponent()
{

}

void CharacterControllerComponent::Update(float dt)
{
	physx::PxVec3 move(0, 0, 0);


	if (Input::IsKeyDown(KeyCode::KEYCODE_W))
	{
		move.x = 10 * dt;
		move.y = 0;
		move.z = 0;
	}
	
	controller->move(move, 0.01f, dt, NULL);
}
