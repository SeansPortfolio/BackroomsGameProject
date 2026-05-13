#pragma once

#include <vector>
#include <glm.hpp>
#include <Gl\glew.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct VertexPositionTexture
{
	glm::vec3 Position;

	glm::vec2 TexCoord;
};

struct VertexPositionNormalTexture
{
	glm::vec3 Position;

	glm::vec2 TexCoord;

	glm::vec3 Normal;
};

class Mesh
{
public:

	void Create(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices);

	void Create(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indices);
	
	void Create(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indices);

	void Bind();

	void Unbind();


private:

	unsigned int VAO;

	IndexBuffer EBO;
	VertexBuffer VBO;
};

