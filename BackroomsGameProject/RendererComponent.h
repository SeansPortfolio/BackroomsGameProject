#pragma once

#include "Component.h"

#include "Model.h"
#include "ShaderProgram.h"

class RendererComponent : public Component
{
public:

	RendererComponent(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shader);

	virtual void Update(float dt);

	virtual void Render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	virtual inline ComponentType GetType() const { return ComponentType::Renderer; }

	void SetShader(std::shared_ptr<ShaderProgram> shader);

	void SetModel(std::shared_ptr<Model> model);

private:


	std::shared_ptr<ShaderProgram> shader;

	std::shared_ptr<Model> model;


};

