#include "GameObject.h"

GameObject::GameObject()
{
	Position = glm::vec3(0, 0, 0);
	Rotation = glm::vec3(0, 0, 0);
	Scale = glm::vec3(1, 1, 1);
}

GameObject::~GameObject()
{

}

glm::mat4 GameObject::GetModelMatrix()
{
	return GetModelMatrix(glm::mat4(1.0f));
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

void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	Children.push_back(child);
}

void GameObject::Update(float dt)
{
	int numChildren = Children.size();
	for (int i = 0; i < numChildren; i++)
	{
		Children[i]->Update(dt);
	}
}