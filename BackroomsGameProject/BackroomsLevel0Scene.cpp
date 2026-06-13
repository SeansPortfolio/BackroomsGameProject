#include "BackroomsLevel0Scene.h"

BackroomsLevel0Scene::BackroomsLevel0Scene()
{
}

BackroomsLevel0Scene::~BackroomsLevel0Scene()
{
}

void BackroomsLevel0Scene::Load()
{
	int mapSize = 10;

	BoxColliderShape* floorCollider = new BoxColliderShape(glm::vec3(0, 0, 0), glm::vec3(5.0f, 0.25f, 5.0f));
	BoxColliderShape* wallCollider = new BoxColliderShape(glm::vec3(0, 5.0f, 0), glm::vec3(0.25f, 5.0f, 5.0f));

	// create the floor
	{
		auto model = Resources::Instance->GetModel("FloorCeiling");
		auto shader = Resources::Instance->GetShader("LitTexture");

		for (int x = 0; x < mapSize; x++)
		{
			for (int z = 0; z < mapSize; z++)
			{
				auto floorTile = std::make_shared<GameObject>();
				floorTile->SetPosition(glm::vec3(x * 10, 0, z * 10));
				floorTile->AddComponent<RendererComponent>(model, shader);
				floorTile->AddComponent<StaticRigidbodyComponent>(floorCollider);

				SceneObjects.push_back(floorTile);

				auto roofTile = std::make_shared<GameObject>();
				roofTile->SetPosition(glm::vec3(x * 10, 10, z * 10));
				roofTile->AddComponent<RendererComponent>(model, shader);
				roofTile->AddComponent<StaticRigidbodyComponent>(floorCollider);

				SceneObjects.push_back(roofTile);

			}
		}
	}

	// create the walls
	{
		auto model = Resources::Instance->GetModel("Wall");
		auto shader = Resources::Instance->GetShader("LitTexture");

		for (int x = 0; x < mapSize; x++)
		{
			auto wallTile = std::make_shared<GameObject>();
			wallTile->SetPosition(glm::vec3(x * 10, 0, mapSize * 10 - 5.0f));
			wallTile->SetRotation(glm::vec3(0, 90, 0));
			wallTile->AddComponent<RendererComponent>(model, shader);
			wallTile->AddComponent<StaticRigidbodyComponent>(wallCollider);

			SceneObjects.push_back(wallTile);

			wallTile = std::make_shared<GameObject>();
			wallTile->SetPosition(glm::vec3(x * 10, 0, -5.0f));
			wallTile->SetRotation(glm::vec3(0, 90, 0));
			wallTile->AddComponent<RendererComponent>(model, shader);
			wallTile->AddComponent<StaticRigidbodyComponent>(wallCollider);

			SceneObjects.push_back(wallTile);
		}

		for (int z = 0; z < mapSize; z++)
		{
			auto wallTile = std::make_shared<GameObject>();
			wallTile->SetPosition(glm::vec3(mapSize * 10 - 5.0f, 0, z * 10));
			wallTile->AddComponent<RendererComponent>(model, shader);
			wallTile->AddComponent<StaticRigidbodyComponent>(wallCollider);

			SceneObjects.push_back(wallTile);

			wallTile = std::make_shared<GameObject>();
			wallTile->SetPosition(glm::vec3(-5.0f, 0, z * 10));
			wallTile->AddComponent<RendererComponent>(model, shader);
			wallTile->AddComponent<StaticRigidbodyComponent>(wallCollider);

			SceneObjects.push_back(wallTile);
		}
	}

	// create center divider
	{
		auto model = Resources::Instance->GetModel("Wall");
		auto door = Resources::Instance->GetModel("DoorFrame");
		auto shader = Resources::Instance->GetShader("LitTexture");

		int x = 3 * 10;
		for (int z = 0; z < mapSize; z++)
		{
			if (z == 3)
			{
				continue;
			}

			auto wallTile = std::make_shared<GameObject>();
			wallTile->SetPosition(glm::vec3(x - 5.0f, 0, z * 10));
			wallTile->AddComponent<RendererComponent>(model, shader);
			wallTile->AddComponent<StaticRigidbodyComponent>(wallCollider);

			SceneObjects.push_back(wallTile);
		}

		auto doorFrame = std::make_shared<GameObject>();
		doorFrame->SetPosition(glm::vec3(x - 5.0f, 0, 3 * 10));
		doorFrame->AddComponent<RendererComponent>(door, shader);

		SceneObjects.push_back(doorFrame);
	}

	// create center divider
	{
		auto model = Resources::Instance->GetModel("Wall");
		auto door = Resources::Instance->GetModel("DoorFrame");
		auto shader = Resources::Instance->GetShader("LitTexture");

		int x = 6 * 10;
		for (int z = 0; z < mapSize; z++)
		{
			if (z == 6)
			{
				continue;
			}

			auto wallTile = std::make_shared<GameObject>();
			wallTile->SetPosition(glm::vec3(x - 5.0f, 0, z * 10));
			wallTile->AddComponent<RendererComponent>(model, shader);
			wallTile->AddComponent<StaticRigidbodyComponent>(wallCollider);

			SceneObjects.push_back(wallTile);
		}

		auto doorFrame = std::make_shared<GameObject>();
		doorFrame->SetPosition(glm::vec3(x - 5.0f, 0, 6 * 10));
		doorFrame->AddComponent<RendererComponent>(door, shader);

		SceneObjects.push_back(doorFrame);
	}

	auto model = Resources::Instance->GetModel("WhiteCube");
	auto shader = Resources::Instance->GetShader("UnlitTexture");

	auto lightSource = std::make_shared<GameObject>();
	lightSource->SetPosition(glm::vec3(5.0f, 2.5f, 5.0f));
	lightSource->AddComponent<RendererComponent>(model, shader);
	SceneObjects.push_back(lightSource);

	lightSource = std::make_shared<GameObject>();
	lightSource->SetPosition(glm::vec3(75.0f, 2.5f, 75.0f));
	lightSource->AddComponent<RendererComponent>(model, shader);
	lightSource->AddComponent<PointLightComponent>(glm::vec3(1.0f, 1.0f, 1.0f), 20.0f);
	SceneObjects.push_back(lightSource);

	Player = std::make_shared<GameObject>(glm::vec3(0, 2, 0));
	Player->AddComponent<CharacterControllerComponent>();
	Player->AddComponent<CameraComponent>();

	SceneCam = Player->GetComponent<CameraComponent>();
	SceneObjects.push_back(Player);

	delete wallCollider;
	delete floorCollider;

	wallCollider = NULL;
	floorCollider = NULL;
}

void BackroomsLevel0Scene::Unload()
{
}

void BackroomsLevel0Scene::Update(float dt)
{
	Scene::Update(dt);

	auto mouseVector = Input::GetMouseMoveVector();
	auto cam = Player->GetComponent<CameraComponent>();
	auto rotation = Player->GetRotation();

	rotation.y += mouseVector.x * 100.0f * dt;
	rotation.x -= mouseVector.y * 100.0f * dt;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (rotation.x > 80.0f)
	{
		rotation.x = 80.0f;
	}
	if (rotation.x < -80.0f)
	{
		rotation.x = -80.0f;
	}
	
	Player->SetRotation(rotation);
}
