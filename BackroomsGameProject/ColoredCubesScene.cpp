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

	Resources::Instance->LoadShader("UnlitTexture");
	Resources::Instance->LoadModel("Cube");

	TextureNames.push_back("SolidBlack");
	TextureNames.push_back("SolidBlue");
	TextureNames.push_back("SolidGreen");
	TextureNames.push_back("SolidPurple");
	TextureNames.push_back("SolidRed");
	TextureNames.push_back("SolidYellow");
	TextureNames.push_back("SolidWhite");

	for (int i = 0; i < TextureNames.size(); i++)
	{
		Resources::Instance->LoadTexture(TextureNames[i]);
	}

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

void ColoredCubesScene::LogicUpdate(float dt)
{

	this->Scene::LogicUpdate(dt);

	for (int i = 0; i < SceneObjects.size(); i++)
	{
		SceneObjects[i]->Rotation.y += 100.0f * dt;
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

std::shared_ptr<GraphicsObject> ColoredCubesScene::CreateRandomCube()
{
	auto cube = std::make_shared<GraphicsObject>();
	auto cubeMesh = Resources::Instance->GetModel("Cube");
	auto shader = Resources::Instance->GetShader("UnlitTexture");

	cube->SetMesh(cubeMesh);
	cube->SetShader(shader);

	int randomValue = rand() % 7;
	cube->SetTexture(Resources::Instance->GetTexture(TextureNames[randomValue]));

	float randX = rand() % 600;
	float randY = rand() % 600;
	float randZ = rand() % 600;

	cube->Position = glm::vec3(randX - 300, randY - 300, randZ - 300);

	randX = rand() % 360;
	randY = rand() % 360;
	randZ = rand() % 360;

	cube->Rotation = glm::vec3(randX, randY, randZ);

	randX = rand() % 200 / 10.0f + 1.0f;

	cube->Scale = glm::vec3(randX, randX, randX);

	return cube;
}
