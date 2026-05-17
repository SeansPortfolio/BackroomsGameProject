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
	Resources::Instance->LoadModel("Wall");
	Resources::Instance->LoadModel("DoorFrame");

	Resources::Instance->LoadShader("UnlitTexture");

	int mapSize = 10;

	// create the floor
	{
		auto model = Resources::Instance->GetModel("FloorCeiling");
		auto shader = Resources::Instance->GetShader("UnlitTexture");

		for (int x = 0; x < mapSize; x++)
		{
			for (int z = 0; z < mapSize; z++)
			{
				auto floorTile = std::make_shared<GameObject>();
				floorTile->Position = glm::vec3(x * 10, 0, z * 10);
				floorTile->AddComponent<RendererComponent>(model, shader);

				SceneObjects.push_back(floorTile);

				auto roofTile = std::make_shared<GameObject>();
				roofTile->Position = glm::vec3(x * 10, 10, z * 10);
				roofTile->AddComponent<RendererComponent>(model, shader);

				SceneObjects.push_back(roofTile);

			}
		}
	}

	// create the walls
	{
		auto model = Resources::Instance->GetModel("Wall");
		auto shader = Resources::Instance->GetShader("UnlitTexture");

		for (int x = 0; x < mapSize; x++)
		{
			auto wallTile = std::make_shared<GameObject>();
			wallTile->Position = glm::vec3(x * 10, 0, mapSize * 10 - 5.0f);
			wallTile->Rotation = glm::vec3(0, 90, 0);
			wallTile->AddComponent<RendererComponent>(model, shader);

			SceneObjects.push_back(wallTile);

			wallTile = std::make_shared<GameObject>();
			wallTile->Position = glm::vec3(x * 10, 0, -5.0f);
			wallTile->Rotation = glm::vec3(0, 90, 0);
			wallTile->AddComponent<RendererComponent>(model, shader);

			SceneObjects.push_back(wallTile);
		}

		for (int z = 0; z < mapSize; z++)
		{
			auto wallTile = std::make_shared<GameObject>();
			wallTile->Position = glm::vec3(mapSize * 10 - 5.0f, 0, z * 10);
			wallTile->AddComponent<RendererComponent>(model, shader);

			SceneObjects.push_back(wallTile);

			wallTile = std::make_shared<GameObject>();
			wallTile->Position = glm::vec3(-5.0f, 0, z * 10);
			wallTile->AddComponent<RendererComponent>(model, shader);

			SceneObjects.push_back(wallTile);
		}
	}

	// create center divider
	{
		auto model = Resources::Instance->GetModel("Wall");
		auto door = Resources::Instance->GetModel("DoorFrame");
		auto shader = Resources::Instance->GetShader("UnlitTexture");

		int x = 3 * 10;
		for (int z = 0; z < mapSize; z++)
		{
			if (z == 3)
			{
				continue;
			}

			auto wallTile = std::make_shared<GameObject>();
			wallTile->Position = glm::vec3(x - 5.0f, 0, z * 10);
			wallTile->AddComponent<RendererComponent>(model, shader);

			SceneObjects.push_back(wallTile);
		}

		auto doorFrame = std::make_shared<GameObject>();
		doorFrame->Position = glm::vec3(x - 5.0f, 0, 3 * 10);
		doorFrame->AddComponent<RendererComponent>(model, shader);

		//SceneObjects.push_back(doorFrame);
	}

	// create center divider
	{
		auto model = Resources::Instance->GetModel("Wall");
		auto door = Resources::Instance->GetModel("DoorFrame");
		auto shader = Resources::Instance->GetShader("UnlitTexture");

		int x = 6 * 10;
		for (int z = 0; z < mapSize; z++)
		{
			if (z == 6)
			{
				continue;
			}

			auto wallTile = std::make_shared<GameObject>();
			wallTile->Position = glm::vec3(x - 5.0f, 0, z * 10);
			wallTile->AddComponent<RendererComponent>(model, shader);

			SceneObjects.push_back(wallTile);
		}

		auto doorFrame = std::make_shared<GameObject>();
		doorFrame->Position = glm::vec3(x - 5.0f, 0, 6 * 10);
		doorFrame->AddComponent<RendererComponent>(model, shader);

		//SceneObjects.push_back(doorFrame);
	}

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
