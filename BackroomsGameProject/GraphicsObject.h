#pragma once
#include "GameObject.h"

#include "Mesh.h"
#include "Texture.h"
#include "ShaderProgram.h"

class GraphicsObject : public GameObject
{
public:

	GraphicsObject();
	~GraphicsObject();

	void SetMesh(std::shared_ptr<Mesh> mesh);

	void SetShader(std::shared_ptr<ShaderProgram> shader);

	void SetTexture(std::shared_ptr<Texture> texture);

	void Update(float dt);

	void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:

	std::shared_ptr<Mesh> mesh;

	std::shared_ptr<ShaderProgram> shader;

	std::shared_ptr<Texture> texture;



};

