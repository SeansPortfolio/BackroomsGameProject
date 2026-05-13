#include "FallingShapesScene.h"

void FallingShapesScene::Load()
{

	Resources::Instance->LoadShader("UnlitTexture");
	Resources::Instance->LoadModel("Cube");

	SceneCam.Position = glm::vec3(0, 0.5f, -230);

}

void FallingShapesScene::Unload()
{

}

void FallingShapesScene::Update(float dt)
{

}

void FallingShapesScene::Render(float aspectRatio)
{

}
