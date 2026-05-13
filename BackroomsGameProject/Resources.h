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

	std::shared_ptr<Mesh> GetModel(const std::string);

private:

	const std::string LoadFileText(const std::string);

	const bool LoadObjFile(const std::string, std::vector<glm::vec3>&, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<unsigned int>&);

	const std::vector<int> SplitFaceString(const std::string&, const char);

	unsigned char* LoadFileImage(const std::string, int*, int*, int*);

	std::map<const std::string, std::shared_ptr<ShaderProgram>> Shaders;

	std::map<const std::string, std::shared_ptr<Texture>> Textures;

	std::map<const std::string, std::shared_ptr<Mesh>> Models;

};

