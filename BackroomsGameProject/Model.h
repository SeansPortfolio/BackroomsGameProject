#pragma once

#include "Mesh.h"
#include "Material.h"

class Model
{
public:

	void Create(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvs, std::vector<std::vector<unsigned int>>& submeshes);

	void SetMaterials(std::vector<std::shared_ptr<Material>>& materials);

	void Render();

private:

	std::vector<std::shared_ptr<Mesh>> Meshes;

	std::vector<std::shared_ptr<Material>> Materials;
};

