#pragma once
#include "GameObject.h"

#include "Model.h"
#include "ShaderProgram.h"

class GraphicsObject : public GameObject
{
public:

	GraphicsObject();

	~GraphicsObject();

	void SetShader(std::shared_ptr<ShaderProgram> shader);

	void SetModel(std::shared_ptr<Model> model);

	void Update(float dt);

	void Render(glm::mat4 parentModel, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:

	std::shared_ptr<ShaderProgram> shader;

	std::shared_ptr<Model> model;

};

