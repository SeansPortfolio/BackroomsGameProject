#include "GameObject.h"

GameObject::GameObject() : GameObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1))
{

}


GameObject::GameObject(glm::vec3 pos) : GameObject(pos, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1))
{

}

GameObject::GameObject(glm::vec3 pos, glm::vec3 rot) : GameObject(pos, rot, glm::vec3(1, 1, 1))
{

}

GameObject::GameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	Transform = std::make_unique<TransformComponent>(pos, rot, scale);
	Transform->Position = pos;
	Transform->Rotation = rot;
	Transform->Scale = scale;


	//AddComponent<TransformComponent>(pos, rot, scale);
}

GameObject::~GameObject()
{

}

void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	Children.push_back(child);
}

void GameObject::Update(float dt)
{
	int numComponents = components.size();
	for (int i = 0; i < numComponents; i++)
	{
		components[i]->Update(dt);
	}

	int numChildren = Children.size();
	for (int i = 0; i < numChildren; i++)
	{
		Children[i]->Update(dt);
	}
}

void GameObject::Render(glm::mat4 parentModel, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	auto modelMatrix = Transform->GetModelMatrix(parentModel);

	int numComponents = components.size();
	for (int i = 0; i < numComponents; i++)
	{
		components[i]->Render(modelMatrix, viewMatrix, projectionMatrix);
	}

	int numChildren = Children.size();
	for (int i = 0; i < numChildren; i++)
	{
		Children[i]->Render(modelMatrix, viewMatrix, projectionMatrix);
	}
}
