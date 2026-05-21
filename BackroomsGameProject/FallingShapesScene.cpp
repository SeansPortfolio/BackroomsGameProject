#include "FallingShapesScene.h"

void FallingShapesScene::Load()
{
	SceneCam.Position = glm::vec3(0, 0, -10);
	SceneCam.Pitch = 50.0f;

	CubeNames.push_back("BlackCube");
	CubeNames.push_back("BlueCube");
	CubeNames.push_back("GreenCube");
	CubeNames.push_back("OrangeCube");
	CubeNames.push_back("PinkCube");
	CubeNames.push_back("PurpleCube");
	CubeNames.push_back("RedCube");
	CubeNames.push_back("WhiteCube");
	CubeNames.push_back("YellowCube");

	int stackZ = 0;
	for (int i = 0; i < 5; i++)
	{
		int size = 10;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - i; j++)
			{
				auto cube = CreateRandomCube(glm::vec3(i * 3, j * 3 + 50.0f, stackZ));
				SceneObjects.push_back(cube);
			}
		}

		stackZ -= 10;

	}
}

void FallingShapesScene::Unload()
{

}

void FallingShapesScene::Update(float dt)
{
	Scene::Update(dt);


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
		SceneCam.Position += SceneCam.Forward * 100.0f * dt;
	}
	if (Input::IsKeyDown(KeyCode::KEYCODE_S))
	{
		SceneCam.Position -= SceneCam.Forward * 100.0f * dt;
	}
	if (Input::IsKeyDown(KeyCode::KEYCODE_A))
	{
		SceneCam.Position -= glm::normalize(glm::cross(SceneCam.Forward, SceneCam.Up)) * 200.0f * dt;
	}
	if (Input::IsKeyDown(KeyCode::KEYCODE_D))
	{
		SceneCam.Position += glm::normalize(glm::cross(SceneCam.Forward, SceneCam.Up)) * 200.0f * dt;
	}

}

std::shared_ptr<GameObject> FallingShapesScene::CreateRandomCube(glm::vec3 pos)
{
	auto cube = std::make_shared<GameObject>(pos);
	BoxColliderShape* floorCollider = new BoxColliderShape(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	auto cubeMesh = Resources::Instance->GetModel(CubeNames[rand() % CubeNames.size()]);
	auto shader = Resources::Instance->GetShader("UnlitTexture");
	cube->AddComponent<RendererComponent>(cubeMesh, shader);
	cube->AddComponent<DynamicRigidbodyComponent>(floorCollider);

	float randX = rand() % 600;
	float randY = rand() % 600;
	float randZ = rand() % 600;


	return cube;
}
