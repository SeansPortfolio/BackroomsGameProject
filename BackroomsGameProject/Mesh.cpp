#include "Mesh.h"

void Mesh::Create(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices)
{
	VAO = 0;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO.Create(vertices.data(), vertices.size() * sizeof(glm::vec3));
	EBO.Create(indices.data(), indices.size());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::Create(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indices)
{
	std::vector<VertexPositionTexture> combinedVertices;

	for (size_t i = 0; i < vertices.size(); i++)
	{
		combinedVertices.push_back({ vertices[i], uvs[i] });
	}

	VAO = 0;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO.Create(combinedVertices.data(), combinedVertices.size() * (sizeof(glm::vec3) + sizeof(glm::vec2)));
	EBO.Create(indices.data(), indices.size());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexture), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexture), (void*)(offsetof(VertexPositionTexture, TexCoord)));
	glEnableVertexAttribArray(1);
}

void Mesh::Create(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indices)
{
	std::vector<VertexPositionNormalTexture> combinedVertices;

	for (size_t i = 0; i < vertices.size(); i++)
	{
		combinedVertices.push_back({ vertices[i], uvs[i],normals[i] });
	}

	VAO = 0;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO.Create(combinedVertices.data(), combinedVertices.size() * (sizeof(glm::vec3) + sizeof(glm::vec3) + sizeof(glm::vec2)));
	EBO.Create(indices.data(), indices.size());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormalTexture), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormalTexture), (void*)(offsetof(VertexPositionNormalTexture, TexCoord)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionNormalTexture), (void*)(offsetof(VertexPositionNormalTexture, Normal)));
	glEnableVertexAttribArray(2);

}

void Mesh::Bind()
{
	glBindVertexArray(VAO);
	EBO.Bind();
}

void Mesh::Unbind()
{
	glBindVertexArray(0);
}
