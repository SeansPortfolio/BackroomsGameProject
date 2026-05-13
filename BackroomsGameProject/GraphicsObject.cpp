#include "GraphicsObject.h"

GraphicsObject::GraphicsObject()
{
}

GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::SetMesh(std::shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}

void GraphicsObject::SetShader(std::shared_ptr<ShaderProgram> shader)
{
	this->shader = shader;
}

void GraphicsObject::SetTexture(std::shared_ptr<Texture> texture)
{
	this->texture = texture;
}

void GraphicsObject::Update(float dt)
{

}

void GraphicsObject::Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	auto modelMatrix = GetModelMatrix();

	shader->Bind();

	shader->SetMat4("Projection", projectionMatrix);
	shader->SetMat4("View", viewMatrix);
	shader->SetMat4("Model", modelMatrix);

	texture->Bind(0);
	mesh->Bind();
}
