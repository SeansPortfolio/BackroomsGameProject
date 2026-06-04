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

void RendererComponent::Render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	shader->Bind();

	shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->SetVec3("lightPos", glm::vec3(5.0f, 2.5f, 5.0f));


	shader->SetMat4("Projection", projectionMatrix);
	shader->SetMat4("View", viewMatrix);
	shader->SetMat4("Model", modelMatrix);

	shader->SetInt("image", 0);
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
