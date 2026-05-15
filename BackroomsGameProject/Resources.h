#pragma once

#include <map>
#include <memory>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "ShaderProgram.h"
#include "Texture.h"
#include "Model.h"
#include "Mesh.h"

class Resources
{
public:

	static std::unique_ptr<Resources> Instance;

	static void Init();

	bool LoadShader(const std::string);

	bool LoadTexture(const std::string);

	bool LoadModel(const std::string);

	std::shared_ptr<ShaderProgram> GetShader(const std::string);

	std::shared_ptr<Texture> GetTexture(const std::string);

	std::shared_ptr<Model> GetModel(const std::string);

private:


	const std::string LoadFileText(const std::string path, const char* fileExtension);

	const bool LoadObjFile(const std::string path, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texcoords, std::vector<std::vector<unsigned int>>& submeshes);

	const bool LoadMtlFile(const std::string path, std::vector<std::shared_ptr<Material>>& materials);

	const std::vector<int> SplitFaceString(const std::string&, const char);

	unsigned char* LoadFileImage(const std::string, int*, int*, int*);

	std::map<const std::string, std::shared_ptr<ShaderProgram>> Shaders;

	std::map<const std::string, std::shared_ptr<Texture>> Textures;

	std::map<const std::string, std::shared_ptr<Model>> Models;







	const char* modelFileExtension = ".obj";

	const char* materialFileExtension = ".mtl";

	const char* textureFileExtension = ".png";

	const char* vertexShaderExtension = ".vert";

	const char* fragmentShaderExtension = ".frag";

};