#include "BackroomsLevel0Scene.h"

BackroomsLevel0Scene::BackroomsLevel0Scene()
{
}

BackroomsLevel0Scene::~BackroomsLevel0Scene()
{
}

void BackroomsLevel0Scene::Load()
{
	Resources::Instance->LoadModel("FloorCeiling");
	Resources::Instance->LoadShader("UnlitTexture");

	auto model = Resources::Instance->GetModel("FloorCeiling");
	auto shader = Resources::Instance->GetShader("UnlitTexture");

	auto floorTile = std::make_shared<GraphicsObject>();
	floorTile->SetModel(model);
	floorTile->SetShader(shader);

	SceneObjects.push_back(floorTile);

}

void BackroomsLevel0Scene::Unload()
{
}

void BackroomsLevel0Scene::LogicUpdate(float dt)
{
	auto mouseVector = Input::GetMouseMoveVector();

	SceneCam.Yaw += mouseVector.x * 100.0f * dt;
	SceneCam.Pitch -= mouseVector.y * 100.0f * dt;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (SceneCam.Pitch > 80.0f)
	{
		SceneCam.Pitch = 80.0f;
	}
	if (SceneCam.Pitch < -80.0f)
	{
		SceneCam.Pitch = -80.0f;
	}

	if (Input::IsKeyDown(KeyCode::KEYCODE_W))
	{
		SceneCam.Position += SceneCam.Forward * 10.0f * dt;
	}
	if (Input::IsKeyDown(KeyCode::KEYCODE_S))
	{
		SceneCam.Position -= SceneCam.Forward * 10.0f * dt;
	}
	if (Input::IsKeyDown(KeyCode::KEYCODE_A))
	{
		SceneCam.Position -= glm::normalize(glm::cross(SceneCam.Forward, SceneCam.Up)) * 20.0f * dt;
	}
	if (Input::IsKeyDown(KeyCode::KEYCODE_D))
	{
		SceneCam.Position += glm::normalize(glm::cross(SceneCam.Forward, SceneCam.Up)) * 20.0f * dt;
	}

}
