#include "Model.h"

void Model::Create(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvs, std::vector<std::vector<unsigned int>>& submeshes)
{
	auto submeshCount = submeshes.size();

	for (int i = 0; i < submeshCount; i++)
	{
		auto mesh = std::make_shared<Mesh>();
		mesh->Create(vertices, normals, uvs, submeshes[i]);
		Meshes.push_back(mesh);
	}
}

void Model::SetMaterials(std::vector<std::shared_ptr<Material>>& materials)
{
	Materials = materials;
}

void Model::Render()
{
	auto submeshCount = Meshes.size();

	for (int i = 0; i < submeshCount; i++)
	{

		Materials[i]->BindTextures();
		Meshes[i]->Bind();
	}


}

