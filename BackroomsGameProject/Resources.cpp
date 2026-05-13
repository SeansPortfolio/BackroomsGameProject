#include "Resources.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include <stb_image.h>

std::unique_ptr<Resources> Resources::Instance;

void Resources::Init()
{
	stbi_set_flip_vertically_on_load(true);
	Instance = std::make_unique<Resources>();
}

bool Resources::LoadShader(const std::string name)
{
	if (Shaders[name] != NULL)
	{
		printf("ERROR: Resources already contains a shader named %s\n", name.c_str());
		return false;
	}

	auto vertexSource = LoadFileText("Resources\\Shaders\\" + name + ".vert");
	auto fragmentSource = LoadFileText("Resources\\Shaders\\" + name + ".frag");

	if (vertexSource.empty() || fragmentSource.empty())
	{
		return false;
	}

	auto shader = std::make_shared<ShaderProgram>();

	if (shader->LoadFromSource(vertexSource.c_str(), fragmentSource.c_str()))
	{
		Shaders[name] = shader;
		return true;
	}

	printf("ERROR: Failed to load shader: %s\n Source: %s\n %s", name.c_str(), vertexSource.c_str(), fragmentSource.c_str());
	return false;
}

bool Resources::LoadTexture(const std::string name)
{
	if (Textures[name] != NULL)
	{
		printf("ERROR: Resources already contains a texture named %s\n", name.c_str());
		return false;
	}

	int width, height, channels;
	auto imageData = LoadFileImage("Resources\\Textures\\" + name + ".png", &width, &height, &channels);

	if (imageData != NULL)
	{
		auto texture = std::make_shared<Texture>();
		texture->Create(imageData, width, height);
		Textures[name] = texture;

		stbi_image_free(imageData);

		return true;
	}

	return false;
}

bool Resources::LoadModel(const std::string name)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<unsigned int> indices;

	if (Models[name] != NULL)
	{
		printf("ERROR: Resources already contains a model named %s\n", name.c_str());
		return false;
	}

	if (LoadObjFile("Resources\\Models\\" + name + ".obj", vertices, normals, texcoords, indices))
	{
		auto mesh = std::make_shared<Mesh>();
		mesh->Create(vertices, normals, texcoords, indices);

		Models[name] = mesh;
		return true;
	}

	return false;
}

std::shared_ptr<ShaderProgram> Resources::GetShader(const std::string name)
{
	return Shaders[name];
}

std::shared_ptr<Texture> Resources::GetTexture(const std::string name)
{
	return Textures[name];
}

std::shared_ptr<Mesh> Resources::GetModel(const std::string name)
{
	return Models[name];
}

const std::string Resources::LoadFileText(const std::string path)
{
	std::ifstream FILE(path);

	if (!FILE.is_open())
	{
		printf("ERROR: File not found: %s\n", path.c_str());
		return "";
	}

	std::string line;
	std::string fileText;

	while (std::getline(FILE, line))
	{
		fileText += line + '\n';
	}

	return fileText;
}

const bool Resources::LoadObjFile(const std::string path, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texcoords, std::vector<unsigned int>& indices)
{
	std::ifstream FILE(path);

	if (!FILE.is_open())
	{
		printf("ERROR: File not found: %s\n", path.c_str());
		return false;
	}

	int faceCount = 0;

	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec3> tempNormals;
	std::vector<glm::vec2> tempTexcoords;

	std::string line;
	while (std::getline(FILE, line))
	{
		if (line[0] == '#')
		{
			continue;
		}

		std::istringstream ss(line);
		std::string type;
		ss >> type;

		if (type == "v")
		{
			glm::vec3 vertex;
			ss >> vertex.x >> vertex.y >> vertex.z;

			tempVertices.push_back(vertex);
		}
		if (type == "vn")
		{
			glm::vec3 normal;
			ss >> normal.x >> normal.y >> normal.z;

			tempNormals.push_back(normal);
		}
		if (type == "vt")
		{
			glm::vec3 texture;
			ss >> texture.x >> texture.y;

			tempTexcoords.push_back(texture);
		}
		if (type == "f")
		{
			// format: f 1/2/3
			// vertex/texture coordinate/normal
			// this data represents each triangle face of the mesh.
			// need to combine vertices with the new meshes.

			std::string v1, v2, v3;
			ss >> v1 >> v2 >> v3;

			auto point1 = SplitFaceString(v1, '/');
			auto point2 = SplitFaceString(v2, '/');
			auto point3 = SplitFaceString(v3, '/');

			indices.push_back(faceCount + 0);
			indices.push_back(faceCount + 1);
			indices.push_back(faceCount + 2);

			vertices.push_back(tempVertices[point1[0] - 1]);
			vertices.push_back(tempVertices[point2[0] - 1]);
			vertices.push_back(tempVertices[point3[0] - 1]);

			texcoords.push_back(tempTexcoords[point1[1] - 1]);
			texcoords.push_back(tempTexcoords[point2[1] - 1]);
			texcoords.push_back(tempTexcoords[point3[1] - 1]);

			normals.push_back(tempNormals[point1[2] - 1]);
			normals.push_back(tempNormals[point2[2] - 1]);
			normals.push_back(tempNormals[point3[2] - 1]);

			faceCount += 3;
		}
	}

	return true;
}

unsigned char* Resources::LoadFileImage(const std::string path, int* width, int* height, int* channels)
{
	unsigned char* image = stbi_load(path.c_str(), width, height, channels, 4);
	return image;
}

const std::vector<int> Resources::SplitFaceString(const std::string& str, const char delimiter)
{
	std::vector<int> tokens;
	std::stringstream ss(str);
	std::string item;

	while (std::getline(ss, item, delimiter)) 
	{
		tokens.push_back(std::stoi(item));
	}

	return tokens;
}
