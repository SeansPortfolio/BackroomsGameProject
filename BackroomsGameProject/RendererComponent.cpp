#include "RendererComponent.h"

RendererComponent::RendererComponent(GameObject* gameObject, std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shader) : Component(gameObject)
{
	SetShader(shader);
	SetModel(model);
}

void RendererComponent::Update(float dt)
{
	// nothing to be done.
}

void RendererComponent::Render(glm::mat4 modelMatrix)
{
	shader->Bind();

	shader->SetMat4("Model", modelMatrix);
	model->Render();

	shader->Unbind();
}

void RendererComponent::SetShader(std::shared_ptr<ShaderProgram> shader)
{
	this->shader = shader;
}

void RendererComponent::SetModel(std::shared_ptr<Model> model)
{
	this->model = model;
}
