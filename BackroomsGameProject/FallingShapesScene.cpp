#include "FallingShapesScene.h"

void FallingShapesScene::Load()
{
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



	SceneCam.Position = glm::vec3(0, -50, -10);
	SceneCam.Pitch = 50.0f;



	int stackZ = 0;
	for (int i = 0; i < 5; i++)
	{
		int size = 10;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - i; j++)
			{
				auto physObj = CreatePhysicsObject(glm::vec3(i * 3, j * 3, stackZ));

				//physObj->SetMesh(Resources::Instance->GetModel("Cube"));
				//physObj->SetTexture(Resources::Instance->GetTexture(TextureNames[(i + j) % TextureNames.size()]));
				physObj->SetShader(Resources::Instance->GetShader("UnlitTexture"));

				SceneObjects.push_back(physObj);
			}
		}

		stackZ -= 10;

	}
}

void FallingShapesScene::Unload()
{

}

void FallingShapesScene::LogicUpdate(float dt)
{
	Scene::LogicUpdate(dt);


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
