#include "GraphicsObject.h"

GraphicsObject::GraphicsObject()
{
}

GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::SetShader(std::shared_ptr<ShaderProgram> shader)
{
	this->shader = shader;
}

void GraphicsObject::SetModel(std::shared_ptr<Model> model)
{
	this->model = model;
}

void GraphicsObject::Update(float dt)
{
	GameObject::Update(dt);
}

void GraphicsObject::Render(glm::mat4 parentModel, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	auto modelMatrix = GetModelMatrix(parentModel);

	shader->Bind();

	shader->SetMat4("Projection", projectionMatrix);
	shader->SetMat4("View", viewMatrix);
	shader->SetMat4("Model", modelMatrix);

	shader->SetInt("image", 0);
	model->Render();

	shader->Unbind();

	int numChildren = Children.size();
	for (int i = 0; i < numChildren; i++)
	{
		Children[i]->Render(modelMatrix, viewMatrix, projectionMatrix);
	}

}
