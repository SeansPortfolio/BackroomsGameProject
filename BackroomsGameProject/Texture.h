#pragma once

#include <GL\glew.h>


class Texture
{
public:

	Texture();
	~Texture();

	void Create(const unsigned char*, int, int);

	void Bind(int);

private:

	GLuint TextureID;

};

