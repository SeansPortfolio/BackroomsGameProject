#include "ColoredCubesScene.h"

ColoredCubesScene::ColoredCubesScene()
{

}

ColoredCubesScene::~ColoredCubesScene()
{

}

void ColoredCubesScene::Load()
{
	srand(time(0));

	CubeNames.push_back("BlackCube");
	CubeNames.push_back("BlueCube");
	CubeNames.push_back("GreenCube");
	CubeNames.push_back("OrangeCube");
	CubeNames.push_back("PinkCube");
	CubeNames.push_back("PurpleCube");
	CubeNames.push_back("RedCube");
	CubeNames.push_back("WhiteCube");
	CubeNames.push_back("YellowCube");

	for (int i = 0; i < 200; i++)
	{
		auto cube = CreateRandomCube();
		SceneObjects.push_back(cube);
	}

	SceneCam.Position = glm::vec3(0, 0, -10);
}

void ColoredCubesScene::Unload()
{


}

void ColoredCubesScene::Update(float dt)
{

	this->Scene::Update(dt);

	for (int i = 0; i < SceneObjects.size(); i++)
	{
		SceneObjects[i]->Transform->Rotation.y += 100.0f * dt;
	}

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

	if (Input::IsKeyDown(KeyCode::KEYCODE_E))
	{
		SceneCam.Position += SceneCam.Up * 100.0f * dt;
	}
	if (Input::IsKeyDown(KeyCode::KEYCODE_Q))
	{
		SceneCam.Position -= SceneCam.Up * 100.0f * dt;
	}



}

std::shared_ptr<GameObject> ColoredCubesScene::CreateRandomCube()
{
	auto cube = std::make_shared<GameObject>();
	auto cubeMesh = Resources::Instance->GetModel(CubeNames[rand() % CubeNames.size()]);
	auto shader = Resources::Instance->GetShader("UnlitTexture");
	cube->AddComponent<RendererComponent>(cubeMesh, shader);

	float randX = rand() % 600;
	float randY = rand() % 600;
	float randZ = rand() % 600;

	cube->Transform->Position = glm::vec3(randX - 300, randY - 300, randZ - 300);

	randX = rand() % 360;
	randY = rand() % 360;
	randZ = rand() % 360;

	cube->Transform->Rotation = glm::vec3(randX, randY, randZ);

	randX = rand() % 200 / 10.0f + 1.0f;

	cube->Transform->Scale = glm::vec3(randX, randX, randX);

	return cube;
}
