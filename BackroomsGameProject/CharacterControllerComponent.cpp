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
	glm::vec3 forward = gameObject->GetForward();
	glm::vec3 move(0, 0, 0);
	glm::vec3 up(0, 1, 0);

	if (Input::IsKeyDown(KeyCode::KEYCODE_W))
	{
		move += forward;
	}
	if (Input::IsKeyDown(KeyCode::KEYCODE_S))
	{
		move += forward * -1.0f;
	}

	if (Input::IsKeyDown(KeyCode::KEYCODE_A))
	{
		move += glm::cross(forward, up) * -1.0f;
	}
	if (Input::IsKeyDown(KeyCode::KEYCODE_D))
	{
		move += glm::cross(forward, up);
	}

	if (glm::abs(move.x) > 0.1f || glm::abs(move.z) > 0.1f)
	{
		move = glm::normalize(move) * 10.0f * dt;
	}

	physx::PxVec3 moveVector(move.x, 0, move.z);

	controller->move(moveVector, 0.01f, dt, NULL);
	gameObject->SetPosition(Physics::ConvertPosition(controller->getPosition()));
}
