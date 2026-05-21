#include "GameObject.h"

GameObject::GameObject() : GameObject(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)) { }

GameObject::GameObject(glm::vec3 pos) : GameObject(pos, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)) { }

GameObject::GameObject(glm::vec3 pos, glm::vec3 rot) : GameObject(pos, rot, glm::vec3(1, 1, 1)) { }

GameObject::GameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	Position = pos;
	Rotation = rot;
	Scale = scale;
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
	int numComponents = Components.size();
	for (int i = 0; i < numComponents; i++)
	{
		Components[i]->Update(dt);
	}

	int numChildren = Children.size();
	for (int i = 0; i < numChildren; i++)
	{
		Children[i]->Update(dt);
	}
}

void GameObject::Render(glm::mat4 parentModel, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	auto modelMatrix = GetModelMatrix(parentModel);

	int numComponents = Components.size();
	for (int i = 0; i < numComponents; i++)
	{
		Components[i]->Render(modelMatrix, viewMatrix, projectionMatrix);
	}

	int numChildren = Children.size();
	for (int i = 0; i < numChildren; i++)
	{
		Children[i]->Render(modelMatrix, viewMatrix, projectionMatrix);
	}
}

glm::mat4 GameObject::GetModelMatrix(glm::mat4 parent)
{
	glm::mat4 modelMatrix = glm::mat4(parent);

	modelMatrix = glm::translate(modelMatrix, Position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, Scale);

	return modelMatrix;
}
