#include "FallingShapesScene.h"

void FallingShapesScene::Load()
{

	Resources::Instance->LoadShader("UnlitTexture");
	Resources::Instance->LoadModel("Cube");
	Resources::Instance->LoadTexture("SolidRed");

	SceneCam.Position = glm::vec3(0, -50, -10);
	SceneCam.Pitch = 50.0f;

	auto cube = CreatePhysicsCube();
	SceneObjects.push_back(cube);
	fallingShape = cube;

}

void FallingShapesScene::Unload()
{

}

void FallingShapesScene::Update(float dt)
{

	auto actor = Physics::physObjects[0];

	// Get the global pose (position + orientation)
	physx::PxTransform transform = actor->getGlobalPose();

	physx::PxVec3 position = transform.p;
	auto rotation = transform.q;

	fallingShape->Position.x = position.x;
	fallingShape->Position.y = position.y;
	fallingShape->Position.z = position.z;


}

void FallingShapesScene::Render(float aspectRatio)
{
	this->Scene::Render(aspectRatio);

}

std::shared_ptr<GraphicsObject> FallingShapesScene::CreatePhysicsCube()
{
	auto cube = std::make_shared<GraphicsObject>();
	auto cubeMesh = Resources::Instance->GetModel("Cube");
	auto shader = Resources::Instance->GetShader("UnlitTexture");

	cube->SetMesh(cubeMesh);
	cube->SetShader(shader);

	int randomValue = rand() % 7;
	cube->SetTexture(Resources::Instance->GetTexture("SolidRed"));

	float randX = rand() % 600;
	float randY = rand() % 600;
	float randZ = rand() % 600;

	return cube;
}
